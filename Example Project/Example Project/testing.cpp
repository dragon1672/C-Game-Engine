//*
#include "testing.h"
#include <Engine\Tools\NUShapeEditor.h>
#include <noise\noise.h>
#include <Engine\Tools\Random\MyRandom.h>

int genTexture(Renderer * renderer) {
	noise::module::Perlin myModuleR;
	noise::module::Perlin myModuleG;
	noise::module::Perlin myModuleB;
	noise::module::Perlin myModuleA;
	myModuleR.SetOctaveCount(1);
	myModuleG.SetOctaveCount(2);
	myModuleB.SetOctaveCount(3);
	myModuleA.SetOctaveCount(4);

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
			float valR = myModuleR.GetValue(x,y,zVal);
			float valG = myModuleG.GetValue(x,y,zVal);
			float valB = myModuleB.GetValue(x,y,zVal);
			float valA = myModuleA.GetValue(x,y,zVal);
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
	myCam.lookAt(glm::vec3(0,2,1),glm::vec3(0,0,0));
	myCam.MOVEMENT_SPEED *= .1;


	ShaderProgram * meShader = addShader("./../shaders/NoiseMapDemoV.glsl","./../shaders/NoiseMapDemoF.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("layer",ParameterType::PT_FLOAT,&layer);

	auto meGeo = addGeometry(Neumont::ShapeGenerator::makePlane(2),GL_TRIANGLES);

	int textureID = genTexture(this);

	auto meRenderable = addRenderable(meGeo,meShader,textureID);
	meRenderable->saveTexture("myTexture");
	meRenderable->saveMatrixInfo("model2WorldTransform");

	menu->edit("OctaveCount: ",layer,1,4);
}
	
void Testing::nextFrame(float dt) {

}
//*/