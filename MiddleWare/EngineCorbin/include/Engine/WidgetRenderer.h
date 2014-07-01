#pragma once

/*
         +-------------------------------------------------------+
		 | Shade Code Notes                                      |
		 +--------------------------------+----------------------+
		 | Save renderable whereMatrix as | model2WorldTransform |
		 | Save renderable texture as     | myTexture            |
		 +-------------------------------------------------------+
//*/
/* default vert shader
#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec3 col;
in layout(location=3) vec2 uv;

out vec2 outUv;
out vec3 outCol;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outUv = uv;
	outCol = col;
}
//*/

/* default frag shader
#version 400

//PassThrough FragShader

in vec2 outUv;
in vec3 outCol;

uniform sampler2D myTexture;

void main() {
	gl_FragColor = outCol * texture(myTexture, outUv);
}
//*/

#include <Engine\Renderer\Renderer.h>
#include <Qt/qwidget.h>
#include <Qt/qtimer.h>
#include <Engine\Tools\Camera.h>
#include <Engine\Tools\Timer.h>
#include <ExportHeader.h>

#include <QtOpenGL\qglwidget>
//                                   GLWidge must be first for MOC to work
class ENGINE_SHARED WidgetRenderer : public QGLWidget, public Renderer {
private:

	Q_OBJECT;

	glm::mat4 viewTransform;
	QTimer updateTimer;
	Timer gameTimer;

protected:
	float dt;
	Camera myCam;
	glm::mat4 additionalViewTransform; //applied after camera
	
	virtual void nextFrame(float dt) {}
	virtual void init() {}
	void saveViewTransform(ShaderProgram * shader, const char * name) {
		shader->saveUniform(name,ParameterType::PT_MAT4,&viewTransform[0][0]);
	}
public:
	void initializeGL();
	void paintGL();
private slots:
	void nxtFrm();
public:
	virtual void mouseMoveEvent(QMouseEvent* e); // just updates the cam by default
	virtual void keyPressEvent(QKeyEvent* e); // just updates the cam by default
	void updateCam(QKeyEvent* key = nullptr, QMouseEvent* mouse = nullptr);
};