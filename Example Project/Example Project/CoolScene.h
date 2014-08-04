#pragma once

#include <Engine\Scene.h>
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <Engine\Tools\Random\Glm.h>
#include <glm/gtx/rotate_vector.hpp>

class CoolScene : public Scene {
	Camera * theCam;
	Renderable * playerCharacter;
	struct {
		glm::vec3 normal; // model normal

		MatrixInfo transData;

		//follow data will be edited on update
		PassInfo * mirrorData;
		Renderable * mirror;
		Renderable * mirrorOutside;

		void updateData(Camera * theCam) {
			glm::vec3 rotatedNorm = glm::mat3(transData.genRotMat()) * normal;
			glm::vec3 eyeVec = -glm::normalize(theCam->getPos() - transData.position);
			
			mirrorData->cam.setPos(transData.position,rotatedNorm);
			mirrorData->cam.setPos(transData.position,glm::reflect(eyeVec,rotatedNorm));
			
			mirror->transformData = transData;
			mirrorOutside->transformData = transData;
		}
	} mirrors[20];
public:
	CoolScene() : Scene("My Cool Scene Of Awesome") {}

	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		theCam = &myCam;
		renderer->farPlane = 1000;
		GeometryInfo * mirrorGeo        = renderer->addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clock hands.bin") ,GL_TRIANGLES);
		GeometryInfo * mirrorOutsideGeo = renderer->addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clock.bin")       ,GL_TRIANGLES);
		int mirrorOutsideTexture = renderer->addTexture("./../textures/clockTexture.png");

		auto temp = renderer->addRenderable(renderer->addGeometry(Neumont::ShapeGenerator::makeCube()),renderer->defaultShaders.passThroughColor);
		temp -> transformData.setScale(100);
		temp -> saveMatrixInfo("model2WorldTransform");

		ShaderProgram * mirrorShader = renderer->addShader("./../shaders/MirrorTexture_V.glsl","./../shaders/MirrorTexture_F.glsl");
		renderer->saveViewTransform(mirrorShader,"viewTransform");

		auto playerGeo = renderer->addGeometry(BinaryToShapeLoader::loadFromFile("./../models/Ogre.bin"));
		playerCharacter = renderer->addRenderable(playerGeo,renderer->defaultShaders.passThroughTexture,renderer->addTexture("./../textures/ogre_diffuse.png"));
		playerCharacter->transformData.setScale(10);
		playerCharacter->saveTexture("myTexture");
		playerCharacter->saveMatrixInfo("model2WorldTransform");
		

		for (int i = 0; i < sizeof(mirrors) / sizeof(*mirrors); i++)
		{
			int range = 50;
			mirrors[i].transData.position = Random::glmRand::randomFloatVectorInBoxRanged(range,range,range);
			mirrors[i].transData.rotation = Random::glmRand::randomFloatVectorInBoxRanged(.00001,180,.00001);

			mirrors[i].normal = glm::vec3(0,0,1); // change if the geo changes
			mirrors[i].mirror = renderer->addRenderable(mirrorGeo,mirrorShader);
			mirrors[i].mirror->saveMatrixInfo("model2WorldTransform");
			mirrors[i].mirrorOutside = renderer->addRenderable(mirrorOutsideGeo,renderer->defaultShaders.passThroughTexture,mirrorOutsideTexture);
			mirrors[i].mirrorOutside->saveMatrixInfo("model2WorldTransform");
			mirrors[i].mirrorOutside->saveTexture("myTexture");
		}

		for (int i = 0; i < sizeof(mirrors) / sizeof(*mirrors); i++)
		{
			mirrors[i].mirrorData = renderer->addPassInfo(true);
			mirrors[i].mirrorData->remove(mirrors[i].mirror);
			mirrors[i].mirrorData->remove(mirrors[i].mirrorOutside);

			mirrors[i].mirrorData->initTextures(renderer->width(),renderer->height());

			mirrors[i].mirrorData->cam.enabled = true;
			mirrors[i].mirror->addUniformParameter("myTexture",ParameterType::PT_TEXTURE,&mirrors[i].mirrorData->colorTexture);
		}


		swapOutCurrentPassInfo(renderer);
		//removing current character
		myDefaultPass->remove(playerCharacter);
	}
	void swapOutCurrentPassInfo(WidgetRenderer * renderer) {
		//updating currentPassInfo so it will draw after other PassInfos
		PassInfo * temp = renderer->addPassInfo(true);
		myDefaultPass->visable = false;
		myDefaultPass = temp;
		theCam = &temp->cam;
	}
	void update(float dt) {
		playerCharacter->transformData.position = theCam->getPos();
		playerCharacter->transformData.postTransform = glm::orientation(theCam->getViewDir(),glm::vec3(0,0,1)) * glm::translate(glm::vec3(0,0,.1));
		for (int i = 0; i < sizeof(mirrors) / sizeof(*mirrors); i++)
		{
			//mirrors[i].transData.rotation.y += 90*dt;
			mirrors[i].updateData(theCam);
		}
	}
};