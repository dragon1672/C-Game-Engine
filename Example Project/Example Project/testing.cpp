//*
#include "testing.h"
#include <Engine\Tools\NUShapeEditor.h>

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