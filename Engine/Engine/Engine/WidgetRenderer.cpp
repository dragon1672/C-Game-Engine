#include <GL/glew.h>
#include <Engine\WidgetRenderer.h>
#include "glm/gtx/transform.hpp"
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>

#pragma region shaderCode
const char * defaultVertShader = "#version 400                      \n"
	"																\n"
	"in layout(location=0) vec3 pos;								\n"
	"in layout(location=1) vec3 col;								\n"
	"in layout(location=3) vec2 uv;									\n"
	"																\n"
	"out vec2 outUv;												\n"
	"out vec3 outCol;												\n"
	"																\n"
	"//mats															\n"
	"uniform mat4x4 viewTransform;									\n"
	"uniform mat4x4 model2WorldTransform;							\n"
	"																\n"
	"void main() {													\n"
	"	vec4 transformedPos =  model2WorldTransform * vec4(pos,1);  \n"
	"	gl_Position =  viewTransform * transformedPos;				\n"
	"	outUv = uv;													\n"
	"	outCol = col;												\n"
	"}"
	"";
const char * defaultFragShader = "#version 400             \n"
	"													   \n"
	"in vec2 outUv;										   \n"
	"in vec3 outCol;									   \n"
	"													   \n"
	"uniform sampler2D myTexture;						   \n"
	"													   \n"
	"void main() {										   \n"
	"	gl_FragColor = vec4(outCol,1);// * texture(myTexture, outUv); \n"
	"	//gl_FragColor = vec4(.5,.5,.5,1); \n"
	"}													   \n"
	"";
#pragma endregion

void WidgetRenderer::initializeGL() {
	glewInit();

	disableCamMovement = false;
	maxDT = .02;

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc (GL_ONE, GL_ONE);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	connect(&updateTimer,SIGNAL(timeout()),this,SLOT(nxtFrm()));
	updateTimer.start(0);
	gameTimer.start();

	Renderer::init();

	setMouseTracking(true);

	//setting up default shader
	bool noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultVertShader,GL_VERTEX_SHADER);	assert(noDefaultShaderErrors);
		 noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultFragShader,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	
	mainShader->linkAndRun();
	mainShader->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	init();
}
float min(float a, float b) {
	return a > b ? b : a;
}
void WidgetRenderer::nxtFrm() {
	dt = min(gameTimer.interval(),maxDT);
	
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_FORWARD ) !=0 ) { myCam.moveForward();  }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_BACKWARD) !=0 ) { myCam.moveBackward(); }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_LEFT    ) !=0 ) { myCam.moveLeft();     }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_RIGHT   ) !=0 ) { myCam.moveRight();    }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_UP      ) !=0 ) { myCam.moveUp();       }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_DOWN    ) !=0 ) { myCam.moveDown();     }

	nextFrame(dt);
	repaint();
}
void WidgetRenderer::saveViewTransform(ShaderProgram * shader, const char * name) {
	shader->saveUniform(name,ParameterType::PT_MAT4,&viewTransform[0][0]);
}

void WidgetRenderer::paintGL() {
	glViewport(0,0,width(),height());
	glClearColor(.1f,.1f,.1f,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const float aspectRatio = (float)width()/(float)height();
	viewTransform = glm::mat4();
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();
	viewTransform *= additionalViewTransform;

	resetAllShaders_validPush();
	
	preAllDraw();
	
	for (uint i = 0; i < numOfRenderables; i++)
	{
		draw(myRenderables[i]);
	}
}

void WidgetRenderer::mouseMoveEvent(QMouseEvent* e) {
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_ENABLECLICK)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}
void WidgetRenderer::setDebugMenu(DebugMenuManager * menu) {
	this->menu = menu;
}