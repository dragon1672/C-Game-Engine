#pragma once

#include <ExportHeader.h>
#include <Engine/Entity/Component.h>
#include <glm/glm.hpp>
#include <Engine/Tools/PropertyWrapper.h>

class ENGINE_SHARED CameraComponent : public Component {
	bool perspectiveNeedsUpdate;
	glm::mat4 perspective;
public:
	CameraComponent(const char * name = nullptr);
	PropertyGetSet<int> width;
	PropertyGetSet<int> height;
	PropertyGetSet<float> nearPlane;
	PropertyGetSet<float> farPlane;
	glm::mat4& getWorld2View();
	glm::mat4& getPerspective();
};