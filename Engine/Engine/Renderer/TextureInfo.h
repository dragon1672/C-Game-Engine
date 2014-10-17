#pragma once

#include <Engine/TypeDefs.h>
#include <glm/glm.hpp>
#include <Engine/Renderer/ParameterType.h>

class TextureInfo {
public:
	uint width;
	uint height;

	TextureInfo() : data(nullptr), type((GLenum)GL_RGBA), type2((GLenum)-1) {}
	TextureInfo(QImage& src) {
		data = src.bits();
		width = src.width();
		height = src.height();
		type = (GLenum)GL_RGBA;
		type2 = (GLenum)-1;
	}

	//don't worry about it
	GLenum type;
	GLenum type2;
	ubyte * data;

	uint bufferID;
	uint slotID;
};