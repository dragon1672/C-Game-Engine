#pragma once

#include <Engine\Scene.h>

class SceneThree : public Scene {
public:
	SceneThree() : Scene("Scene Three") {}

	uint worldTexture;

	Renderable * world;
	Renderable * meObject;

	//lighting info
	glm::vec3  lightColor;
	glm::vec3  diffusePos;
	float specPower;


	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(0,5,-5),glm::vec3());
		lightColor = glm::vec3(1,1,1);
		specPower  = 50;

		ShaderProgram * cubeMapShader = renderer->addShader("./../shaders/CubeMap_V.glsl","./../shaders/CubeMap_F.glsl");
		

		//setup renderables
		auto worldGeo = renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20));
		world = renderer->addRenderable(worldGeo,renderer->defaultShaders.passThroughCubeMap);
		world->transformData.setScale(30);
		world->saveMatrixInfo("model2WorldTransform");
		auto meObjectGeo = renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20));
		meObject = renderer->addRenderable(meObjectGeo,renderer->defaultShaders.passThroughCubeMap);
		meObject->saveMatrixInfo("model2WorldTransform");

		//save shader uniforms
		renderer->saveViewTransform(cubeMapShader,"viewTransform");
		cubeMapShader->saveUniform("camPos",myCam.getPos());
		cubeMapShader->saveUniform("specPower",specPower);
		cubeMapShader->saveUniform("lightColor",lightColor);
		cubeMapShader->saveUniform("worldMap",ParameterType::PT_TEXTURE,&worldTexture);
		
		
		renderer->defaultShaders.passThroughCubeMap->saveUniform("worldMap",ParameterType::PT_TEXTURE,&worldTexture);

		worldTexture = renderer->addCubeTexture("./../textures/boxes/earth","posx.png","negx.png","posy.png","negy.png","posz.png","negz.png");
		
	}
	void update(float dt) {
		meObject->transformData.rotation.y += 180 * dt;
	}
};