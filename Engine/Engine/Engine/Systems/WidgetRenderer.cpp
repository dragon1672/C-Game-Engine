#include <GL/glew.h>
#include <Engine\Systems\WidgetRenderer.h>
#include "glm/gtx/transform.hpp"
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>

#pragma region shaderCode
const char * defaultVertShader = "#version 400					  \n"
	"															  \n"
	"in layout(location=0) vec3 pos;							  \n"
	"in layout(location=1) vec3 col;							  \n"
	"in layout(location=3) vec2 uv;								  \n"
	"															  \n"
	"out vec2 fragUv;											  \n"
	"out vec3 fragCol;											  \n"
	"out vec3 fragPos;											  \n"
	"out vec3 fragWorldPos;										  \n"
	"															  \n"
	"//mats														  \n"
	"uniform mat4x4 viewTransform;								  \n"
	"uniform mat4x4 model2WorldTransform;						  \n"
	"															  \n"
	"void main() {												  \n"
	"	vec4 transformedPos = model2WorldTransform * vec4(pos,1); \n"
	"	gl_Position = viewTransform * transformedPos;			  \n"
	"	fragUv = uv;											  \n"
	"	fragCol = col;											  \n"
	"	fragPos = pos;											  \n"
	"	fragWorldPos = vec3(transformedPos);					  \n"
	"}															  \n"
	"															  \n";
//color
const char * defaultFragShader_Color = "#version 400\n"
	"												\n"
	"in vec3 fragCol;								\n"
	"												\n"
	"void main() {									\n"
	"	gl_FragColor = vec4(fragCol,1);				\n"
	"}												\n"
	"";
//texture
const char * defaultFragShader_Texture = "#version 400\n"
	"												  \n"
	"in vec2 fragUv;								  \n"
	"uniform sampler2D myTexture;					  \n"
	"												  \n"
	"void main() {									  \n"
	"	gl_FragColor = texture(myTexture,fragUv);	  \n"
	"}												  \n"
	"";
//Cube map withModeldPos
const char * defaultFragShader_CubeMapModel= "#version 400\n"
	"													  \n"
	"in vec3 fragPos;									  \n"
	"uniform samplerCube worldMap;						  \n"
	"													  \n"
	"void main() {										  \n"
	"	gl_FragColor = texture(worldMap,fragPos);		  \n"
	"}													  \n"
	"";
//Cube map withWorldPos
const char * defaultFragShader_CubeMapWorld = "#version 400\n"
	"													   \n"
	"in vec3 fragWorldPos;								   \n"
	"uniform samplerCube worldMap;						   \n"
	"													   \n"
	"void main() {										   \n"
	"	gl_FragColor = texture(worldMap,fragWorldPos);	   \n"
	"}													   \n"
	"													   \n";
#pragma endregion
#pragma region HUD assets



#pragma endregion

void WidgetRenderer::initializeGL() {
	glewInit();

	disableCamMovement = false;
	maxDT = .02f;
	nearPlane = .1f;
	farPlane = 200;
	oldWidth = oldHeight = -1;

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
	//ShaderProgram * passThroughColor;    // see code set A
	bool noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultVertShader,      GL_VERTEX_SHADER);		assert(noDefaultShaderErrors);
		 noDefaultShaderErrors = mainShader->addProgram_srcCode(defaultFragShader_Color,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	mainShader->linkAndRun();
	mainShader->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	defaultShaders.passThroughColor = mainShader;
	//ShaderProgram * passThroughTexture;  // see code set B
	defaultShaders.passThroughTexture = addShader();
	noDefaultShaderErrors = defaultShaders.passThroughTexture->addProgram_srcCode(defaultVertShader,        GL_VERTEX_SHADER);		assert(noDefaultShaderErrors);
	noDefaultShaderErrors = defaultShaders.passThroughTexture->addProgram_srcCode(defaultFragShader_Texture,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	defaultShaders.passThroughTexture->linkAndRun();
	defaultShaders.passThroughTexture->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);


	//ShaderProgram * passThroughCubeMap;  // see code set C
	defaultShaders.passThroughCubeMap = addShader();
	noDefaultShaderErrors = defaultShaders.passThroughCubeMap->addProgram_srcCode(defaultVertShader,             GL_VERTEX_SHADER);		assert(noDefaultShaderErrors);
	noDefaultShaderErrors = defaultShaders.passThroughCubeMap->addProgram_srcCode(defaultFragShader_CubeMapModel,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	defaultShaders.passThroughCubeMap->linkAndRun();
	defaultShaders.passThroughCubeMap->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	//ShaderProgram * passThroughWCubeMap; // see code set D
	defaultShaders.passThroughWCubeMap = addShader();
	noDefaultShaderErrors = defaultShaders.passThroughWCubeMap->addProgram_srcCode(defaultVertShader,             GL_VERTEX_SHADER);	assert(noDefaultShaderErrors);
	noDefaultShaderErrors = defaultShaders.passThroughWCubeMap->addProgram_srcCode(defaultFragShader_CubeMapWorld,GL_FRAGMENT_SHADER);	assert(noDefaultShaderErrors);
	defaultShaders.passThroughWCubeMap->linkAndRun();
	defaultShaders.passThroughWCubeMap->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

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

void WidgetRenderer::setDefaultPassInfo(PassInfo * toSet) {
	passInfo_Default = toSet;
}
void WidgetRenderer::resetDefaultPassInfoToScreen() {
	passInfo_Default = &passInfo_Screen;
}

void WidgetRenderer::saveViewTransform(ShaderProgram * shader, const char * name) {
	shader->saveUniform(name,ParameterType::PT_MAT4,&viewTransform[0][0]);
}
void WidgetRenderer::savePerspectiveMat(ShaderProgram * shader, const char * name) {
	shader->saveUniform(name,ParameterType::PT_MAT4,&perspectiveMat[0][0]);
}

void WidgetRenderer::paintGL() {
	if((oldWidth != width() || oldHeight != height())
		&& oldWidth > 0 && oldHeight > 0) {
		windowResized(oldWidth,oldHeight);
	}
	oldWidth = width();
	oldHeight = height();
	glViewport(0,0,width(),height());

	for (uint i = 0; i < passInfos.size(); i++)
	{
		if(passInfos[i]->visable) {
			resetAllShaders_validPush();
			drawPass(*passInfos[i]);
		}
	}
	drawPass(HUD,false);

	
}

void WidgetRenderer::drawPass(PassInfo& toDraw, bool clear) {
	if(toDraw.myRenderables.size() == 0) return; // no need to do more work than we have to

	toDraw.activate();
	if(clear) {
		float clearX = toDraw.clearColor.x;
		float clearY = toDraw.clearColor.y;
		float clearZ = toDraw.clearColor.z;
		glClearColor(clearX,clearY,clearZ,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	const float aspectRatio = (float)width()/(float)height();
	perspectiveMat = glm::perspective(60.0f,aspectRatio,nearPlane,farPlane);
	viewTransform = perspectiveMat;
	viewTransform *= toDraw.cam.enabled ? toDraw.cam.getWorld2View() : myCam.getWorld2View();
	viewTransform *= additionalViewTransform;
	
	preAllDraw();
		
	for (uint j = 0; j < toDraw.myRenderables.size(); j++)
	{
		draw(*toDraw.myRenderables[j]);
	}
}

void WidgetRenderer::mouseMoveEvent(QMouseEvent* e) {
	if(!disableCamMovement && GetAsyncKeyState(CAM_CONTROL_ENABLECLICK)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}
void WidgetRenderer::wheelEvent(QWheelEvent* e) {
	int delta = e->delta();
	const int increment = 75;
	float percent = .1f;
	for (int i = 0; i < delta; i++)
	{
		myCam.moveForward(percent / increment);
	}
	for (int i = 0; i > delta; i--)
	{
		myCam.moveBackward(percent / increment);
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