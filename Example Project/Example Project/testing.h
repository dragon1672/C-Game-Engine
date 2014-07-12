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
	Renderable * meCube;
	glm::mat4 cubeRotation;
	Renderable * lightSrcRenderable;
	int normalMap;

	glm::vec3 lightColor;
	float specPower;

	bool whiteAsTexture;

	void init();
	
	void nextFrame(float dt);
	/* clock
public:
	Renderable * clock,
			   * hourHand,
			   * minHand,
			   * secHand,
			   * clockFace,
			   * glassFace;
	int hrHandAlpha,minhandAlpha,secondHandAlpha;
	glm::vec3 blendColor;
	float alpha;
	float timeScale;

	int clockFaceLowBound;
	int clockFaceHighBound;

	float seconds;
	float minutes;
	float hours;

	bool smooth;

	float clockFaceID;
	void init() {
		//myCam.setPos(glm::vec3(0,.1,30),glm::vec3(0,0,-.5));
		myCam.lookAt(glm::vec3(0,.1,30),glm::vec3(0,0,0));

		timeScale = 1;
		alpha = .5;
		smooth = true;
		
		auto clockFaceGeo =  addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clock face.bin"),  GL_TRIANGLES);
		auto clockhandGeo =  addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clock hands.bin") ,GL_TRIANGLES);
		auto clockGeo =      addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clock.bin")       ,GL_TRIANGLES);
		auto clockLenseGeo = addGeometry(BinaryToShapeLoader::loadFromFile("./../models/clockLense.bin")  ,GL_TRIANGLES);

		ShaderProgram * basicShader       = addShader("./../shaders/PassThrough_V.glsl","./../shaders/PassThrough_F.glsl"); // for clock, clock face
		saveViewTransform(basicShader,"viewTransform");
		
		ShaderProgram * alphaBinaryShader = addShader("./../shaders/BinaryAlpha_V.glsl","./../shaders/BinaryAlpha_F.glsl"); // for clock hands
		saveViewTransform(alphaBinaryShader,"viewTransform");
		
		ShaderProgram * alphaBlendShader  = addShader("./../shaders/BlendAlpha_V.glsl", "./../shaders/BlendAlpha_F.glsl" ); // for clock Lense
		saveViewTransform(alphaBlendShader,"viewTransform");

		hrHandAlpha     = addTexture("./../textures/HrHand_alpha.png");
		minhandAlpha    = addTexture("./../textures/Minhand_Alpha.png");
		secondHandAlpha = addTexture("./../textures/SecHand_alpha.png");

		//setting up clock face graphic
		clockFaceLowBound  = addTexture("./../textures/ClockFace_0.png");
		clockFaceHighBound = addTexture("./../textures/ClockFace_1.png");
		clockFaceHighBound = addTexture("./../textures/ClockFace_2.png");
		clockFaceHighBound = addTexture("./../textures/ClockFace_3.png");
		clockFaceHighBound = addTexture("./../textures/ClockFace_4.png");
		clockFaceHighBound = addTexture("./../textures/ClockFace_5.png");

		clock     = addRenderable(clockGeo,basicShader,addTexture("./../textures/clockTexture.png"));
		clock->saveTexture("myTexture");	clock->saveWhereMat("model2WorldTransform");
		
		clockFace = addRenderable(clockFaceGeo,basicShader,addTexture("./../textures/ClockFace.png"));
		clockFace->saveTexture("myTexture");	clockFace->saveWhereMat("model2WorldTransform");

		hourHand  = addRenderable(clockhandGeo,alphaBinaryShader,addTexture("./../textures/ClockHands.png"));
		hourHand->addUniformParameter("myAlpha", ParameterType::PT_TEXTURE,&hrHandAlpha);
		hourHand->saveTexture("myTexture");	hourHand->saveMatrixInfo("model2WorldTransform");
		
		minHand   = addRenderable(clockhandGeo,alphaBinaryShader,hourHand->textureID);
		minHand->addUniformParameter("myAlpha", ParameterType::PT_TEXTURE,&minhandAlpha);
		minHand->saveTexture("myTexture");	minHand->saveMatrixInfo("model2WorldTransform");
		
		secHand   = addRenderable(clockhandGeo,alphaBinaryShader,hourHand->textureID);
		secHand->addUniformParameter("myAlpha", ParameterType::PT_TEXTURE,&secondHandAlpha);
		secHand->saveTexture("myTexture");	secHand->saveMatrixInfo("model2WorldTransform");

		glassFace = addRenderable(clockLenseGeo,alphaBlendShader,-1);
		glassFace->saveTexture("myTexture");
		glassFace->saveMatrixInfo("model2WorldTransform");
		glassFace->addUniformParameter("blendColor",blendColor);
		glassFace->addUniformParameter("alphaVal",alpha);
		randomClockFace();
		

		

		blendColor = glm::vec3(1,1,1);

		menu->edit("Time Scale:",timeScale,-10,100);
		menu->edit("Smooth:",smooth);
		menu->button("Reset Time To Now:",fastdelegate::MakeDelegate(this,&Testing::setTimeToNow));
		menu->edit("Alpha:",alpha,0,1,true,"Clock Face");
		menu->edit("ClockFaceTexture",clockFaceID,clockFaceLowBound,clockFaceHighBound+1-.1f,true,"Clock Face");
		menu->button("Random Texture",fastdelegate::MakeDelegate(this,&Testing::randomClockFace),"Clock Face");

		time_t t = time(0);
		struct tm * now = localtime( & t );
		seconds = now->tm_sec;
		minutes = now->tm_min;
		hours   = now->tm_hour;
	}
	void setTimeToNow() {
		time_t t = time(0);
		struct tm * now = localtime( & t );
		seconds = now->tm_sec % 60;
		minutes = now->tm_min % 60;
		hours   = now->tm_hour % 12;
		timeScale = 1;
	}
	void randomClockFace() {
		clockFaceID = Random::randomInt(clockFaceLowBound,clockFaceHighBound);
	}
	void nextFrame(float dt) {
		glassFace->textureID = (int)clockFaceID;
		seconds += dt * timeScale;
		if(seconds > 60) { minutes += 1; seconds -= 60; }
		if(minutes > 60) { hours   += 1; minutes -= 60; }


		float secondsPercent = smooth ? (seconds / 60) : (((int)seconds) / 60.0f);
		float minutesPercent = smooth ? (minutes + secondsPercent) / 60 : (((int)minutes) / 60.0f);
		float hoursPercent   = smooth ? (hours   + minutesPercent) / 12 : (((int)hours  ) / 12.0f);

		hourHand -> transformData.rotation.z = -hoursPercent   * 360;
		minHand  -> transformData.rotation.z = -minutesPercent * 360;
		secHand  -> transformData.rotation.z = -secondsPercent * 360;
		alphaAnimation(dt);
	}
	void alphaAnimation(float dt) {
		static bool hasCompleted = false;
		if(!hasCompleted) {
			float beginAlpha = 1;
			float endAlpha = .4;
			float duration = 5; //seconds
			static float currentProgress = 0;
			currentProgress += dt;
			float currentPercent = currentProgress / duration;
			alpha = (endAlpha - beginAlpha) * currentPercent + beginAlpha;
			hasCompleted = currentPercent >= 1;
		}
	}
	//*/
};