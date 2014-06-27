#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>

void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type) {
	this->title = name;
	theProg = prog;
	this->type = type;
	cashedInt = nullptr;
	cashedFloat = nullptr;
	cashedBool = nullptr;
}
void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type, const int * val) {
	init(prog,name,type);
	cashedInt = val;
	sendData(val);
}
void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type, const bool * val) {
	init(prog,name,type);
	cashedBool = val;
	sendData(val);
}
void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type, const float * val) {
	init(prog,name,type);
	cashedFloat = val;
	sendData();
}

void ShaderUniformPram::sendData() {
	if(cashedInt!=nullptr)   sendData(cashedInt);
	if(cashedFloat!=nullptr) sendData(cashedFloat);
	if(cashedBool!=nullptr) sendData(cashedBool);
}
void ShaderUniformPram::sendData(const int * val) {
	theProg->passUniform(title,type,*val);
}
void ShaderUniformPram::sendData(const bool * val) {
	theProg->passUniform(title,type,*val);
}
void ShaderUniformPram::sendData(const float * val) {
	theProg->passUniform(title,type,val);
}