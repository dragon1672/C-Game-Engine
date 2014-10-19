#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine/Systems/Object.h>

class ENGINE_SHARED	Script : public Object {
public:
	std::string src;
};