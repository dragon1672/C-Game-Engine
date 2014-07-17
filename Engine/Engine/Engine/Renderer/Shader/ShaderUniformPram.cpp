#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>

void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type) {
	this->title = name;
	theProg = prog;
	this->type = type;
	cashedPointer = nullptr;
}
void ShaderUniformPram::init(ShaderProgram * prog, const char * name, ParameterType type, const void * val) {
	init(prog,name,type);
	cashedPointer = val;
	sendData(val);
}

void ShaderUniformPram::sendData() {
	if(cashedPointer!=nullptr)   sendData(cashedPointer);
}
void ShaderUniformPram::sendData(const void * val) {
	theProg->passUniform(title,type,val);
}