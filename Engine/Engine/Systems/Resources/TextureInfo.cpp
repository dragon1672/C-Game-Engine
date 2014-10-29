#include <gl/glew.h>
#include "TextureInfo.h"
#include <QtGui/QImage>



TextureInfo::TextureInfo() : data(nullptr), type((GLenum)GL_RGBA), type2((GLenum)-1), slotID((uint)-1), bufferID((uint)-1) { }
TextureInfo::TextureInfo(std::string name) : data(nullptr), type((GLenum)GL_RGBA), type2((GLenum)-1), slotID((uint)-1), bufferID((uint)-1) { this->name = name; }

void TextureInfo::PassDownToHardWare()
{
	if((int)slotID   < 0) slotID = NumTextures++;
	if((int)bufferID < 0) glGenTextures(1,&bufferID);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0+slotID);
	glBindTexture(GL_TEXTURE_2D, bufferID);

	glTexImage2D(GL_TEXTURE_2D,0, this->type, this->width, this->height, 0, this->type2, GL_UNSIGNED_BYTE, this->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

int TextureInfo::NumTextures = 0;
