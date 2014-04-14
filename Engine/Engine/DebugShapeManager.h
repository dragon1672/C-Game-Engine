#pragma once

#include "ExportHeader.h"

#include "Renderer.h"
#include <glm\glm.hpp>
#include <vector>
#include <limits>


#define useArrowForVec

typedef unsigned short ushort;

class ENGINE_SHARED DebugShapeManager {
#ifdef _DEBUG
private:
	static glm::vec3 UP;
public:
	struct DebugShapeData {
		GeometryInfo * whatGeo;
		glm::mat4 transform;
		glm::vec4 overrideColor;
		float lifetime;
		bool ignoreDepthTest;
		bool enableOverrideColor;
		std::vector<ShaderUniformPram> prams;
		bool draw;
		inline void kill() {
			draw = false;
			lifetime = -1;
		}
		inline void init(ShaderProgram * theOne) {
			draw = true;
			ShaderUniformPram toAdd;
			toAdd.init(theOne,"model2WorldTransform",	ParameterType::PT_MAT4,&transform[0][0]);			prams.push_back(toAdd);
			toAdd.init(theOne,"overrideColor",			ParameterType::PT_VEC4,&overrideColor[0]);			prams.push_back(toAdd);
			toAdd.init(theOne,"ignoreDepthTest",		ParameterType::PT_BOOLEAN,&ignoreDepthTest);		prams.push_back(toAdd);
			toAdd.init(theOne,"enableOverrideColor",	ParameterType::PT_BOOLEAN,&enableOverrideColor);	prams.push_back(toAdd);
		}
	};
private:
	std::vector<DebugShapeData *> shapes;

	Renderer        myRenderer;
	float         * viewMatrix;
	ShaderProgram * debugShapeShader;
	GeometryInfo  * GEO_sphere;
	GeometryInfo  * GEO_cube;
	GeometryInfo  * GEO_vector;
	GeometryInfo  * GEO_line;
	GeometryInfo  * GEO_point;

	glm::vec3 noZeros(glm::vec3 vec);
	glm::mat4 span2Points(glm::vec3 start, glm::vec3 end, float offset);
public:
	void init(float * viewMatrix);

	void initShaders();

	DebugShapeData * addUnitSphere(glm::mat4& transform,                    glm::vec4& color,                   float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true);
	DebugShapeData * addUnitCube  (glm::mat4& transform,                    glm::vec4& color,                   float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true);
	DebugShapeData * addLine      (glm::vec3& start,     glm::vec3& end,    glm::vec4& color, float offset = 0, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true);
	DebugShapeData * addUnitVector(glm::vec3& tail,      glm::vec3& vector, glm::vec4& color, float offset = 0, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true);
	DebugShapeData * addPoint     (glm::vec3& pos,                                                              float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true);
	
	void update(float dt);

	void draw();
#else
	public:
	void init(float * viewMatrix) {}

	void initShaders();

	void addUnitSphere(glm::mat4& transform,                    glm::vec4& color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {}
	void addUnitCube  (glm::mat4& transform,                    glm::vec4& color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {}
	void addUnitVector(glm::vec3& tail,      glm::vec3& vector, glm::vec4& color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {}
	void addLine      (glm::vec3& start,     glm::vec3& end,    glm::vec4& color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {}
	void addPoint     (glm::vec3& pos,                                            float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {}
public:
	
	void update(float dt) {}

	void draw() {}
#endif
};