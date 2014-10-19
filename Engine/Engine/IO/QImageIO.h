#pragma once

#include <Engine/IO/FileIO.h>
#include <QtGui/QImage>


namespace FileIO {
	QImage loadImage(const char * path, bool flipHorz = false, bool flipVert = false);
	QImage loadImage(std::string path, bool flipHorz = false, bool flipVert = false);
}