//*
#include "testing.h"
#include <Engine\Tools\NUShapeEditor.h>
#include <noise\noise.h>

int genTexture(Renderer * renderer) {
	noise::module::Perlin myModule;

	const uint BYTES_PER_COLOR = 4;
	const uint width  = 256;
	const uint height = 256;
	const int zVal = 20;
	GLubyte * meTexture = new GLubyte[BYTES_PER_COLOR * width * height];
	for (int row= 0; row < height; row++)
	{
		for (int col= 0; col < width; col++) {
			float x = (float)row / height;
			float y = (float)col / width;
			myModule.SetOctaveCount(1);	float valR = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(2);	float valG = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(3);	float valB = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(4);	float valA = myModule.GetValue(x,y,zVal);
			GLubyte * textureStart = &meTexture[row * width * BYTES_PER_COLOR + col*BYTES_PER_COLOR];
			
			textureStart[0] = (valR+1) / 2 * 0xFF;	// R
			textureStart[1] = (valG+1) / 2 * 0xFF;	// G
			textureStart[2] = (valB+1) / 2 * 0xFF;	// B
			textureStart[3] = (valA+1) / 2 * 0xFF;	// A
		}
	}
	return renderer->addTexture(meTexture,width,height);
}

void Testing::init() {
	//myCam.lookAt(glm::vec3(0,2,1),glm::vec3(0,0,0));
	myCam.setPos(glm::vec3(-.5,1,.5), glm::vec3(0,-1,-.3));
	myCam.MOVEMENT_SPEED *= .1;

	layer = 1;
	updateRate = 2;

	ShaderProgram * meShader = addShader("./../shaders/NoiseMapDemoV.glsl","./../shaders/NoiseMapDemoF.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("layer",ParameterType::PT_FLOAT,&layer);
	meShader->saveUniform("baseColor", ParameterType::PT_VEC3,&color[0]);

	auto meGeo = addGeometry(Neumont::ShapeGenerator::makePlane(2),GL_TRIANGLES);

	int textureID = genTexture(this);

	auto meRenderable = addRenderable(meGeo,meShader,textureID);
	meRenderable->saveTexture("myTexture");
	meRenderable->saveMatrixInfo("model2WorldTransform");
	 
	menu->edit("OctaveCount: ",layer,1,4);
	menu->edit("UpdateRate: ",updateRate,0,3);
	menu->watch("Color: ",color);
}
	
void Testing::nextFrame(float dt) {
	static float timePassed = -1;
	timePassed += dt;
	if(timePassed > updateRate || timePassed < 0) {
		timePassed = timePassed < 0 ? 0 : timePassed-updateRate;
		color = Random::glmRand::randomFloatVectorInBox(1,1,1);
	}
}
//*/