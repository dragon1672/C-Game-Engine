#pragma once

#include <Engine/TypeDefs.h>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Resource.h>

class QImage;

class ENGINE_SHARED TextureInfo : public Resource {
private:
	static int NumTextures;
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

	void PassDownToHardWare();
};