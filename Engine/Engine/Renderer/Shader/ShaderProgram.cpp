#include <GL\glew.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>
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
#include <Engine\Renderer\TextureInfo.h>


GLuint ShaderProgram::currentProgram;
int ShaderProgram::numOfTextures = 0;

struct CodeBlock { // used to store shader code
	GLuint id;
	std::string code;
};

 std::string ShaderProgram::file2str(const char * filePath) {
	std::ifstream file(filePath);
	return std::string(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
}
bool ShaderProgram::validFile(const char * filePath) {
	std::ifstream file(filePath);
	bool valid = file.good();
	file.close();
	return valid;
}

void ShaderProgram::startup() {
	programID = glCreateProgram();
	qDebug() << "Creating Shader Program ID: " << programID;
}
ShaderProgram::~ShaderProgram() {
	shutdown();
}
void ShaderProgram::shutdown() {
	CLEAR_VECTOR(prams);
}
void ShaderProgram::buildBasicProgram(const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	//startup();
	bool win = false;
	win = addProgram(vertexShaderFilePath,GL_VERTEX_SHADER);
	if(win) win = addProgram(fragmentShaderFilePath,GL_FRAGMENT_SHADER);
	if(win) linkAndRun();
}
bool ShaderProgram::addProgram(const char * filePath, unsigned short shaderType) {
	qDebug() << "\nAttempting to load file: " << filePath;
	
	bool isValid = validFile(filePath);
	if(isValid) {
		isValid = addProgram_srcCode(file2str(filePath),shaderType);
	} else {
		qDebug() << "File(" << filePath << ") was not found\n";
		assert(false);
	}
	return isValid;
}
bool ShaderProgram::addProgram_srcCode(const char * shaderCode, unsigned short shaderType) {
	return addProgram_srcCode(std::string(shaderCode),shaderType);
}
bool ShaderProgram::addProgram_srcCode(std::string shaderCode, unsigned short shaderType) {
	bool isValid;
	CodeBlock shaderInfo;
	shaderInfo.code = shaderCode;
	shaderInfo.id = glCreateShader(shaderType);
	qDebug() << "Shader Load Successful ID: " << shaderInfo.id;

	isValid = complileShader(shaderInfo.code.c_str(),shaderInfo.id,true);
	if(isValid) {
		glAttachShader(programID,shaderInfo.id);
		qDebug() << "File(" << shaderInfo.id << ") Complile Successful ProgramID: " << programID << "\n";
	} else {
		qDebug() << "File(" << shaderInfo.id << ") Failed to Complile - NOT ADDED TO PROGRAM\n";
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
void ShaderProgram::passUniform(uint location, ParameterType parameterType, const void * value) {
	if(parameterType == ParameterType::PT_FLOAT) {
		glUniform1f(location, *(float*)value);
	} else if(parameterType == ParameterType::PT_VEC2) {
		glUniform2fv(location,1,(float*)value);
	} else if(parameterType == ParameterType::PT_VEC3) {
		glUniform3fv(location,1,(float*)value);
	} else if(parameterType == ParameterType::PT_VEC4) {
		glUniform4fv(location,1,(float*)value);
	} else if(parameterType == ParameterType::PT_MAT3) {
		glUniformMatrix3fv(location,1,false,(float*)value);
	} else if(parameterType == ParameterType::PT_MAT4) {
		glUniformMatrix4fv(location,1,false,(float*)value);
	} else if(ParameterType::PT_BOOLEAN) {
		bool decodedValue = *(bool*)value;
		glUniform1i(location,decodedValue);
	} else if(parameterType == ParameterType::PT_INT) {
		int decodedValue = *(int*)value;
		glUniform1i(location,decodedValue);
	} else if(parameterType == ParameterType::PT_TEXTURE) {
		int slot = ((TextureInfo*)value)->slotID;
		glUniform1i(location,slot);
	} else {
		//wat?
		qDebug() << "Uniform " << location << " of type: " << parameterType << " was not passed down correctly";
		assert(false);
	}
}

void ShaderProgram::saveUniform(const char * name, const bool& value)      { saveUniform(name,ParameterType::PT_BOOLEAN,&value);    }
void ShaderProgram::saveUniform(const char * name, const float& value)     { saveUniform(name,ParameterType::PT_FLOAT,&value);      }
void ShaderProgram::saveUniform(const char * name, const glm::vec3& value) { saveUniform(name,ParameterType::PT_VEC3,&value[0]);    }
void ShaderProgram::saveUniform(const char * name, const glm::vec4& value) { saveUniform(name,ParameterType::PT_VEC4,&value[0]);    }
void ShaderProgram::saveUniform(const char * name, const glm::mat3& value) { saveUniform(name,ParameterType::PT_MAT3,&value[0][0]); }
void ShaderProgram::saveUniform(const char * name, const glm::mat4& value) { saveUniform(name,ParameterType::PT_MAT4,&value[0][0]); }
void ShaderProgram::saveUniform(const char* name, ParameterType parameterType, const void * value) {
	prams.push_back(new ShaderUniformPram());
	prams[prams.size()-1]->init(this,name,parameterType,value);
}

void ShaderProgram::passSavedUniforms_try() {
	if(validPush)
		passSavedUniforms_force();
}
void ShaderProgram::passSavedUniforms_force() {
	for (uint i = 0; i < prams.size(); i++)
	{
		prams[i]->sendData();
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
		//qDebug() << "Regestering Shader Program  from " << currentProgram << " to " << programID << " into pipeline";
		currentProgram = programID;
		glUseProgram(programID);
	}
}

GLuint ShaderProgram::linkAndRun() {
	link();
	useProgram();
	return programID;
}