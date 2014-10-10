#include "MeshLoader.h"
#include <Engine/Tools/CollectionEditing.h>

#define GET_DATA(type, offset) *reinterpret_cast<type *>(bytes+offset);	offset += sizeof(type);

namespace FileIO {
	std::function<Mesh(fileByte*)> loaders[] = {
		//v1
		[](fileByte * bytes){
			Mesh ret;
			uint offset = 0;
			/*int vertexOffset = */GET_DATA(int,offset);
			int vertexSize   = GET_DATA(int,offset);
			/*int indiceOffset = */GET_DATA(int,offset);
			int indiceSize   = GET_DATA(int,offset);
			int numOfVerts   = vertexSize / (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
			int numOfindices = indiceSize/(sizeof (ushort)*3) * 3;


			for (int i = 0; i < numOfVerts; i++) {
				ret.verts.push_back(Vert());
				float posX  = GET_DATA(float,offset);
				float posY  = GET_DATA(float,offset);
				float posZ  = GET_DATA(float,offset);
				float UvX   = GET_DATA(float,offset);
				float UvY   = GET_DATA(float,offset);
				float normX = GET_DATA(float,offset);
				float normY = GET_DATA(float,offset);
				float normZ = GET_DATA(float,offset);
				ret.verts[i].pos  = glm::vec3( posX,  posY,  posZ  );
				ret.verts[i].uv   = glm::vec2( UvX,   UvY );
				ret.verts[i].norm = glm::vec3( normX, normY, normZ );
			}
			ret.indicees = Collections::Select<char,uint>(bytes+offset,numOfindices,[&offset,bytes](ushort n){
				uint ret = (*reinterpret_cast<ushort *>(bytes+offset));	offset += sizeof(ushort); return ret;
			});
		},
		//v2
		[](fileByte * bytes){
			//TODO
		}
	};



	Mesh loadFromBinary(fileByte * bytes) {
		int offset = 0;
		int firstNum = GET_DATA(int,offset);
		if(firstNum % 16) {
			//qDebug() << "Invalid Binary File";
		}

		assert(firstNum % 16 == 0);
		int index = firstNum / 16;
		return (loaders[index](bytes));
	}
	Mesh loadMeshFromFile(const char * filePath) {
		FileData file = loadFile(filePath);
		Mesh ret = loadFromBinary(file.data);
		file.cleanup();
		return ret;
	}
}