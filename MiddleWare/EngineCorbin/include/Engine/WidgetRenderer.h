#pragma once

/*
         +-------------------------------------------------------+
		 | Shade Code Notes                                      |
		 +--------------------------------+----------------------+
		 | Save renderable whereMatrix as | model2WorldTransform |
		 | Save renderable texture as     | myTexture            |
		 +-------------------------------------------------------+
//*/

/* default vert shader  Part of Set { A,B }
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
	vec4 transformedPos =  model2WorldTransform * vec4(pos,1);
	gl_Position =  viewTransform * transformedPos;
	outUv = uv;
	outCol = col;
}
//*/

/* default frag shader in set { A }
#version 400

in vec3 outCol;

void main() {
	gl_FragColor = vec4(outCol,1);
}
//*/

/* default frag shader with texture in set { B }
#version 400

in vec2 outUv;
uniform sampler2D myTexture;
	
void main() {
	gl_FragColor = texture(myTexture,outUv);
}
//*/

#include <Engine\Renderer\Renderer.h>
#include <Qt/qwidget.h>
#include <Qt/qtimer.h>
#include <Engine\Tools\Camera.h>
#include <Engine\Tools\Timer.h>
#include <ExportHeader.h>
#include <Engine\DebugTools\DebugMenuManager.h>
#include <Engine\Renderer\Output\PassInfo.h>

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
	float nearPlane, farPlane;
	std::vector<PassInfo *> passInfos;
	PassInfo passInfo_Screen;
protected:
	DebugMenuManager * menu;
	Camera myCam;
	bool disableCamMovement;
	glm::mat4 additionalViewTransform; //applied after camera
	PassInfo * passInfo_Default;
public:

	struct {
		ShaderProgram * passThroughColor; // see code set A
		ShaderProgram * passThroughTexture; // see code set B
	} defaultShaders;


	void setDefaultPassInfo(PassInfo * toSet) {
		passInfo_Default = toSet;
	}
	void resetDefaultPassInfoToScreen() {
		passInfo_Default = &passInfo_Screen;
	}


	// call when ever creating a new matrix
	void saveViewTransform(ShaderProgram * shader, const char * name);
	
	// any DT greater than this will be truncated to this (default .02)
	void setMaxDT(float max);

	//if using Renderer::addRenderable(...) it will be added to the default PassInfo
	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID = -1);
	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID, PassInfo * passInfoToRegisterTo);
	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, PassInfo * passInfoToRegisterTo);

	PassInfo * addPassInfo(bool populateWithContentsOfDefault);

private: // these are the guys you want to override

	virtual void nextFrame(float dt) {}
	virtual void init() {}
	virtual void preDraw() {} // called before drawing each object
	virtual void preAllDraw() {} // called before all objects are drawn



	//Don't worry about anything down here
public:
	void initializeGL();
	void paintGL();
	~WidgetRenderer();
private slots:
	void nxtFrm();
public:
	virtual void mouseMoveEvent(QMouseEvent* e); // enables camera drag movement
	virtual void keyPressEvent(QKeyEvent* e) {}
	void updateCam(QKeyEvent* key = nullptr, QMouseEvent* mouse = nullptr);
	void setDebugMenu(DebugMenuManager * menu);
};