#include "BinaryToShapeLoader.h"
#include <fstream>
#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)


#define WHITE glm::vec4(1,1,1,1)

Neumont::ShapeData BinaryToShapeLoader::loadFromFile(const char * fileName) {
	std::ifstream input( fileName , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	int fileSize = (int)input.tellg();
	input.seekg(0, std::ios::beg);
	
	byte * bytes = new byte[fileSize];
	input.read(bytes, fileSize);
	input.close();
	int offset = 0;

	int vertexOffset = *reinterpret_cast<int *>(bytes+offset);	offset += sizeof(int);
	int vertexSize   = *reinterpret_cast<int *>(bytes+offset);	offset += sizeof(int);
	int indiceOffset = *reinterpret_cast<int *>(bytes+offset);	offset += sizeof(int);
	int indiceSize   = *reinterpret_cast<int *>(bytes+offset);	offset += sizeof(int);
	int numOfVerts   = vertexSize / (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
	int numOfindices = indiceSize/(sizeof (ushort)*3) * 3;

	Neumont::Vertex * verts = new Neumont::Vertex[numOfVerts];
	ushort * indicees = new ushort[numOfindices];

	for (int i = 0; i < numOfVerts; i++) {
		verts[i].color = WHITE;
		float posX  = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float posY  = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float posZ  = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float UvX   = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float UvY   = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float normX = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float normY = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		float normZ = *reinterpret_cast<float *>(bytes+offset);	offset += sizeof(float);
		verts[i].position= glm::vec3(posX,posY,posZ);
		verts[i].uv = glm::vec2(UvX,UvY);
		verts[i].normal = glm::vec3(normX,normY,normZ);
	}
	for (int i = 0; i < numOfindices; i++) {
		indicees[i] = *reinterpret_cast<ushort *>(bytes+offset);	offset += sizeof(ushort);
	}

	delete [] bytes;

	Neumont::ShapeData ret;
	ret.indices = indicees;
	ret.numIndices = numOfindices;
	ret.verts = verts;
	ret.numVerts = numOfVerts;
	return ret;
}