#pragma once

typedef unsigned int uint;

#include "ExportHeader.h"

class ENGINE_SHARED BufferManager {
public:
	struct ENGINE_SHARED BufferInfo {
		uint bufferID;
		uint offset;
	private:
		uint remainingSpace;
		friend class BufferManager;
	};

private:
	static const int defaultBufferSize = 1048576;
	BufferInfo myBuffers[10];
	uint currentBufferCount;
	
public:
	BufferManager() {
		currentBufferCount = 0;
	}

	BufferInfo addData(uint size,  const void * data);
	BufferInfo addData(uint size1, const void * data1, uint size2, const void * data2);

private:
	//add buffer and returns a pointer to that buffer
	BufferManager::BufferInfo * addBuffer(int size = defaultBufferSize);

	//edits buffer passed in and returns a new instance of that buffer
	BufferManager::BufferInfo storeData(BufferInfo * buff, uint size, const void * data);
};