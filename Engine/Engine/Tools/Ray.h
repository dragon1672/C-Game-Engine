#pragma once

#include <glm\glm.hpp>
#include "ExportHeader.h"
#include "Camera.h"

struct ENGINE_SHARED Ray {
	glm::vec3 direction;
	glm::vec3 origin;
};