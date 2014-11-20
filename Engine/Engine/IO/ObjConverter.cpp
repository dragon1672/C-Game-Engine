#include "ObjConverter.h"
#include <Engine/Tools/Parsing.h>
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/CollectionEditing.h>
#include <unordered_map>
#include <algorithm>



#pragma region Converter
__interface IParser {
	void Parse(std::string line);
};
__interface ILineParser
{
	bool isLine(std::string line);
	void addData(std::string line);
};
template<typename T>
class LineParser : public ILineParser {
public:
	std::vector<T> ParsedData;
	std::function<void(T&)>callback;
	std::string lineToMatch;

	LineParser(std::string toMatch) : lineToMatch(toMatch) {}
	LineParser(std::string toMatch,std::function<void(T)> callback) : lineToMatch(toMatch),callback(callback) {}

	virtual bool isLine(std::string line) {
		if(line.size() < lineToMatch.size()+1) return false;
		for (unsigned int i = 0; i < lineToMatch.size(); i++) {
			if(line[i] != lineToMatch[i]) return false;
		}
		bool ret = line[lineToMatch.size()] == ' ';
		return ret;
	}
	virtual void addData(std::string line) {
		T t;
		t.Parse(line);
		ParsedData.push_back(t);
		if(callback) callback(t);
	}

};

template<unsigned int N>
class Vec : public IParser {
public:
	static const unsigned int size = N;
	float data[size];
	Vec() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	virtual void Parse(std::string line) {
		for (int i = 0; i < size; i++) {
			const float defaultVal = 0;
			bool valid = false;
			data[i] = defaultVal;
			while(!valid && line != "") { // if at first you don't succeed, try try again
				valid = EngineParser::tryParseFloatGobbleSrc(line,data[i]);
			}
			//if failed result will == 0;
			assert(valid || data[i] == defaultVal);
		}
	}

};

class ObjVertex {
public:
	static ObjVertex ParseVert(std::string data, bool& valid) {
		valid = true;
		int pos,uvs,nor;
		pos = -1;	valid = valid && EngineParser::tryParseIntGobbleSrc(data,pos);
		uvs = -1;	valid = valid && EngineParser::tryParseIntGobbleSrc(data,uvs);
		nor = -1;	valid = valid && EngineParser::tryParseIntGobbleSrc(data,nor);
		return ObjVertex(pos,uvs,nor);
	}
	int posID,uvID,normID;
	Vec<3> Position;
	Vec<2> Uv;
	Vec<3> Norm;
	ObjVertex(int pos,int uv, int norm) :
		posID(pos),uvID(uv), normID(norm)
	{ }
	size_t GetHashCode() const {
		return std::hash<int>()(posID) ^ std::hash<int>()(uvID) ^ std::hash<int>()(normID);
	}
};

inline bool operator==(const ObjVertex& rhs, const ObjVertex& lhs){
	if(rhs.posID  != lhs.posID ) return false;
	if(rhs.uvID   != lhs.uvID  ) return false;
	if(rhs.normID != lhs.normID) return false;
	return true;
}
inline bool operator!=(const ObjVertex& rhs, const ObjVertex& lhs){return !( rhs == lhs);}

class Indicee : public IParser {
public:
	std::vector<ObjVertex> verts;
	virtual void Parse(std::string line) {
		auto vecs = StringManapulation::split(line,' ');
		for (unsigned int i = 0; i < vecs.size(); i++) {
			bool valid = false;
			auto tmp = ObjVertex::ParseVert(vecs[i],valid);
			if(valid)
				verts.push_back(tmp);
		}
	}

};

namespace std {
	template <>
	class hash<ObjVertex>{
	public :
		size_t operator()(const ObjVertex &name ) const {
			return name.GetHashCode();
		}
	};
};

#pragma endregion

Mesh FileIO::Obj2Mesh(fileByte * bytes, uint fileSize, std::string name, LoadingCallBack callback /*= LoadingCallBack()*/)
{
#pragma region init parsers
	std::vector<ObjVertex> verts;
	std::vector<unsigned int> indicees;

	LineParser<Vec<3>> _posParser ("v");
	LineParser<Vec<3>> _normParser("vn");
	LineParser<Vec<2>> _uvsParser ("vt");
	std::unordered_map<ObjVertex,int>  _allVerts;
	LineParser<Indicee> _verParser("f",[&](Indicee& toAdd){
		while(toAdd.verts.size() >= 3) {
			const int indexs[] = {0,toAdd.verts.size()-2,toAdd.verts.size()-1};
			for (int i = 0; i < 3; i++) {
				ObjVertex& v = toAdd.verts[indexs[i]];
				int vertIndicee;
				if(!Collections::tryReadMap(_allVerts,v,vertIndicee)) {
					vertIndicee = _allVerts.size();

					if(v.posID  > 0) { for (int i = 0; i < 3; i++) { v.Position.data[i] = _posParser. ParsedData[v.posID  - 1].data[i]; } }
					if(v.uvID   > 0) { for (int i = 0; i < 2; i++) { v.Uv.data[i]       = _uvsParser. ParsedData[v.uvID   - 1].data[i]; } }
					if(v.normID > 0) { for (int i = 0; i < 3; i++) { v.Norm.data[i]     = _normParser.ParsedData[v.normID - 1].data[i]; } }

					_allVerts.emplace(v,vertIndicee);
				}
				indicees.push_back(vertIndicee);
			}
			toAdd.verts.pop_back();
		}
	});
	std::vector<ILineParser *> rawParsers;
	rawParsers.push_back(&_posParser);
	rawParsers.push_back(&_normParser);
	rawParsers.push_back(&_uvsParser);
	rawParsers.push_back(&_verParser);
#pragma endregion

#pragma region Parsing
	uint currentSize = fileSize;
	fileByte * currentFileSpot = bytes;

	while(currentSize > 0) {
		std::string line;
		currentFileSpot = FileIO::readLine(currentFileSpot,currentSize,line);
		int index = fileSize - currentSize;

		bool added = false;
		for (unsigned int parserIndex = 0; parserIndex < rawParsers.size(); parserIndex++) {
			added = rawParsers[parserIndex]->isLine(line);
			if (!added) continue;
			rawParsers[parserIndex]->addData(line);
			break;
		}
		if(callback) {
			callback(index,fileSize,line,added);
		}
	}
#pragma endregion

#pragma region setting OBJVector

	//because of some class casting crap, i'm unable to use orginal vector of my custom object for sorting
	//saving new vector that holds onto indexs of indicees and the vert orginal position and sorting that vector

	//original index, indiceeIndex
	std::vector<std::pair<int,int>> myVec;
	std::vector<ObjVertex> orginalVector;
	myVec.reserve(_allVerts.size());
	orginalVector.reserve(_allVerts.size());
	int counter = 0;
	for(auto& v : _allVerts) {
		myVec.push_back(std::pair<int,int>(counter++,v.second));
		orginalVector.push_back(v.first);
	}
	std::sort(myVec.begin(),myVec.end(),[](std::pair<int,int> first, std::pair<int,int> second){
		return first.second <= second.second;
	});
	for (unsigned int i = 0; i < myVec.size(); i++) {
		verts.push_back(orginalVector[myVec[i].first]);
	}

#pragma endregion

#pragma region converting

	Mesh ret(name);

	ret.indices = indicees;
	ret.verts = Collections::Select<ObjVertex,Vert>(verts,[](ObjVertex&v) {
		Vert ret;
		for (int i = 0; i < 3; i++) { ret.pos[i]  = v.Position.data[i]; }
		for (int i = 0; i < 2; i++) { ret.uv[i]   = v.Uv.data[i];       }
		for (int i = 0; i < 3; i++) { ret.norm[i] = v.Norm.data[i];     }
		return ret;
	});

	return ret;

#pragma endregion
}

Mesh FileIO::ObjFilej2Mesh(const char * filePath, std::string name, LoadingCallBack callback /*= LoadingCallBack()*/)
{
	FileData tmp = FileIO::loadFile(filePath);
	auto ret = Obj2Mesh(tmp.data,tmp.size,name, callback);
	tmp.cleanup();
	return ret;
}

Mesh FileIO::ObjFilej2Mesh(std::string filePath, std::string name, LoadingCallBack callback /*= LoadingCallBack()*/)
{
	return ObjFilej2Mesh(filePath.c_str(),name,callback);
}
