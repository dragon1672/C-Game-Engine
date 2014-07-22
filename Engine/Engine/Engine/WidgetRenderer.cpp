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
//color
const char * defaultFragShader_Color = "#version 400       \n"
	"													   \n"
	"in vec3 outCol;									   \n"
	"													   \n"
	"void main() {										   \n"
	"	gl_FragColor = vec4(outCol,1);                     \n"
	"}													   \n"
	"";
//texture
const char * defaultFragShader_Texture = "#version 400     \n"
	"													   \n"
	"in vec2 outUv;										   \n"
	"uniform sampler2D myTexture;                          \n"
	"													   \n"
	"void main() {										   \n"
	"	gl_FragColor = vec4(1,1,1,1);                      \n"
	"	gl_FragColor = texture(myTexture,outUv);           \n"
	"	gl_FragColor.a = 1;                                \n"
	"}													   \n"
	"";
#pragma endregion

void WidgetRenderer::initializeGL() {
	glewInit();

	disableCamMovement = false;
	maxDT = .02;
	nearPlane = .1f;
	farPlane = 200;

	passInfos.push_back(&passInfo_Screen);
	passInfo_Default = &passInfo_Screen;

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
	bool noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultVertShader,      GL_VERTEX_SHADER);		assert(noDefaultShaderErrors);
		 noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultFragShader_Color,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	mainShader->linkAndRun();
	mainShader->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	defaultShaders.passThroughColor = mainShader;
	defaultShaders.passThroughTexture = addShader();

	noDefaultShaderErrors = defaultShaders.passThroughTexture->addProgram_srcCode(defaultVertShader,        GL_VERTEX_SHADER);		assert(noDefaultShaderErrors);
	noDefaultShaderErrors = defaultShaders.passThroughTexture->addProgram_srcCode(defaultFragShader_Texture,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	defaultShaders.passThroughTexture->linkAndRun();
	defaultShaders.passThroughTexture->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	init();
}
float min(float a, float b) {
	return a > b ? b : a;
}
void WidgetRenderer::nxtFrm() {
	dt = min(gameTimer.interval(),maxDT);
	
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_FORWARD ) !=0 ) { myCam.moveForward(dt);  }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_BACKWARD) !=0 ) { myCam.moveBackward(dt); }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_LEFT    ) !=0 ) { myCam.moveLeft(dt);     }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_RIGHT   ) !=0 ) { myCam.moveRight(dt);    }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_UP      ) !=0 ) { myCam.moveUp(dt);       }
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_DOWN    ) !=0 ) { myCam.moveDown(dt);     }

	nextFrame(dt);
	repaint();
}
void WidgetRenderer::saveViewTransform(ShaderProgram * shader, const char * name) {
	shader->saveUniform(name,ParameterType::PT_MAT4,&viewTransform[0][0]);
}

void WidgetRenderer::paintGL() {
	glViewport(0,0,width(),height());

	resetAllShaders_validPush();

	for (uint i = 0; i < passInfos.size(); i++)
	{
		if(passInfos[i]->visable) {
			passInfos[i]->activate();
			float clearX = passInfos[i]->clearColor.x;
			float clearY = passInfos[i]->clearColor.y;
			float clearZ = passInfos[i]->clearColor.z;
			glClearColor(clearX,clearY,clearZ,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
			const float aspectRatio = (float)width()/(float)height();
			viewTransform = glm::mat4();
			viewTransform *= glm::perspective(60.0f,aspectRatio,nearPlane,farPlane);
			viewTransform *= passInfos[i]->cam.enabled ? passInfos[i]->cam.getWorld2View() : myCam.getWorld2View();
			viewTransform *= additionalViewTransform;
	
			preAllDraw();
		
			for (uint j = 0; j < passInfos[i]->myRenderables.size(); j++)
			{
				draw(*passInfos[i]->myRenderables[j]);
			}
		}
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


void WidgetRenderer::setMaxDT(float max) {
	this->maxDT = max;
}
Renderable* WidgetRenderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID) {
	Renderable * ret = Renderer::addRenderable(whatGeometry,howShaders,textureID);
	passInfo_Default->add(ret);
	return ret;
}
Renderable* WidgetRenderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID, PassInfo * passInfoToRegisterTo) {
	Renderable * ret = Renderer::addRenderable(whatGeometry,howShaders,textureID);
	passInfoToRegisterTo->add(ret);
	return ret;
}
Renderable* WidgetRenderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, PassInfo * passInfoToRegisterTo) {
	Renderable * ret = Renderer::addRenderable(whatGeometry,howShaders);
	passInfoToRegisterTo->add(ret);
	return ret;
}
PassInfo * WidgetRenderer::addPassInfo(bool populateWithContentsOfDefault) {
	PassInfo * ret = new PassInfo();
	passInfos.push_back(ret);
	if(populateWithContentsOfDefault) ret->loadRenderables(passInfo_Default);
	return ret;
}

WidgetRenderer::~WidgetRenderer() {
	while(passInfos.size() != 0) {
		int index = passInfos.size() - 1;
		if(passInfos[index] != &passInfo_Screen)
			delete passInfos[passInfos.size() - 1];
		passInfos.pop_back();
	}
}