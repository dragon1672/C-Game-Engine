#pragma once

#include <Engine/TypeDefs.h>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>

class QImage;

class ENGINE_SHARED TextureInfo : public Object {
public:
	uint width;
	uint height;
	ubyte * data;

	GLenum type;
	GLenum type2;
	uint bufferID;
	uint slotID;

	TextureInfo();
	TextureInfo(QImage * src);
};