#include "DebugShapeManager.h"
#ifdef _DEBUG
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <ShapeData.h>
#include <ShapeGenerator.h>
#include "NUShapeEditor.h"

glm::vec3 DebugShapeManager::UP(0,1,0);
void      DebugShapeManager::init(float * viewMatrix) {
	myRenderer.init();
	this->viewMatrix = viewMatrix;

	//makin some shapes
	Neumont::ShapeData NUSphere = NUShapeEditor::scaleToRange(NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makeSphere(15)));
	Neumont::ShapeData NUCube   = NUShapeEditor::scaleToRange(NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makeCube()));
	Neumont::ShapeData NULine;
	
	NULine.numVerts = 2;
	NULine.numIndices = 2;
	NULine.verts = new Neumont::Vertex[NULine.numVerts];
	NULine.indices = new ushort[NULine.numIndices];
	NULine.indices[0] = 0;
	NULine.verts  [0].color    = glm::vec4(1,1,1,1);
	NULine.verts  [0].position = glm::vec3(0,0,0);
	NULine.verts  [1].position = UP;
	NULine.verts  [1].color    = glm::vec4(2,2,2,2); // lighter tip
	NULine.indices[1] = 1;

	Neumont::ShapeData NUPoint;
	NUPoint.numVerts = 6;
	NUPoint.numIndices = 6;
	NUPoint.verts = new Neumont::Vertex[NUPoint.numVerts];
	NUPoint.indices = new ushort[NUPoint.numIndices];
	//R
	NUPoint.indices[0] = 0;
	NUPoint.verts  [0].color    = glm::vec4(+1,0,0,0); // r
	NUPoint.verts  [0].position = glm::vec3(+1,0,0);
	NUPoint.verts  [1].position = glm::vec3(-1,0,0);
	NUPoint.verts  [1].color    = glm::vec4(+0,0,0,0);
	NUPoint.indices[1] = 1;
	//G
	NUPoint.indices[2] = 2;
	NUPoint.verts  [2].color    = glm::vec4(0,+1,0,0); // g
	NUPoint.verts  [2].position =  UP;
	NUPoint.verts  [3].position = -UP;
	NUPoint.verts  [3].color    = glm::vec4(0,+0,0,0);
	NUPoint.indices[3] = 3;
	//B
	NUPoint.indices[4] = 4;
	NUPoint.verts  [4].color    = glm::vec4(0,0,+1,0); // b
	NUPoint.verts  [4].position = glm::vec3(0,0,+1);
	NUPoint.verts  [5].position = glm::vec3(0,0,-1);
	NUPoint.verts  [5].color    = glm::vec4(0,0,+0,0);
	NUPoint.indices[5] = 5;

	
	//send data down
	GEO_sphere = myRenderer.addGeometry(NUSphere,GL_TRIANGLES);
	GEO_sphere->NU_VertexStreamedPosition(0);
	GEO_sphere->NU_VertexStreamedColor(1);
	GEO_cube   = myRenderer.addGeometry(NUCube,  GL_TRIANGLES);
	GEO_cube->NU_VertexStreamedPosition(0);
	GEO_cube->NU_VertexStreamedColor(1);
	GEO_line   = myRenderer.addGeometry(NULine,  GL_LINES);
	GEO_line->NU_VertexStreamedPosition(0);
	GEO_line->NU_VertexStreamedColor(1);
#ifdef useArrowForVec
	this->GEO_vector = myRenderer.addGeometry(NUShapeEditor::scaleToRange(NUShapeEditor::noNegY(NUShapeEditor::rotate(Neumont::ShapeGenerator::makeArrow(),90,0,0))),GL_TRIANGLES);
	GEO_vector->NU_VertexStreamedPosition(0);
	GEO_vector->NU_VertexStreamedColor(1);
#else
	GEO_vector = GEO_line;
#endif
	GEO_point  = myRenderer.addGeometry(NUPoint, GL_LINES);
	GEO_point->NU_VertexStreamedPosition(0);
	GEO_point->NU_VertexStreamedColor(1);

	initShaders();
}
void      DebugShapeManager::initShaders() {
	debugShapeShader = myRenderer.addShader("../Shaders/PassThroughVertexShader.glsl","../Shaders/PassThroughFragShader.glsl");
	debugShapeShader->saveUniform("viewTransform",ParameterType::PT_MAT4,viewMatrix);
}
DebugShapeManager::DebugShapeData * DebugShapeManager::addUnitSphere(glm::mat4& transform,                    glm::vec4& color, float lifetime, bool depthTest) {
	DebugShapeData * toAdd = new DebugShapeData();
	toAdd->whatGeo = GEO_sphere;
	toAdd->transform = transform;
	toAdd->overrideColor = color;
	toAdd->lifetime = lifetime;
	toAdd->ignoreDepthTest = !depthTest;
	toAdd->enableOverrideColor = false;
	toAdd->init(debugShapeShader);
	shapes.push_back(toAdd);
	return toAdd;
}
DebugShapeManager::DebugShapeData * DebugShapeManager::addUnitCube  (glm::mat4& transform,                    glm::vec4& color, float lifetime, bool depthTest) {
	DebugShapeData * toAdd = new DebugShapeData();
	toAdd->whatGeo = GEO_cube;
	toAdd->transform = transform;
	toAdd->overrideColor = color;
	toAdd->lifetime = lifetime;
	toAdd->ignoreDepthTest = !depthTest;
	toAdd->enableOverrideColor = false;
	toAdd->init(debugShapeShader);
	shapes.push_back(toAdd);
	return toAdd;
}
DebugShapeManager::DebugShapeData * DebugShapeManager::addUnitVector(glm::vec3& tail,      glm::vec3& vector, glm::vec4& color, float lifetime, bool depthTest) {
	DebugShapeData * toAdd = new DebugShapeData();
	toAdd->whatGeo = GEO_vector;
	toAdd->transform = span2Points(tail, tail + vector);
	toAdd->overrideColor = color;
	toAdd->lifetime = lifetime;
	toAdd->ignoreDepthTest = !depthTest;
	toAdd->enableOverrideColor = false;
	toAdd->init(debugShapeShader);
	shapes.push_back(toAdd);
	return toAdd;
}
DebugShapeManager::DebugShapeData * DebugShapeManager::addLine      (glm::vec3& start,     glm::vec3& end,    glm::vec4& color, float lifetime, bool depthTest) {
	DebugShapeData * toAdd = new DebugShapeData();
	toAdd->whatGeo = GEO_line;
	toAdd->transform = span2Points(start, end);
	toAdd->overrideColor = color;
	toAdd->lifetime = lifetime;
	toAdd->ignoreDepthTest = !depthTest;
	toAdd->enableOverrideColor = true;
	toAdd->init(debugShapeShader);
	shapes.push_back(toAdd);
	return toAdd;
}
DebugShapeManager::DebugShapeData * DebugShapeManager::addPoint     (glm::vec3& pos,                                            float lifetime, bool depthTest) {
	DebugShapeData * toAdd = new DebugShapeData();
	toAdd->whatGeo = GEO_point;
	toAdd->transform = glm::translate(pos);
	toAdd->overrideColor = glm::vec4(1,1,1,1);
	toAdd->lifetime = lifetime;
	toAdd->ignoreDepthTest = !depthTest;
	toAdd->enableOverrideColor = false;
	toAdd->init(debugShapeShader);
	shapes.push_back(toAdd);
	return toAdd;
}
glm::vec3 DebugShapeManager::noZeros(glm::vec3 vec) {
	for (int i = 0; i < 3; i++)
	{
		vec[i] = vec[i] == 0 ? .00000001f : vec[i];
	}
	return vec;
}
glm::mat4 DebugShapeManager::span2Points(glm::vec3 start, glm::vec3 end) {
	glm::vec3 tail = start;
	glm::vec3 newUp = glm::normalize(end - start);
	float scale = glm::length(end - start);

	glm::mat4 ret = glm::translate(tail);
	ret *= glm::orientation(newUp,UP);
	ret *= glm::scale(glm::vec3(1,scale,1));

	return ret;
}
void      DebugShapeManager::update(float dt) {
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->lifetime -= dt;
		if(shapes[i]->lifetime<0) {
			delete shapes[i];
			shapes.erase(shapes.begin()+i--);
		}
	}
}
void      DebugShapeManager::draw() {
	debugShapeShader -> useProgram();
	debugShapeShader -> passSavedUniforms_force();
	for (unsigned int i = 0; i < shapes.size(); i++) {
		if(shapes[i]->draw) {
			for (unsigned int j = 0; j < shapes[i]->prams.size(); j++) {
				shapes[i]->prams[j].sendData();
			}
			myRenderer.draw(*(shapes[i]->whatGeo));
		}
	}
}
#endif