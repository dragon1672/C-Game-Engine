#include <GL/glew.h>
#include <Engine\WidgetRenderer.h>
#include "glm/gtx/transform.hpp"

#pragma region shaderCode
const char * defaultVertShader = "#version 400"
	"																"
	"in layout(location=0) vec3 pos;								"
	"in layout(location=1) vec3 col;								"
	"in layout(location=3) vec2 uv;									"
	"																"
	"out vec2 outUv;												"
	"out vec3 outCol;												"
	"																"
	"//mats															"
	"uniform mat4x4 viewTransform;									"
	"uniform mat4x4 model2WorldTransform;							" // save where matrix as "model2WorldTransform"
	"																"
	"void main() {													"
	"	vec4 transformedPos =  model2WorldTransform * vec4(pos,1);  "
	"	gl_Position =  viewTransform * transformedPos;				"
	"	outUv = uv;													"
	"	outCol = col;												"
	"}"
	"";
const char * defaultFragShader = "#version 400"
	"													   "
	"//PassThrough FragShader							   "
	"													   "
	"in vec2 outUv;										   "
	"in vec3 outCol;									   "
	"													   "
	"uniform sampler2D myTexture;						   " // save texture as "myTexture"
	"													   "
	"void main() {										   "
	"	gl_FragColor = outCol * texture(myTexture, outUv); "
	"}													   "
	"";
#pragma endregion

void WidgetRenderer::initializeGL() {
	glewInit();
	Renderer::init();

	setMouseTracking(true);
	
	//setting up default shader
	bool win = mainShader->addProgram_srcCode(defaultVertShader,GL_VERTEX_SHADER);
	assert(win);
	win = mainShader->addProgram_srcCode(defaultVertShader,GL_FRAGMENT_SHADER);
	assert(win);
	mainShader->linkAndRun();
	mainShader->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);
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