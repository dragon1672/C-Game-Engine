#pragma once

#include <Engine/TypeDefs.h>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>
#include <Engine\Systems\Resource.h>

class QImage;

class ENGINE_SHARED MAKE_RESOURCE_CLASS(TextureInfo) {
private:
	static int NumTextures;
public:
	static void resetAll();
	uint width;
	uint height;
	ubyte * data;
	uint numOfBytes;

	GLenum type;
	GLenum type2;
	uint bufferID;
	uint slotID;

	TextureInfo(std::string name="");

	void PassDownToHardWare();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

	virtual void shutdown();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	bool equals(TextureInfo& that) const;

};