#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>

class Testing : public BasicGui {
public:
	void init() {
		auto tempGeo = meScene.addGeometry(Neumont::ShapeGenerator::makeCube(),GL_TRIANGLES);
		auto renderableTemp = meScene.addRenderable(tempGeo,meScene.mainShader,0);

		renderableTemp->saveWhereMat("model2WorldTransform");
		renderableTemp->saveTexture("myTexture");

	}
	void nextFrame() {

	}
};