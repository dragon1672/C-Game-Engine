#include <GL\glew.h>
#include "BufferManager.h"

#ifdef _DEBUG
#pragma warning(disable: 4127)
#pragma warning(push)
#include <Qt/qdebug.h>
#pragma warning(pop)
#endif

#include <cassert>
BufferManager::BufferInfo BufferManager::addData(uint size1, const void * data1, uint size2, const void * data2) {
	bool stored = false;
	int totalsize = size1+size2;
	BufferInfo ret = BufferInfo();
	for(uint i=0;i<currentBufferCount && !stored;i++) {
		if((uint)totalsize < myBuffers[i].remainingSpace) {
			ret = storeData(&myBuffers[i],size1,data1);
			storeData(&myBuffers[i],size2,data2);
			stored = true;
		}
	}

	if(!stored) {
		uint requiredSize = (totalsize>defaultBufferSize)? totalsize : defaultBufferSize;
		BufferInfo * buff = addBuffer(requiredSize);
		ret = storeData(buff,size1,data1);
		storeData(buff,size2,data2);
		assert(buff->offset+buff->remainingSpace == requiredSize);
	}
	return ret;
}
BufferManager::BufferInfo BufferManager::addData(uint size, const void * data) {
	bool stored = false;
	BufferInfo ret = BufferInfo();
	for(uint i=0;i<currentBufferCount && !stored;i++) {
		if(size < myBuffers[i].remainingSpace) {
			ret = storeData(&myBuffers[i],size,data);
			stored = true;
		}
	}

	if(!stored) {
		int requiredSize = (size>defaultBufferSize)? size : defaultBufferSize;
		ret = storeData(addBuffer(requiredSize),size,data);
	}
	return ret;
}

BufferManager::BufferInfo * BufferManager::addBuffer(int size) {
	BufferInfo * ret = &myBuffers[currentBufferCount++];

	glGenBuffers(1, &(ret->bufferID));
	
	glBindBuffer(GL_ARRAY_BUFFER, ret->bufferID);
	
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

	ret->remainingSpace = size;
	ret->offset = 0;
#ifdef _DEBUG
	qDebug() << "Created new Buffer( ID: " << ret->bufferID << ", Size: " << ret->remainingSpace << " )";
#endif
	return ret;
}
BufferManager::BufferInfo BufferManager::storeData(BufferInfo * buff, uint size, const void * data) {
#ifdef _DEBUG
	qDebug() << "Storing in Buffer ( " << buff->bufferID << " ) " << size << " / " << buff->remainingSpace << " bytes of data";
#endif
	glBindBuffer(GL_ARRAY_BUFFER, buff->bufferID);
	
	glBufferSubData(GL_ARRAY_BUFFER,buff->offset,size,data);
	
	BufferInfo ret = *buff;

	buff->remainingSpace -= size;
	buff->offset += size;

	return ret;
}