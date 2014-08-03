#pragma once

#include <Engine\Scene.h>
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <Engine\Tools\Random\Glm.h>

class SceneThree : public Scene {
public:
	SceneThree() : Scene("Scene Three") {}

	uint worldTexture;

	std::vector<GeometryInfo *> geos;
	int geoID;

	std::vector<uint> textures;
	int currentTextureID;

	bool shouldRefract;
	float refractFloat;

	Renderable * world;
	Renderable * meObject;
	glm::vec3 angleVel;

	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(0,5,5),glm::vec3());
		geoID = 0;
		currentTextureID = 0;
		refractFloat = 1;
		shouldRefract = false;

		angleVel = Random::randomFloat(180,360) * Random::glmRand::randomUnitVector();

		worldTexture = renderer->addCubeTexture("./../textures/boxes/earth","posx.png","negx.png","posy.png","negy.png","posz.png","negz.png");

		ShaderProgram * cubeMapShader = renderer->addShader("./../shaders/CubeMap_V.glsl","./../shaders/CubeMap_F.glsl");
		renderer->saveViewTransform(cubeMapShader,"viewTransform");
		cubeMapShader->saveUniform("camPos",myCam.getPos());
		cubeMapShader->saveUniform("refractFloat",refractFloat);
		cubeMapShader->saveUniform("shouldRefract",shouldRefract);

		//setup renderables
		auto worldGeo = renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20));
		world = renderer->addRenderable(worldGeo,renderer->defaultShaders.passThroughCubeMap);
		world->transformData.setScale(30);
		world->saveMatrixInfo("model2WorldTransform");
		world->addUniformParameter("worldMap",ParameterType::PT_TEXTURE,&worldTexture);

		auto meObjectGeo = renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20));
		meObject = renderer->addRenderable(meObjectGeo,cubeMapShader);
		meObject->saveMatrixInfo("model2WorldTransform");
		meObject->addUniformParameter("modelRotation",meObject->transformData.genRotMat());
		meObject->addUniformParameter("worldMap",ParameterType::PT_TEXTURE,&worldTexture);

		geos.push_back(meObjectGeo);
		geos.push_back(renderer->addGeometry(Neumont::ShapeGenerator::makeTeapot(20,glm::mat4())));
		geos.push_back(renderer->addGeometry(Neumont::ShapeGenerator::makeTorus(20)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/Ogre.bin"),            10)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/TeddyBear.bin"),       100)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/CartoonTree.bin"),     10)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/GhoulOBJ.bin"),        1)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/Clock.bin"),          .5)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/Head.bin"),            10)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/HQ_Moviecycle.bin"),   1)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/TronJustBike.bin"),    10)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/myChair.bin"),         1)));
		geos.push_back(renderer->addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/phone.bin"),           1)));
	
		textures.push_back(renderer->addCubeTexture("./../textures/boxes/Debug","posx.png","negx.png","posy.png","negy.png","posz.png","negz.png"));
		textures.push_back(worldTexture);
		textures.push_back(renderer->addCubeTexture("./../textures/boxes/Meadow","posx.png","negx.png","posy.png","negy.png","posz.png","negz.png"));

		menu->edit("angleSpeed",angleVel,-360,360);
		menu->edit("World", currentTextureID, 0,textures.size()-1);
		menu->edit("Geo", geoID, 0,geos.size()-1);
		menu->edit("refractFloat",refractFloat,0,2);
		menu->edit("shouldRefract",shouldRefract);
		
	}
	void update(float dt) {
		meObject->transformData.rotation += angleVel * dt;
		meObject->whatGeo = geos[geoID];
		worldTexture = textures[currentTextureID];
	}
};