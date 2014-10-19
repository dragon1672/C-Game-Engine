#include <GL\glew.h>
#include "GeometryInfo.h"
#include <Engine\Tools\CollectionEditing.h>

BufferManager GeometryInfo::manager;


void GeometryInfo::init(uint vertSize, const void * verts, uint numVerts, ushort* indices, uint numIndices, GLuint indexingMode) {
	init(vertSize,verts,numVerts,sizeof(ushort),indices,numIndices,indexingMode);
}
	void GeometryInfo::init(uint vertSize, const void * verts, uint numVerts, uint* indices, uint numIndices, GLuint indexingMode) {
	init(vertSize,verts,numVerts,sizeof(uint),indices,numIndices,indexingMode);
}
void GeometryInfo::init(const Neumont::Vertex * verts, uint numVerts, ushort* indices, uint numIndices, GLuint indexingMode) {
	init(sizeof(Neumont::Vertex),verts,numVerts,indices,numIndices,indexingMode);
}
void GeometryInfo::init(const Neumont::Vertex * verts, uint numVerts, uint* indices, uint numIndices, GLuint indexingMode) {
	init(sizeof(Neumont::Vertex),verts,numVerts,indices,numIndices,indexingMode);
}

void GeometryInfo::init(uint vertSize, const void * verts, uint numVerts, uint indicesize, void* indices, uint numIndices, uint indexingMode)
{
	sizeOfVerts = vertSize;
	uint vertexBufferSize = numVerts * sizeOfVerts;
	uint indexBufferSize = numIndices * indicesize;


	glGenVertexArrays(1,&vertexArrayObjectID);
	this->numVerts = numVerts;
	this->numIndices = numIndices;
	this->indexingMode = indexingMode;
	bufferInformation = manager.addData(vertexBufferSize,verts,indexBufferSize,indices);
}

void GeometryInfo::addStreamedParameter(uint layoutLocation, ParameterType parameterType,  uint bufferOffset, uint bufferStride) {
	addStreamedParameter(layoutLocation,parameterType/sizeof(float),bufferOffset,bufferStride);
}

void GeometryInfo::addStreamedParameter(uint layoutLocation, int numOfFloats, uint bufferOffset, uint bufferStride)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferInformation.bufferID);
	glBindVertexArray(vertexArrayObjectID);

	glEnableVertexAttribArray(layoutLocation); // pos

	glBindBuffer(GL_ARRAY_BUFFER, bufferInformation.bufferID);
	glVertexAttribPointer(layoutLocation, numOfFloats, GL_FLOAT, GL_FALSE, bufferStride, (void*)(bufferOffset+bufferInformation.offset));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferInformation.bufferID);
}

void GeometryInfo::addStreamedParameters(int * sizes,int numOfSizes)
{
	int stride = Collections::Sum(sizes,numOfSizes) * sizeof(float);
	int offset = 0;
	for (int i = 0; i < numOfSizes; i++)
	{
		addStreamedParameter(i,sizes[i],offset,stride);
		offset += sizes[i] * sizeof(float);
	}
}
