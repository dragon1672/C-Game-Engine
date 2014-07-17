#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_h

#pragma warning(disable: 4201)
#pragma warning(push)
#include <QtOpenGL\qglwidget>
#pragma warning(pop)
#include <string>
#include <Engine\Renderer\ParameterType.h>
#include "ExportHeader.h"
#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\unsigned.h>

class ENGINE_SHARED ShaderProgram {
private:
	static int numOfTextures;
	static const int MAX_POSSIBLE_PROGRAM_FILES = 10;
	static GLuint currentProgram;
	
	ShaderUniformPram prams[30];
	uint numOfPrams;

	GLuint programID;

	static std::string file2str(const char * filePath);
	static bool validFile(const char * filePath);
	bool validPush;
public:
	void startup();
	void shutdown();

	//restarts, compiles, link and uses this program
	void buildBasicProgram(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	bool addProgram(const char * filePath, unsigned short shaderType);
	bool addProgram_srcCode(const char * shaderCode, unsigned short shaderType);
	bool addProgram_srcCode(std::string shaderCode, unsigned short shaderType);
	bool complileShader(const char * code, GLuint id, bool debug);
	void link();
	GLuint linkAndRun();

	GLuint getProgramID();
	GLuint getCurrentlyUsedProgram();
	bool isCurrentProgram();
	void useProgram();

	int getUniform(const char* title);
	//only passes data down once, will not update every paint
	void passUniform(const char* name, ParameterType parameterType, const void * value);

	//use these to add shader wide uniforms
	void saveUniform(const char* name, ParameterType parameterType, const void * value);

	//used in draw calls
	void passSavedUniforms_try();
	void passSavedUniforms_force();
	bool getValidPush();
	void resetValidPush();

	static QImage getImageFromFile(QString filePath, bool flipHorz = false, bool flipVert = false);

	//returns the bufferID
	static GLuint load2DTexture(QImage image);
	static GLuint load2DTexture(QString filePath, bool flipHorz = false, bool flipVert = false);
	static GLuint load2DTexture(ubyte * data, uint width, uint height);
};

#endif