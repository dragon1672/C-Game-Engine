#include "testing.h"

Neumont::Vertex stackVerts[] = 
{
	// Top
	glm::vec3(-1.0f, +1.0f, +1.0f), // 0
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, +1.0f), // 1
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, -1.0f), // 2
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, -1.0f), // 3
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	
	// Front
	glm::vec3(-1.0f, +1.0f, -1.0f), // 4
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, -1.0f), // 5
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, -1.0f), // 6
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 7
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	
	// Right
	glm::vec3(+1.0f, +1.0f, -1.0f), // 8
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(+1.0f, +1.0f, +1.0f), // 9
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 10
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, -1.0f), // 11
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Left
	glm::vec3(-1.0f, +1.0f, +1.0f), // 12
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, -1.0f), // 13
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 14
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 15
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Back
	glm::vec3(+1.0f, +1.0f, +1.0f), // 16
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, +1.0f), // 17
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 18
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 19
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Bottom
	glm::vec3(+1.0f, -1.0f, -1.0f), // 20
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 21
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 22
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 23
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
};
unsigned short stackIndices[] = {
	0,  1,  2,  0,  2,  3, // Top
	4,  5,  6,  4,  6,  7, // Front
	8,  9,  10, 8,  10, 11, // Right 
	12, 13, 14, 12, 14, 15, // Left
	16, 17, 18, 16, 18, 19, // Back
	20, 22, 21, 20, 23, 22, // Bottom
};

Neumont::ShapeData makeCube() {
	Neumont::ShapeData ret;
	ret.verts = stackVerts;
	ret.numVerts = sizeof(stackVerts) / sizeof(*stackVerts);

	ret.indices = stackIndices;
	ret.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
	return ret;
}

void Testing::init() {
	myCam.lookAt(glm::vec3(0,.1,10),glm::vec3(0,0,0));

	specPower = 100;
	lightColor = glm::vec3(1,1,1);

	whiteAsTexture = false;

	auto meGeo =  addGeometry(NUShapeEditor::scale(makeCube(),5),GL_TRIANGLES);
	auto cameraGeo = addGeometry(Neumont::ShapeGenerator::makeSphere(50),GL_TRIANGLES);

	lightSrcRenderable = addRenderable(cameraGeo,mainShader,-1);
	lightSrcRenderable->saveMatrixInfo("model2WorldTransform");

	ShaderProgram * meShader = addShader("./../shaders/tanNormal_V.glsl","./../shaders/tanNormal_F.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("diffusePos",   ParameterType::PT_VEC3, &lightSrcRenderable->transformData.position[0]         );
	meShader->saveUniform("lightColor", ParameterType::PT_VEC3, &lightColor[0]         );
	meShader->saveUniform("camPos",     ParameterType::PT_VEC3, &myCam.getPos()[0]     );
	meShader->saveUniform("specPower",  ParameterType::PT_FLOAT, &specPower            );
	meShader->saveUniform("whiteAsTexture", ParameterType::PT_BOOLEAN, &whiteAsTexture );
		
	meCube = addRenderable(meGeo,meShader,addTexture("./../textures/basicNormal.png",false,true));
	meCube->saveTexture("normalMap");
	meCube->saveMatrixInfo("model2WorldTransform");
	meCube->addUniformParameter("modelRotation", cubeRotation );
	
	menu->setDefaultTab("cheese");
	menu->edit("lightPosition",lightSrcRenderable->transformData.position,-20,20);
	//menu->edit("lightColor",lightColor,0,1);
	//menu->edit("specPower",specPower,3,100);
	menu->edit("Cube Rot:",meCube->transformData.rotation,-360,360);
	menu->setDefaultTab("pie");
	menu->edit("showLightSrc",lightSrcRenderable->visible);
	menu->edit("whiteAsTexture",whiteAsTexture);

	lightSrcRenderable->transformData.position = glm::vec3(0,10,0); // debug menu is corrupting data ?!?
	lightSrcRenderable->transformData.scale = glm::vec3(.2,.2,.2);
}
	
void Testing::nextFrame(float dt) {
	static float time = 0;
	time += dt;
	if(time > 2) {
		time -= 2;
		if(menu->isActiveTab("pie"))
			menu->setActiveTab("cheese");
		else
			menu->setActiveTab("pie");
	}
	cubeRotation = meCube->transformData.genRotMat();

}