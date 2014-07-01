#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>

#include <glm\gtx\transform.hpp>

class Testing : public WidgetRenderer {
public:
	static const int skyboxScale = 2;
	float skyboxRotation;
	glm::mat4 * skyBoxMatrix;

	int alphaTexture;
	int mainTexture;
	int grassTexture;
	void init() {
		skyboxRotation = 0;
		auto meShader = addShader("../shaders/alphaV.glsl","../shaders/alphaF.glsl");
		mainShader->buildBasicProgram("../shaders/passV.glsl","../shaders/passF.glsl");
		saveViewTransform(meShader,"viewTransform");

		alphaTexture = addTexture("./../textures/Alpha.png");
		mainTexture = addTexture("./../textures/Alpha_mainTexture.png");
		grassTexture = addTexture("./../textures/Grass.png");

		auto skyBoxGeo = addGeometry(Neumont::ShapeGenerator::makeSphere(20),GL_TRIANGLES);
		auto skyBoxRenderable = addRenderable(skyBoxGeo,meShader,mainTexture);

		skyBoxMatrix = &skyBoxRenderable->whereMat;
		skyBoxRenderable->saveWhereMat("model2WorldTransform");
		skyBoxRenderable->saveTexture("myTexture");
		skyBoxRenderable->addUniformParameter("myAlpha",ParameterType::PT_TEXTURE,&alphaTexture);

		auto planeGeo = addGeometry(Neumont::ShapeGenerator::makePlane(10),GL_TRIANGLES);
		auto planeRenderable = addRenderable(planeGeo,mainShader,grassTexture);
		planeRenderable->saveWhereMat("model2WorldTransform");
		planeRenderable->saveTexture("myTexture");
	}
	void nextFrame(float dt) {
		skyboxRotation += dt;
		*skyBoxMatrix = glm::rotate(skyboxRotation,glm::vec3(0,0,1)) * glm::scale(glm::vec3(skyboxScale,skyboxScale,skyboxScale));
	}
};