//*
#include "testing.h"
#include <Engine\Tools\NUShapeEditor.h>

#pragma region cube
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
#pragma endregion

void Testing::init() {
	myCam.lookAt(glm::vec3(0,.1,10),glm::vec3(0,0,0));

	specPower = 100;
	lightColor = glm::vec3(1,1,1);
	
	
	showTexture = true;
	useNormalMap = true;
	useOcclusion = false;

	auto meGeo =  addGeometry(NUShapeEditor::overrideColorWithTanNormals(BinaryToShapeLoader::loadFromFile("./../models/Ogre.bin")),GL_TRIANGLES);
	auto cameraGeo = addGeometry(Neumont::ShapeGenerator::makeSphere(50),GL_TRIANGLES);

	lightSrcRenderable = addRenderable(cameraGeo,mainShader,-1);
	lightSrcRenderable->saveMatrixInfo("model2WorldTransform");

	ShaderProgram * meShader = addShader("./../shaders/tanNormal_V.glsl","./../shaders/tanNormal_orge_F.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("diffusePos",     ParameterType::PT_VEC3, &lightSrcRenderable->transformData.position[0]         );
	meShader->saveUniform("lightColor",     ParameterType::PT_VEC3, &lightColor[0]     );
	meShader->saveUniform("camPos",         ParameterType::PT_VEC3, &myCam.getPos()[0] );
	meShader->saveUniform("specPower",      ParameterType::PT_FLOAT, &specPower        );
	meShader->saveUniform("showTexture",    ParameterType::PT_BOOLEAN, &showTexture    );
	meShader->saveUniform("useNormal",      ParameterType::PT_BOOLEAN, &useNormalMap   );
	meShader->saveUniform("useOcc",         ParameterType::PT_BOOLEAN, &useOcclusion   );
		
	normalMap = addTexture("./../textures/ogre_normalmap.png");
	occlusionmap = addTexture("./../textures/ao_ears.png");

	meOrge = addRenderable(meGeo,meShader,addTexture("./../textures/ogre_diffuse.png"));
	meOrge->saveMatrixInfo("model2WorldTransform");
	meOrge->saveTexture("diffuseMap");
	meOrge->addUniformParameter("normalMap",     ParameterType::PT_TEXTURE,&normalMap);
	meOrge->addUniformParameter("occMap",        ParameterType::PT_TEXTURE,&occlusionmap);
	meOrge->addUniformParameter("modelRotation", headRotation );

	meOrge->transformData.scale = glm::vec3(7,7,7);
	
	menu->edit("lightPosition",lightSrcRenderable->transformData.position,-20,20);
	menu->edit("Cube Rot:",meOrge->transformData.rotation,-360,360);
	menu->edit("showLightSrc",lightSrcRenderable->visible);
	menu->edit("normMap",useNormalMap);
	menu->edit("occMap",useOcclusion);
	menu->edit("diffuse",showTexture);

	lightSrcRenderable->transformData.position = glm::vec3(0,4,9.5); // debug menu is corrupting data ?!?
	lightSrcRenderable->transformData.scale = glm::vec3(.2,.2,.2);
}
	
void Testing::nextFrame(float dt) {
	headRotation = meOrge->transformData.genRotMat();
}
//*/