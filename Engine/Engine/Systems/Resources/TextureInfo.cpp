#include <gl/glew.h>
#include "TextureInfo.h"
#include <QtGui/QImage>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/IO/Stream.h>



TextureInfo::TextureInfo(std::string name) : data(nullptr), type((GLenum)GL_RGBA), type2((GLenum)-1), slotID((uint)-1), bufferID((uint)-1), Resource_CRTP(name) { }

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

bool TextureInfo::isValid()
{
	return data != nullptr && width > 0 && height > 0;
}

std::vector<std::string> TextureInfo::getErrors()
{
	std::vector<std::string> ret;
	if(data==nullptr) ret.push_back("no data for image");
	if((int)width  <= 0) ret.push_back("invalid image width");
	if((int)height <= 0) ret.push_back("invalid image height");
	return ret;
}

void TextureInfo::shutdown()
{
	SAFE_DELETE(data);
	if((int)bufferID < 0) glDeleteTextures(1,&bufferID);
}

void TextureInfo::ChildSave(Stream& s)
{
	s << width << height << numOfBytes << type << type2;
	s.append(data,numOfBytes);
}

void TextureInfo::ChildLoad(Stream& s)
{
	s >> width >> height >> numOfBytes >> type >> type2;
	SAFE_NEW(data,ubyte[numOfBytes]);
	s.readAndMoveForwardArray(data,numOfBytes);
}

void TextureInfo::resetAll()
{
	//NumTextures = 0;
}

bool TextureInfo::equals(TextureInfo& that) const
{
	if(width      != that.width)      return false;
	if(height     != that.height)     return false;
	if(numOfBytes != that.numOfBytes) return false;
	return FileIO::equalBits(data,that.data,numOfBytes);
}

int TextureInfo::NumTextures = 0;
