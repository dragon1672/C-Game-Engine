#pragma once

#include <string>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>

namespace ShaderPreProcessor {
	ENGINE_SHARED std::string processGLSL(std::string src);
	ENGINE_SHARED void registerShaderObject(ShaderObject * obj);
	ENGINE_SHARED void registerShaderObject(ShaderObject& obj);
};