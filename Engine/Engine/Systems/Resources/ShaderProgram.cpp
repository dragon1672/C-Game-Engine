#include <GL\glew.h>
#include "ShaderProgram.h"
#include <fstream>
#pragma warning(disable: 4127)
#pragma warning(push)
#include <QtCore\QDebug>
#include <QtCore/QFile>
#include <QtGui/QImage>
#include <QtCore/QCoreApplication>
#pragma warning(pop)
#include <cassert>
#include <Engine\Defines\Vectors.h>
#include <Engine\Systems\Resources\TextureInfo.h>
#include <Engine/Systems/Resources/Shaders/ShaderPreProcessor.h>


GLuint ShaderProgram::currentProgram;

void ShaderProgram::buildBasicProgram(std::string vertexShaderFile, std::string fragmentShaderFile) {
	addProgram(vertexShaderFile,GL_VERTEX_SHADER);
	addProgram(fragmentShaderFile,GL_FRAGMENT_SHADER);
}
void ShaderProgram::buildBasicProgram(const char * vertexShaderFile, const char * fragmentShaderFile) {
	addProgram(vertexShaderFile,GL_VERTEX_SHADER);
	addProgram(fragmentShaderFile,GL_FRAGMENT_SHADER);
}
void ShaderProgram::addProgram(const char * shaderCode, unsigned short shaderType) {
	addProgram(std::string(shaderCode),shaderType);
}
void ShaderProgram::addProgram(std::string shaderCode, unsigned short shaderType) {
	CodeBlock newGuy;
	newGuy.code = shaderCode;
	newGuy.type = shaderType;
	files.push_back(newGuy);
}
bool ShaderProgram::compileShader(CodeBlock& block)
{
	bool isValid;
	uint id = glCreateShader(block.type);
	qDebug() << "Shader Load Successful ID: " << id;
	std::string code = ShaderPreProcessor::processGLSL(block.code);
	isValid = complileShader(code.c_str(),id,true);
	if(isValid) {
		glAttachShader(programID,id);
		qDebug() << "File(" << id << ") Compile Successful ProgramID: " << programID << "\n";
	} else {
		qDebug() << "File(" << id << ") Failed to Compile - NOT ADDED TO PROGRAM\n";
		assert(false);
	}
	return isValid;
}

int ShaderProgram::getUniform(const char* title) {
	return glGetUniformLocation(getProgramID(),title);
}
void ShaderProgram::passUniform(const char* name, ParameterType parameterType, const void * value) {
	uint location = getUniform(name);
	passUniform(location,parameterType,value);
}

#include <map>
#include <functional>
namespace {
	std::map<ParameterType,std::function<void(uint,const void *)>> makeMap() {
		std::map<ParameterType,std::function<void(uint,const void *)>> ret;
		ret[ParameterType::PT_FLOAT     ] = [](uint location,const void * value)->void{ glUniform1f(       location,         *(float*)value);                 };
		ret[ParameterType::PT_VEC2      ] = [](uint location,const void * value)->void{ glUniform2fv(      location,1,        (float*)value);                 };
		ret[ParameterType::PT_VEC3      ] = [](uint location,const void * value)->void{ glUniform3fv(      location,1,        (float*)value);                 };
		ret[ParameterType::PT_VEC4      ] = [](uint location,const void * value)->void{ glUniform4fv(      location,1,        (float*)value);                 };
		ret[ParameterType::PT_MAT3      ] = [](uint location,const void * value)->void{ glUniformMatrix3fv(location,1, false, (float*)value);                 };
		ret[ParameterType::PT_MAT4      ] = [](uint location,const void * value)->void{ glUniformMatrix4fv(location,1, false, (float*)value);                 };
		ret[ParameterType::PT_BOOLEAN   ] = [](uint location,const void * value)->void{ glUniform1i(       location,          *(bool*)value);                 };
		ret[ParameterType::PT_INT       ] = [](uint location,const void * value)->void{ glUniform1i(       location,          *(int*) value);                 };
		ret[ParameterType::PT_TEXTURE   ] = [](uint location,const void * value)->void{ if(value != nullptr) glUniform1i(       location,          ((TextureInfo*)value)->slotID); };
		ret[ParameterType::PT_TEXTURE2D ] = [](uint location,const void * value)->void{ if(value != nullptr) glUniform1i(       location,          ((TextureInfo*)value)->slotID); };
		ret[ParameterType::PT_TEXTURE3D ] = [](uint location,const void * value)->void{ if(value != nullptr) glUniform1i(       location,          ((TextureInfo*)value)->slotID); };
		return ret;
	}
	std::map<ParameterType,std::function<void(uint,const void *)>> uniformPasses = makeMap();
}

void ShaderProgram::passUniform(ShaderObject* obj) {
	ShaderPreProcessor::registerShaderObject(obj);
	for (int i = 0; i < obj->numOfUniforms(); i++) {
		passUniform(obj->getUniforms()[i]);
	}
}
void ShaderProgram::passUniform(const char * name, const bool& value)      { passUniform(name,ParameterType::PT_BOOLEAN,&value);    }
void ShaderProgram::passUniform(const char * name, const float& value)     { passUniform(name,ParameterType::PT_FLOAT,&value);      }
void ShaderProgram::passUniform(const char * name, const glm::vec3& value) { passUniform(name,ParameterType::PT_VEC3,&value[0]);    }
void ShaderProgram::passUniform(const char * name, const glm::vec4& value) { passUniform(name,ParameterType::PT_VEC4,&value[0]);    }
void ShaderProgram::passUniform(const char * name, const glm::mat3& value) { passUniform(name,ParameterType::PT_MAT3,&value[0][0]); }
void ShaderProgram::passUniform(const char * name, const glm::mat4& value) { passUniform(name,ParameterType::PT_MAT4,&value[0][0]); }

void ShaderProgram::passUniform(ShaderObject& obj) { passUniform(&obj); }
void ShaderProgram::passUniform(ShaderUniformPram * pram) { passUniform(pram->Title(),pram->Type(),pram->Pointer()); }
void ShaderProgram::passUniform(ShaderUniformPram& pram) { passUniform(&pram); }
void ShaderProgram::passUniform(uint location, ParameterType parameterType, const void * value) { uniformPasses[parameterType](location,value); }

void ShaderProgram::saveUniform(const char * name, const bool& value)      { saveUniform(name,ParameterType::PT_BOOLEAN,&value);    }
void ShaderProgram::saveUniform(const char * name, const float& value)     { saveUniform(name,ParameterType::PT_FLOAT,&value);      }
void ShaderProgram::saveUniform(const char * name, const glm::vec3& value) { saveUniform(name,ParameterType::PT_VEC3,&value[0]);    }
void ShaderProgram::saveUniform(const char * name, const glm::vec4& value) { saveUniform(name,ParameterType::PT_VEC4,&value[0]);    }
void ShaderProgram::saveUniform(const char * name, const glm::mat3& value) { saveUniform(name,ParameterType::PT_MAT3,&value[0][0]); }
void ShaderProgram::saveUniform(const char * name, const glm::mat4& value) { saveUniform(name,ParameterType::PT_MAT4,&value[0][0]); }
void ShaderProgram::saveUniform(ShaderObject * obj) {
	ShaderPreProcessor::registerShaderObject(obj);
	objUniforms.push_back(obj);
}
void ShaderProgram::saveUniform(const char* name, ParameterType parameterType, const void * value) { saveUniform(ShaderUniformPram(name,parameterType,value)); }
void ShaderProgram::saveUniform(ShaderUniformPram * pram) { saveUniform(*pram); }
void ShaderProgram::saveUniform(ShaderUniformPram& pram) { prams.push_back(pram); }

void ShaderProgram::passSavedUniforms_try() {
	if(validPush)
		passSavedUniforms_force();
}
void ShaderProgram::passSavedUniforms_force() {
	for (uint i = 0; i < prams.size(); i++) {
		passUniform(prams[i]);
	}
	for (uint i = 0; i < objUniforms.size(); i++) {
		passUniform(objUniforms[i]);
	}
	validPush = false;
}
bool ShaderProgram::getValidPush() {
	return validPush;
}
void ShaderProgram::resetValidPush() {
	validPush = true;
}

bool ShaderProgram::complileShader(const char * code, GLuint id, bool debug) {
	bool valid = true;
	const char * codeAdapt[1];
	codeAdapt[0] = code;
	glShaderSource(id,1,codeAdapt,0);
	
	//qDebug() << "Compiling Shader " << id;
	glCompileShader(id);
	

	if(debug) {
		GLint compileStatus;
		glGetShaderiv(id,GL_COMPILE_STATUS, &compileStatus);
		if(compileStatus != GL_TRUE) {
			GLint logLength;
			glGetShaderiv(id,GL_INFO_LOG_LENGTH,&logLength);
			char * buffer = new char[logLength];
			GLsizei someRandom;
			glGetShaderInfoLog(id,logLength,&someRandom,buffer);
			qDebug() << buffer;
			delete [] buffer;

			valid = false;
		}
	}
	return valid;
}

void ShaderProgram::link() {
	qDebug() << "Linking Program ID: " << programID;
	glLinkProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
	return programID;
}
GLuint ShaderProgram::getCurrentlyUsedProgram() {
	return currentProgram;
}
bool ShaderProgram::isCurrentProgram() {
	return (currentProgram == programID);
}
void ShaderProgram::useProgram() {
	if(!isCurrentProgram()) {
		//qDebug() << "Registering Shader Program  from " << currentProgram << " to " << programID << " into pipeline";
		currentProgram = programID;
		glUseProgram(programID);
	}
}

GLuint ShaderProgram::linkAndRun() {
	link();
	useProgram();
	return programID;
}

void ShaderProgram::PassDownToHardWare()
{
	programID = glCreateProgram();
	qDebug() << "Creating Shader Program ID: " << programID;
	//compile and link :D
	for (uint i = 0; i < files.size(); i++)
	{
		compileShader(files[i]);
	}
	link();
}

void ShaderProgram::update()
{
	passSavedUniforms_force();
}

ShaderProgram::ShaderProgram(const char * name)
{
	this->name = name;
}

ShaderProgram::ShaderProgram()
{

}
