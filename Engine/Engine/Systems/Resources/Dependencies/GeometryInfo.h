#pragma once

#include <Engine\Systems\Resources\Dependencies\BufferManager.h>
#pragma warning(disable: 4201)
#pragma warning(push)
#include <Vertex.h>
#pragma warning(pop)
#include <Engine\Systems\Resources\Dependencies\ParameterType.h>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Dependencies/AutoAtrib.h>

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

	void init(uint vertSize, const void * verts, uint numVerts, uint indicesize, const void* indices, uint numIndices, uint indexingMode);
	
	template <typename T,typename R> void init(const T * verts, uint numVerts, const R* indices, uint numIndices, uint indexingMode) {
		init(sizeof(T),verts,numVerts,sizeof(R),indices,numIndices,indexingMode);
	}
	void reset();

	void addStreamedParameter(uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);
	void addStreamedParameter(uint layoutLocation, int numOfFloats, uint bufferOffset, uint bufferStride);
	//Vertex Data
	void addStreamedParameters(AutoAtrib * obj);
	void addStreamedParameters(int * sizes,int numOfSizes);

	inline uint vertexBufferSize() const { return numVerts   * sizeOfVerts; }
	inline uint dataOffset()       const { return bufferInformation.offset; }
	inline uint indicesOffset()    const { return dataOffset() + vertexBufferSize(); };
};