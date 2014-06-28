#pragma once

//cpp
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"

#include <Engine\Renderer\Renderer.h>
#include <Qt/qwidget.h>
#include <Engine\Tools\Camera.h>
#include <Engine\Tools\Timer.h>

class WidgetRenderer : public Renderer, public QWidget {
private:
	glm::mat4 viewTransform;
	QTimer updateTimer;
	Timer gameTimer;
public:
	Camera myCam;
	//applied after camera
	glm::mat4 additionalViewTransform;
	

	void init() {
		Renderer::init();
		glewInit();

		setMouseTracking(true);
	
		connect(&updateTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		updateTimer.start(0);
		gameTimer.start();
	}
private:
	void nxtFrm() {
		nextFrame(gameTimer.interval());
	}
protected:
	virtual void nextFrame(float dt) {

	}
public:
	void paintGL() {
		glViewport(0,0,width(),height());
		glClearColor(.1f,.1f,.1f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		const float aspectRatio = (float)width()/(float)height();
		viewTransform = glm::mat4();
		viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
		viewTransform *= myCam.getWorld2View();
		viewTransform *= additionalViewTransform;

		resetAllShaders_validPush();

		for (uint i = 0; i < numOfRenderables; i++)
		{
			draw(myRenderables[i]));
		}
	}
};