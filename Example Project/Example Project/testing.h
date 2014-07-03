#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness

#include <glm\gtx\transform.hpp>

class Testing : public WidgetRenderer {
public:
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;

	glm::vec3 blendColor;
	char * myString;

	Renderable * meRenderable;
	void init() {
		myCam.setPos(glm::vec3(0,.1,0),glm::vec3(0,0,.5));

		//place shaders to folder "shaders" in solution directory
		auto meShader = addShader("../shaders/vert.glsl","../shaders/frag.glsl");
		saveViewTransform(meShader,"viewTransform");

		// format for textures with folder in solution directory
		//alphaTexture = addTexture("./../textures/Alpha.png");

		blendColor = Random::glmRand::randomFloatVectorInBox(1,1,1);

		menu->watch("Blend: ",blendColor);
		menu->watch("Blend: ",blendColor,"tab2");
		menu->watch("Blend: ",blendColor,"tab2");
		menu->edit("Blend: ",blendColor,0,1,0,1,0,1);
		myString = "pie is good";
		menu->watch("Demo:",myString);
		myString = "Pie is really good";

		// initUVData because sphere's don't have it
		auto tempGeo = addGeometry(NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeSphere(20)),GL_TRIANGLES);
		
		// when using a NU shape there is no need to define layouts
		meRenderable = addRenderable(tempGeo,meShader,-1);
		
		meRenderable->saveWhereMat("model2WorldTransform"); // really just a call to addUniformPram
		meRenderable->addUniformParameter("blendColor",ParameterType::PT_VEC3,&blendColor[0]);

	}
	void nextFrame(float dt) {
		//bad hack to update color and rotation every 2 seconds
		static float currentTime = 0;
		currentTime += dt;
		if(currentTime > 2) {
			currentTime = 0;
			blendColor = Random::glmRand::randomFloatVectorInBox(1,1,1);
			const int rotSpeedRange = 100;
			rotationSpeed = Random::glmRand::randomFloatVectorInBoxRanged(rotSpeedRange,rotSpeedRange,rotSpeedRange);
		}

		//just edit the where matrix for renderables
		rotation += rotationSpeed * dt;
		meRenderable->whereMat = glm::rotate(rotation.x,glm::vec3(1,0,0))
							  *= glm::rotate(rotation.y,glm::vec3(0,1,0))
							  *= glm::rotate(rotation.z,glm::vec3(0,0,1));
	}
};