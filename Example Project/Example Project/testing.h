#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>

#include <glm\gtx\transform.hpp>

class Testing : public WidgetRenderer {
public:
	glm::mat4 * whereMat;
	void init() {
		auto tempGeo = addGeometry(Neumont::ShapeGenerator::makeCube(),GL_TRIANGLES);
		auto renderableTemp = addRenderable(tempGeo,mainShader,0);
		whereMat = &renderableTemp->whereMat;
		renderableTemp->saveWhereMat("model2WorldTransform");
		renderableTemp->saveTexture("myTexture");
	}
	void nextFrame(float dt) {
		static float walkin = 0;
		//walkin += dt * 1;
		*whereMat = glm::translate(glm::vec3(0,0,walkin));
	}
};