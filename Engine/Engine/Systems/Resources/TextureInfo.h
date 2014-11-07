#pragma once

#include <Engine/TypeDefs.h>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>
#include <Engine\Systems\Resource.h>

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

	TextureInfo(std::string name="");

	void PassDownToHardWare();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

	virtual void shutdown();

};