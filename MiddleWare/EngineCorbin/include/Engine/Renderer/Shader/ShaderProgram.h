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
#include <glm\glm.hpp>

class ENGINE_SHARED ShaderProgram {
private:
	static int numOfTextures;
	static GLuint currentProgram;
	
	std::vector<ShaderUniformPram *> prams;

	GLuint programID;

	static std::string file2str(const char * filePath);
	static bool validFile(const char * filePath);
	bool validPush;
public:
	void startup();
	~ShaderProgram();
	void shutdown();

	//restarts, compiles, link and uses this program
	void buildBasicProgram(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);

	//adds singluar shaders
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
	void passUniform(uint location, ParameterType parameterType, const void * value);

	//use these to add shader wide uniforms
	void saveUniform(const char * name, const bool& value);
	void saveUniform(const char * name, const float& value);
	void saveUniform(const char * name, const glm::vec3& value);
	void saveUniform(const char * name, const glm::vec4& value);
	void saveUniform(const char * name, const glm::mat3& value);
	void saveUniform(const char * name, const glm::mat4& value);
	void saveUniform(const char* name, ParameterType parameterType, const void * value);

	//used in draw calls
	void passSavedUniforms_try();
	void passSavedUniforms_force();
	bool getValidPush();
	void resetValidPush();

	static QImage getImageFromFile(QString& filePath, bool flipHorz = false, bool flipVert = false);

	struct ImageData {
		ubyte * data;
		uint width;
		uint height;
		GLenum type;
		GLenum type2;
		ImageData() : data(nullptr),
					width(-1), height(-1),
					type(GL_RGBA), type2(-1) {}
		ImageData(QImage& src) {
			init(src);
			type = GL_RGBA;
			type2 = -1;
		}
		void init(QImage& src) {
			data = src.bits();
			width = src.width();
			height = src.height();
		}
	};

	//returns the slotID
	static GLuint load2DTexture(QImage& image, GLenum type = GL_RGBA);
	static GLuint load2DTexture(QImage& image, GLenum type, GLenum type2);
	static GLuint load2DTexture(QString& filePath, bool flipHorz = false, bool flipVert = false);
	static GLuint load2DTexture(ubyte * data, uint width, uint height, GLenum type = GL_RGBA);
	static GLuint load2DTexture(ubyte * data, uint width, uint height, GLenum type, GLenum type2);
	static GLuint load2DTexture(ImageData& imageData);

	static void update2DTexture(uint textureID, uint slot, QImage& image, GLenum type = GL_RGBA);
	static void update2DTexture(uint textureID, uint slot, QImage& image, GLenum type, GLenum type2);
	static void update2DTexture(uint textureID, uint slot, QString& filePath, bool flipHorz = false, bool flipVert = false);
	static void update2DTexture(uint textureID, uint slot, ubyte * data, uint width, uint height, GLenum type = GL_RGBA);
	static void update2DTexture(uint textureID, uint slot, ubyte * data, uint width, uint height, GLenum type, GLenum type2);
	static void update2DTexture(uint textureID, uint slot, ImageData& imageData);

	static GLuint loadCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	static GLuint loadCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	static GLuint loadCubeTexture(ImageData& posX,ImageData& negX,ImageData& posY,ImageData& negY,ImageData& posZ,ImageData& negZ);
	static GLuint loadCubeTexture(QImage& posX,QImage& negX,QImage& posY,QImage& negY,QImage& posZ,QImage& negZ);
};

#endif