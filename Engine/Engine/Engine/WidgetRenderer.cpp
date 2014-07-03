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
void WidgetRenderer::nxtFrm() {
	dt = gameTimer.interval();
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

	for (uint i = 0; i < numOfRenderables; i++)
	{
		draw(myRenderables[i]);
	}
}

void WidgetRenderer::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_RBUTTON)!=0) {
		updateCam(nullptr,e);
	}
}
void WidgetRenderer::keyPressEvent(QKeyEvent* e) {
	updateCam(e,nullptr);
}
void WidgetRenderer::updateCam(QKeyEvent* key, QMouseEvent* mouse) {
	if(key != nullptr) {
		if(key->key() == Qt::Key::Key_W) {
			myCam.moveForward();
		} else if(key->key() == Qt::Key::Key_S) {
			myCam.moveBackward();
		} else if(key->key() == Qt::Key::Key_A) {
			myCam.moveLeft();
		} else if(key->key() == Qt::Key::Key_D) {
			myCam.moveRight();
		} else if(key->key() == Qt::Key::Key_R) {
			myCam.moveUp();
		} else if(key->key() == Qt::Key::Key_F) {
			myCam.moveDown();
		}
	}
	if(mouse!=nullptr) {
		glm::vec2 newPos(mouse->x(),mouse->y());
		myCam.updateMousePos(newPos);
	}
}
void WidgetRenderer::setDebugMenu(DebugMenuManager * menu) {
	this->menu = menu;
}