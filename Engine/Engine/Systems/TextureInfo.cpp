#include "TextureInfo.h"
#include <QtGui/QImage>



TextureInfo::TextureInfo() : data(nullptr), type((GLenum)GL_RGBA), type2((GLenum)-1) { }

TextureInfo::TextureInfo(QImage * src)
{
	data = src->bits();
	width = src->width();
	height = src->height();
	type = (GLenum)GL_RGBA;
	type2 = (GLenum)-1;
}
