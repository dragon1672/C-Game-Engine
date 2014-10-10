#pragma once

#include <Engine\Renderer\Geo\BufferManager.h>
#pragma warning(disable: 4201)
#pragma warning(push)
#include <Vertex.h>
#pragma warning(pop)
#include <Engine\Renderer\ParameterType.h>
#include <ExportHeader.h>

struct ENGINE_SHARED GeometryInfo {
private:
	static BufferManager manager;
public:
	BufferManager::BufferInfo bufferInformation;
	uint vertexArrayObjectID;
	uint numVerts;
	uint numIndices;
	uint indexingMode;
	uint sizeOfVerts;

	void init(uint vertSize, const void * verts, uint numVerts, uint indicesize, void* indices, uint numIndices, uint indexingMode);
	void init(uint vertSize, const void * verts, uint numVerts, ushort* indices, uint numIndices, uint indexingMode);
	void init(uint vertSize, const void * verts, uint numVerts, uint*   indices, uint numIndices, uint indexingMode);
	void init(const Neumont::Vertex * verts,     uint numVerts, ushort* indices, uint numIndices, uint indexingMode);
	void init(const Neumont::Vertex * verts,     uint numVerts, uint*   indices, uint numIndices, uint indexingMode);
	void reset();

	void addStreamedParameter(uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);
	void addStreamedParameter(uint layoutLocation, int numOfFloats, uint bufferOffset, uint bufferStride);
	//Vertex Data
	void addStreamedParameters(int * sizes,int numOfSizes);

	inline uint vertexBufferSize() const { return numVerts   * sizeOfVerts; }
	inline uint dataOffset()       const { return bufferInformation.offset; }
	inline uint indicesOffset()    const { return dataOffset() + vertexBufferSize(); };
};