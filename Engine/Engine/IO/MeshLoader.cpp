#include "MeshLoader.h"
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Tools/Printer.h>

#define GET_DATA(type, offset) *reinterpret_cast<type *>(bytes+offset);	offset += sizeof(type);

namespace FileIO {
	std::function<Mesh(fileByte*, std::string name)> loaders[] = {
		//v1
		[](fileByte * bytes, std::string name) -> Mesh {
			Mesh ret(name);
			uint offset = 0;
			/*int vertexOffset = */GET_DATA(int,offset);
			int vertexSize   = GET_DATA(int,offset);
			/*int indiceOffset = */GET_DATA(int,offset);
			int indiceSize   = GET_DATA(int,offset);
			int numOfVerts   = vertexSize / (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
			int numOfindices = indiceSize/(sizeof (ushort)*3) * 3;


			for (int i = 0; i < numOfVerts; i++) {
				ret.verts.push_back(Vert());
				ret.verts[i].pos.x = GET_DATA(float,offset);
				ret.verts[i].pos.y = GET_DATA(float,offset);
				ret.verts[i].pos.z = GET_DATA(float,offset);
				ret.verts[i].uv.x  = GET_DATA(float,offset);
				ret.verts[i].uv.y  = GET_DATA(float,offset);
				ret.verts[i].norm.x  = GET_DATA(float,offset);
				ret.verts[i].norm.y  = GET_DATA(float,offset);
				ret.verts[i].norm.z  = GET_DATA(float,offset);
			}
			ret.indices = Collections::Select<char,uint>(bytes+offset,numOfindices,[&offset,bytes](ushort n){
				uint tmp = (*reinterpret_cast<ushort *>(bytes+offset));	offset += sizeof(ushort); return tmp;
			});
			return ret;
		},
		/*v2
		[](fileByte * bytes, const char * name)->Mesh{
			return Mesh(); // TODO
		}
		//*/
	};



	Mesh loadFromBinary(fileByte * bytes, std::string name) {
		int offset = 0;
		int VersionNumber = GET_DATA(int,offset);
		return loaders[VersionNumber](bytes,name);
	}
	Mesh loadMeshFromFile(std::string filePath, std::string name) {
		return loadMeshFromFile(filePath.c_str(),name);
	}
	Mesh loadMeshFromFile(const char * filePath, std::string name) {
		FileData file = loadFile(filePath);
		Mesh ret;
		if(file.data != nullptr) {
			ret = loadFromBinary(file.data,name);
			file.cleanup();
		}
		return ret;
	}
}