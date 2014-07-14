#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <ctime>

#include <glm\gtx\transform.hpp>

class Testing : public WidgetRenderer {
public:
	Renderable * meOrge;
	glm::mat4 headRotation;
	Renderable * lightSrcRenderable;
	int normalMap;
	int occlusionmap;
	bool showTexture;
	bool useNormalMap;
	bool useOcclusion;

	glm::vec3 lightColor;
	float specPower;

	void init();
	
	void nextFrame(float dt);
};