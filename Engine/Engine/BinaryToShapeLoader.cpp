#include "BinaryToShapeLoader.h"
#include <fstream>
#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)

#define GET_DATA(type, offset) *reinterpret_cast<type *>(bytes+offset);	offset += sizeof(type);

#define WHITE glm::vec4(1,1,1,1)
Neumont::ShapeData BinaryToShapeLoader::loadFromFile(const char * fileName) {
	//understand da file
	std::ifstream input( fileName , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	int fileSize = (int)input.tellg();
	input.seekg(0, std::ios::beg);
	
	//copy da file
	myByte * bytes = new myByte[fileSize];
	input.read(bytes, fileSize);
	input.close();

	//load da data
	Neumont::ShapeData ret = loadFromBinary(bytes);

	//delete da copy of the file
	delete [] bytes;

	return ret;
}
Neumont::ShapeData BinaryToShapeLoader::loadFromBinary(myByte * bytes) {
	uint offset = 0;
	int vertexOffset = GET_DATA(int,offset);
	int vertexSize   = GET_DATA(int,offset);
	int indiceOffset = GET_DATA(int,offset);
	int indiceSize   = GET_DATA(int,offset);
	int numOfVerts   = vertexSize / (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
	int numOfindices = indiceSize/(sizeof (ushort)*3) * 3;

	Neumont::Vertex * verts = new Neumont::Vertex[numOfVerts];
	ushort * indicees = new ushort[numOfindices];

	for (int i = 0; i < numOfVerts; i++) {
		verts[i].color = WHITE;
		float posX  = GET_DATA(float,offset);
		float posY  = GET_DATA(float,offset);
		float posZ  = GET_DATA(float,offset);
		float UvX   = GET_DATA(float,offset);
		float UvY   = GET_DATA(float,offset);
		float normX = GET_DATA(float,offset);
		float normY = GET_DATA(float,offset);
		float normZ = GET_DATA(float,offset);
		verts[i].position= glm::vec3(posX,posY,posZ);
		verts[i].uv = glm::vec2(UvX,UvY);
		verts[i].normal = glm::vec3(normX,normY,normZ);
	}
	for (int i = 0; i < numOfindices; i++) {
		indicees[i] = *reinterpret_cast<ushort *>(bytes+offset);	offset += sizeof(ushort);
	}

	Neumont::ShapeData ret;
	ret.indices = indicees;
	ret.numIndices = numOfindices;
	ret.verts = verts;
	ret.numVerts = numOfVerts;
	return ret;
}