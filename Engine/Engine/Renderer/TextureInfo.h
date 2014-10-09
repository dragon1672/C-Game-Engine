#pragma once

#include <Engine/unsigned.h>
#include <glm/glm.hpp>

class TextureInfo {
public:
	uint bufferID;
	uint slotID;
};
class ImageInfo : public TextureInfo {
	const char * src;
	uint width;
	uint height;
	glm::vec2 offset;
	glm::vec2 scale;
};