#include <Engine\Renderer\Renderable.h>

void Renderable::init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID) {
	this->whatGeo   = whatGeo;
	this->howShader = howShader;
	this->visible   = visible;
	this->textureID = textureID;
	numUniformParameters = 0;
}
void Renderable::reset() {
	numUniformParameters = 0;
}

void Renderable::addUniformParameter(const char * name, ParameterType parameterType, const float * value) {
	uniformParameters[numUniformParameters++].init(howShader,name,parameterType,value);
}
void Renderable::addUniformParameter(const char * name, ParameterType parameterType, const int * value) {
	uniformParameters[numUniformParameters++].init(howShader,name,parameterType,value);
}
void Renderable::saveWhereMat(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_MAT4,reinterpret_cast<float*>(&whereMat[0]));
}
void Renderable::saveTexture(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_TEXTURE,reinterpret_cast<int*>(&textureID));
}
void Renderable::saveVisable(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_BOOLEAN,reinterpret_cast<int*>(&visible));
}

void Renderable::passUniformsDownDown() {
	for (uint i = 0; i < numUniformParameters; i++)
	{
		uniformParameters[i].sendData();
	}
}