#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Systems/CameraManager.h>
#include <ExportHeader.h>

class EditorCam : public CameraComponent {


	virtual void update();

};