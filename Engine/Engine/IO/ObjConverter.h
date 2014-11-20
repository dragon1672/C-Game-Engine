#pragma once

#include <Engine/IO/FileIO.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <functional>
#include <ExportHeader.h>

typedef std::function<void(uint currentIndex, uint maxIndex, std::string line, bool wasValid)> LoadingCallBack;

namespace FileIO {
	ENGINE_SHARED Mesh Obj2Mesh(fileByte * bytes, uint fileSize, std::string name, LoadingCallBack callback = LoadingCallBack());
	ENGINE_SHARED Mesh ObjFilej2Mesh(const char * filePath, std::string name, LoadingCallBack callback = LoadingCallBack());
	ENGINE_SHARED Mesh ObjFilej2Mesh(std::string filePath, std::string name, LoadingCallBack callback = LoadingCallBack());
}