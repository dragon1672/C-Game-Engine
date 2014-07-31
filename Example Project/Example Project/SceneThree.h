#pragma once

#include <Engine\Scene.h>

class SceneThree : public Scene {
	SceneThree() : Scene("Scene Three") {}

	uint worldTexture;


	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(0,5,-5),glm::vec3());
		//worldTexture = renderer
	}
	void update(float dt) {

	}
};