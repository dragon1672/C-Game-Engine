#pragma once

#include "Scene.h"
#include <ShapeGenerator.h>

class SceneTwo : public Scene {
public:
	SceneTwo() : Scene("SceneTwo") {}
	Renderable * meRenderable;
	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		auto tempGeo = renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20),GL_TRIANGLES);
		meRenderable = renderer->addRenderable(tempGeo,renderer->mainShader);
		meRenderable->saveMatrixInfo("model2WorldTransform");
	}
	void enable() {
		meRenderable->visible = true;
	}
	void disable() {
		meRenderable->visible = false;
	}
	void update(float dt) {
		meRenderable->transformData.rotation.x -= 30 * dt;
	}
};