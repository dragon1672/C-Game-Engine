#pragma once

#include <Engine/IO/FileIO.h>
#include <QtGui/QImage>


namespace FileIO {
	struct ENGINE_SHARED BinaryImage {
		//extension CorImage
		int width,height,numOfBytes;
		byte * data;
		static int dataOffset() { return 3*sizeof(int); }
		void cleanup() { delete (data-dataOffset()); }
	};
	ENGINE_SHARED BinaryImage loadBinaryImage(const char * path);
	ENGINE_SHARED BinaryImage loadBinaryImage(std::string path);
	ENGINE_SHARED QImage loadImage(const char * path, bool flipHorz = false, bool flipVert = false);
	ENGINE_SHARED QImage loadImage(std::string path, bool flipHorz = false, bool flipVert = false);
}