#pragma once

#include <vector>
#include <Engine\Renderer\Renderable.h>
#include <Engine\Tools\Camera.h>
#include <ExportHeader.h>

class ENGINE_SHARED PassInfo {
public:
	std::vector<Renderable *> myRenderables;
	uint colorTexture;
	uint depthTexture;
	bool overrideCam;
	Camera cam;
	uint frameBufferID;

	PassInfo() : frameBufferID(0), overrideCam(false) {}

	//will init textures
	void initTextures(int width, int height); // will generate a frame buffer for you to use

	// will set this PassInfo as the dude to draw to
	void activate();

	//renderable managment
	bool contains(Renderable * toCheck);
	void add(Renderable * toAdd);
	void remove(Renderable * toRemove);
	void loadRenderables(PassInfo * toLoadFrom, bool allowDups = true);
};


/**todo
 * Setup default cam
 * make each scene use it's own pass info
 * change cam for each pass info
 * function pointer preDraw
//*/