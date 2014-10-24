#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/ObjectManager.h>
#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Defines/SingletonsDefine.h>

#include <Engine/Tools/CollectionEditing.h>

#define camManager CameraManager::getInstance()

class ENGINE_SHARED CameraManager {
	ObjectManager allCams;
	CameraComponent * activeCam;
	DEFINE_SINGLETON(CameraManager);
public:
	CameraManager();
	CameraComponent * ActiveCam() const;
	void ActiveCam(CameraComponent * val);
	CameraComponent * getNewCam(const char * name);
	CameraComponent * getCam(int index);
	CameraComponent * getCam(const char * name);
	std::vector<CameraComponent *> getAllCamMatches(const char * name);
};