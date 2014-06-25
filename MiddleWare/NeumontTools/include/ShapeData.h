#ifndef NEUMONT_SHAPE_DATA_H
#define NEUMONT_SHAPE_DATA_H
#include "Vertex.h"
#include <string>

namespace Neumont
{
	struct DLL_SHARED ShapeData
	{
		Vertex* verts;
		uint numVerts;
		ushort* indices;
		uint numIndices;
		char* textureFileName;
		char* normalMapFileName;
		ShapeData();
		uint vertexBufferSize() const;
		uint indexBufferSize() const;
		void cleanUp();
	};
}

#endif