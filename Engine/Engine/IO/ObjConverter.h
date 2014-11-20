#pragma once

#include <Engine/IO/FileIO.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <functional>

typedef std::function<void(uint currentIndex, uint maxIndex, std::string line, bool wasValid)> LoadingCallBack;

namespace FileIO {
	Mesh Obj2Mesh(fileByte * bytes, uint fileSize, LoadingCallBack callback = LoadingCallBack());
	Mesh ObjFilej2Mesh(char * filePath, LoadingCallBack callback = LoadingCallBack());
}