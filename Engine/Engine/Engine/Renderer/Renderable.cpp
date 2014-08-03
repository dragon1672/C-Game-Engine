#include <Engine\Renderer\Renderable.h>
#include <Qt/qdebug.h>
#include <Engine\Defines\Vectors.h>

void Renderable::init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID) {
	this->whatGeo   = whatGeo;
	this->howShader = howShader;
	this->visible   = visible;
	this->textureID = textureID;
}
Renderable::~Renderable() {
	reset();
}
void Renderable::reset() {
	CLEAR_VECTOR(uniformParameters);
}
void Renderable::addUniformParameter(const char * name, const bool& value) {
	addUniformParameter(name,ParameterType::PT_BOOLEAN,&value);
}
void Renderable::addUniformParameter(const char * name, const float& value) {
	addUniformParameter(name,ParameterType::PT_FLOAT,&value);
}
void Renderable::addUniformParameter(const char * name, const glm::vec3& value) {
	addUniformParameter(name,ParameterType::PT_VEC3,&value[0]);
}
void Renderable::addUniformParameter(const char * name, const glm::vec4& value) {
	addUniformParameter(name,ParameterType::PT_VEC4,&value[0]);
}
void Renderable::addUniformParameter(const char * name, const glm::mat3& value) {
	addUniformParameter(name,ParameterType::PT_MAT3,&value[0][0]);
}
void Renderable::addUniformParameter(const char * name, const glm::mat4& value) {
	addUniformParameter(name,ParameterType::PT_MAT4,&value[0][0]);
}
void Renderable::addUniformParameter(const char * name, ParameterType parameterType, const void * value) {
	uniformParameters.push_back(new ShaderUniformPram());
	uniformParameters[uniformParameters.size()-1]->init(howShader,name,parameterType,value);
}
void Renderable::saveMatrixInfo(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_MAT4,reinterpret_cast<float*>(&transformData.getTransform()[0]));
}
void Renderable::saveWhereMat(const char * uniformName) {
	qDebug() << " +--------------------WARNING--------------------+\n"
			 << "| You are using a deprecated transform          |\n"
			 << "| Please switch to matrix info                  |\n"
			 << "+-----------------------------------------------+";
	addUniformParameter(uniformName,ParameterType::PT_MAT4,reinterpret_cast<float*>(&whereMat[0]));
}
void Renderable::saveTexture(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_TEXTURE,reinterpret_cast<int*>(&textureID));
}
void Renderable::saveVisable(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_BOOLEAN,reinterpret_cast<int*>(&visible));
}

void Renderable::passUniformsDownDown() {
	for (uint i = 0; i < uniformParameters.size(); i++)
	{
		uniformParameters[i]->sendData();
	}
}