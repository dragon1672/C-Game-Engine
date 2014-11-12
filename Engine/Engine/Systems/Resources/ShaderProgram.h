#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_h

#pragma warning(disable: 4201)
#pragma warning(push)
#include <QtOpenGL\qglwidget>
#pragma warning(pop)
#include <string>
#include <Engine\Systems\Resources\Shaders\ParameterType.h>
#include "ExportHeader.h"
#include <Engine\Systems\Resources\Shaders\ShaderUniformPram.h>
#include <Engine\TypeDefs.h>
#include <glm\glm.hpp>
#include <Engine\Systems\Resource.h>
#include <Engine\Systems\Resources\Shaders\ShaderObject.h>

class ENGINE_SHARED ShaderProgram : public Resource {
private:
	static GLuint currentProgram;
	
	std::vector<ShaderUniformPram> prams;
	std::vector<ShaderObject*> objUniforms;

	struct CodeBlock : public StreamableObject { // used to store shader code
		GLuint type;
		std::string code;

		virtual void Save(Stream&s);
		virtual void Load(Stream&s);

	};

	std::vector<CodeBlock> files;

	GLuint programID;

	bool validPush;

	void passSavedUniforms_try();
	void passSavedUniforms_force();
	bool getValidPush();
	void resetValidPush();
	bool complileShader(const char * code, GLuint id, bool debug);
	void link();
	GLuint linkAndRun();
	int getUniform(const char* title);

	bool compileShader(CodeBlock&);
public:
	ShaderProgram(std::string name="");


	void buildBasicProgram(std::string  vertexShaderFile, std::string  fragmentShaderFile);
	void buildBasicProgram(const char * vertexShaderFile, const char * fragmentShaderFile);
	//adds singular shaders
	void addProgram(const char * shaderCode, unsigned short shaderType);
	void addProgram(std::string shaderCode,  unsigned short shaderType);

	GLuint getProgramID();
	GLuint getCurrentlyUsedProgram();
	bool isCurrentProgram();
	void useProgram();

	//use these to add shader wide uniforms
	void saveUniform(const char * name, const bool& value);
	void saveUniform(const char * name, const float& value);
	void saveUniform(const char * name, const glm::vec3& value);
	void saveUniform(const char * name, const glm::vec4& value);
	void saveUniform(const char * name, const glm::mat3& value);
	void saveUniform(const char * name, const glm::mat4& value);
	void saveUniform(ShaderObject * obj);
	void saveUniform(const char* name, ParameterType parameterType, const void * value);
	void saveUniform(ShaderUniformPram * obj);
	void saveUniform(ShaderUniformPram& obj);

	virtual void PassDownToHardWare();
	virtual void update();
	//only passes data down once, will not update every paint
	void passUniform(const char * name, const bool& value);
	void passUniform(const char * name, const float& value);
	void passUniform(const char * name, const glm::vec3& value);
	void passUniform(const char * name, const glm::vec4& value);
	void passUniform(const char * name, const glm::mat3& value);
	void passUniform(const char * name, const glm::mat4& value);
	void passUniform(ShaderUniformPram * pram);
	void passUniform(ShaderUniformPram& pram);
	void passUniform(ShaderObject* pram);
	void passUniform(ShaderObject& pram);
	void passUniform(const char* name, ParameterType parameterType, const void * value);
	void passUniform(uint location, ParameterType parameterType, const void * value);

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

};

#endif