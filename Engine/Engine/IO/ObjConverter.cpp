#include "ObjConverter.h"
#include <Engine/Tools/Parsing.h>
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/CollectionEditing.h>
#include <unordered_map>
#include <algorithm>
#include <array>



#pragma region Converter
__interface IParser {
	void Parse(std::string& line);
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
	std::array<float,size> data;
	Vec() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	Vec<N>& operator=(const Vec<N>& that) // copy assignment
	{
		if (this != &that) {
			this->data = that.data;
		}
		return *this;
	}
	Vec<N>& operator=(Vec<N>&& that) // move assignment
	{
		assert(this != &that); // self-assignment check not required
		this->data = that.data;
		return *this;
	}

	virtual void Parse(std::string& line) {
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
		const int prime = 761;
		int result = 1;
		result *= prime * posID;
		result *= prime * uvID;
		result *= prime * normID;
		return result;
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
	virtual void Parse(std::string& line) {
		std::vector<std::string>vecs;
		StringManapulation::split(line,' ',vecs);
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
	uint currentSize = fileSize;
	fileByte * currentFileSpot = bytes;

	int lineCount = FileIO::lineCount(bytes,fileSize)-1;
	int currentLine = 0;


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
				if(!Collections::tryReadMap(_allVerts,v,vertIndicee)) { // adding new vert
					vertIndicee = _allVerts.size();

					if(v.posID  > 0) { v.Position = _posParser. ParsedData[v.posID  - 1]; }
					if(v.uvID   > 0) { v.Uv       = _uvsParser. ParsedData[v.uvID   - 1]; }
					if(v.normID > 0) { v.Norm     = _normParser.ParsedData[v.normID - 1]; }

					_allVerts.emplace(v,vertIndicee);
				}
				indicees.push_back(vertIndicee);
			}
			toAdd.verts.pop_back();
		}
	});
	//reserving some space to decrease vector resizing
	_posParser.ParsedData.reserve(lineCount/2);
	_normParser.ParsedData.reserve(lineCount/2);
	_uvsParser.ParsedData.reserve(lineCount/2);
	_verParser.ParsedData.reserve(lineCount/2);
	
	std::vector<ILineParser *> rawParsers;
	rawParsers.push_back(&_posParser);
	rawParsers.push_back(&_normParser);
	rawParsers.push_back(&_uvsParser);
	rawParsers.push_back(&_verParser);
#pragma endregion

#pragma region Parsing
	while(currentSize > 0) {
		std::string line;
		currentFileSpot = FileIO::readLine(currentFileSpot,currentSize,line);

		bool added = false;
		for (unsigned int parserIndex = 0; parserIndex < rawParsers.size(); parserIndex++) {
			added = rawParsers[parserIndex]->isLine(line);
			if (!added) continue;
			rawParsers[parserIndex]->addData(line);
			break;
		}
		if(callback) {
			callback(currentLine,lineCount,line,added);
		}
		currentLine++;
	}
#pragma endregion

#pragma region setting OBJVector

	//because of some class casting crap, I'm unable to use original vector of my custom object for sorting
	//saving new vector that holds onto indexs of indicees and the vert original position and sorting that vector

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
