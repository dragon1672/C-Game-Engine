#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/ObjectManager.h>
#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Defines/SingletonsDefine.h>

#include <Engine/Tools/CollectionEditing.h>

#define camManager CameraManager::getInstance()

class ENGINE_SHARED CameraManager {
	ObjectManager allCams;
	friend CameraComponent;
	DEFINE_SINGLETON(CameraManager);
public:
	CameraManager();
	CameraComponent * getCam(int index);
	CameraComponent * getCam(const char * name);
	void removeCam(CameraComponent * c);
	std::vector<CameraComponent *> getAllCamMatches(const char * name);
	std::vector<CameraComponent *> getAllActiveCams();
};