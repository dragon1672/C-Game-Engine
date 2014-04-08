#pragma once

#include "BufferManager.h"
#pragma warning(disable: 4201)
#pragma warning(push)
#include <Vertex.h>
#pragma warning(pop)
#include "ParameterType.h"
#include "ExportHeader.h"

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

	void init(uint vertSize, const void * verts, uint numVerts, ushort* indices, uint numIndices, uint indexingMode);
	//template<class TVert>
	void init(const Neumont::Vertex * verts, uint numVerts, ushort* indices, uint numIndices, uint indexingMode);


	void addStreamedParameter(uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);
	//Vertex Data
	inline void NU_VertexStreamedPosition(int layoutLocation) { addStreamedParameter(layoutLocation,ParameterType::PT_VEC3,Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE); }
	inline void NU_VertexStreamedColor(int layoutLocation)    { addStreamedParameter(layoutLocation,ParameterType::PT_VEC4,Neumont::Vertex::COLOR_OFFSET,    Neumont::Vertex::STRIDE); }
	inline void NU_VertexStreamedNormal(int layoutLocation)   { addStreamedParameter(layoutLocation,ParameterType::PT_VEC3,Neumont::Vertex::NORMAL_OFFSET,   Neumont::Vertex::STRIDE); }
	inline void NU_VertexStreamedUv(int layoutLocation)       { addStreamedParameter(layoutLocation,ParameterType::PT_VEC2,Neumont::Vertex::UV_OFFSET,       Neumont::Vertex::STRIDE); }

	inline uint vertexBufferSize() const { return numVerts   * sizeOfVerts; }
	inline uint indexBufferSize()  const { return numIndices * sizeof(ushort); }
	inline uint dataOffset()       const { return bufferInformation.offset; }
	inline uint indicesOffset()    const { return bufferInformation.offset + vertexBufferSize(); };
	inline uint endOffset()        const { return bufferInformation.offset + totalBufferSize();  };
	inline uint totalBufferSize()  const { return indexBufferSize() + vertexBufferSize(); };
};