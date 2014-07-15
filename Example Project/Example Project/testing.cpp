//*
#include "testing.h"
#include <Engine\Tools\NUShapeEditor.h>
#include <noise\noise.h>

void Testing::init() {
	myCam.lookAt(glm::vec3(0,2,1),glm::vec3(0,0,0));
	myCam.MOVEMENT_SPEED *= .5;


	auto meShader = addShader("./../shaders/PassThroughV.glsl","./../shaders/PassThroughF.glsl");
	saveViewTransform(meShader,"viewTransform");

	auto meGeo = addGeometry(Neumont::ShapeGenerator::makePlane(2),GL_TRIANGLES);

	noise::module::Perlin myModule;
	myModule.SetOctaveCount(20);
	//myModule.SetFrequency(1.0);

	double ds[5];
	for (int i = 0; i < sizeof(ds) / sizeof(*ds); i++)
	{
		ds[i] = myModule.GetValue(i,i,i);
	}

	const uint BYTES_PER_COLOR = 4;
	const uint width  = 200;
	const uint height = 200;
	GLubyte * meTexture = new GLubyte[BYTES_PER_COLOR * width * height];
	for (int row= 0; row < height; row++)
	{
		for (int col= 0; col < width; col++) {
			float x = (float)row / height;
			float y = (float)col / width;
			float val = myModule.GetValue(x,y,0);
			meTexture[row * width * BYTES_PER_COLOR + col*BYTES_PER_COLOR] = (val+1) / 2 * 0xFF;
		}
	}

	int textureID = addTexture(meTexture,width,height);


	auto meRenderable = addRenderable(meGeo,meShader,textureID);
	meRenderable->saveTexture("myTexture");
	meRenderable->saveMatrixInfo("model2WorldTransform");
}
	
void Testing::nextFrame(float dt) {

}
//*/