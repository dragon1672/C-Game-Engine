#pragma once

#include <Engine/unsigned.h>
#include <glm/glm.hpp>
#include <Engine/Renderer/ParameterType.h>

class TextureInfo {
public:
	uint bufferID;
	uint slotID;
	ParameterType type;
};

struct ImageData {
	ubyte * data;
	uint width;
	uint height;
	GLenum type;
	GLenum type2;
	ImageData() : data(nullptr),
		width((uint)-1), height((uint)-1),
		type((GLenum)GL_RGBA), type2((GLenum)-1) {}
	ImageData(QImage& src) {
		init(src);
		type = (GLenum)GL_RGBA;
		type2 = (GLenum)-1;
	}
	void init(QImage& src) {
		data = src.bits();
		width = src.width();
		height = src.height();
	}
};