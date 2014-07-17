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
#include <Engine\DebugTools\DebugMenuManager.h>

#include <QtOpenGL\qglwidget>
//                                   GLWidge must be first for MOC to work
class ENGINE_SHARED WidgetRenderer : public QGLWidget, public Renderer {
private:
#pragma region camControls
	//changing these will do nothing
	static const int CAM_CONTROL_FORWARD  = 'W';
	static const int CAM_CONTROL_BACKWARD = 'S';
	static const int CAM_CONTROL_LEFT     = 'A';
	static const int CAM_CONTROL_RIGHT    = 'D';
	static const int CAM_CONTROL_UP       = 'R';
	static const int CAM_CONTROL_DOWN     = 'F';
	static const int CAM_CONTROL_ENABLECLICK = VK_LBUTTON;
#pragma endregion

	Q_OBJECT;

	glm::mat4 viewTransform;
	QTimer updateTimer;
	Timer gameTimer;
	float dt;
	float maxDT;

protected:
	DebugMenuManager * menu;
	Camera myCam;
	bool disableCamMovement;
	glm::mat4 additionalViewTransform; //applied after camera
	
public:
	// call when ever creating a new matrix
	void saveViewTransform(ShaderProgram * shader, const char * name);
protected:
	void setMaxDT(float max); // any DT greater than this will be truncated to this (default .02)

	virtual void nextFrame(float dt) {}
	virtual void init() {}
	virtual void preDraw() {} // called before drawing each object
	virtual void preAllDraw() {} // called before all objects are drawn
public:
	void initializeGL();
	void paintGL();
private slots:
	void nxtFrm();
public:
	virtual void mouseMoveEvent(QMouseEvent* e); // enables camera drag movement
	virtual void keyPressEvent(QKeyEvent* e) {}
	void updateCam(QKeyEvent* key = nullptr, QMouseEvent* mouse = nullptr);
	void setDebugMenu(DebugMenuManager * menu);
};