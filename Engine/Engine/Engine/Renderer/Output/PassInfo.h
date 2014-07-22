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
	Camera cam;//call cam.enabled = true to render scene from this camera

	PassInfo() : frameBufferID(0), cam(false), visable(true), clearColor(.1f,.1f,.1f) {}

	//will init output to textures and set color/depth texture
	void initTextures(int width, int height); // will generate a frame buffer for you to use

	//renderable managment
	bool contains(Renderable * toCheck);
	void add(Renderable * toAdd);
	void remove(Renderable * toRemove);
	void loadRenderables(PassInfo * toLoadFrom, bool allowDups = true);

	//some extraCrap
	glm::vec3 clearColor;


	//Don't worry about any of this
	uint frameBufferID;
	// will set this PassInfo as the dude to draw to
	void activate();
	bool visable;
};


/**todo
 * Setup default cam
 * make each scene use it's own pass info
 * change cam for each pass info
 * function pointer preDraw
//*/