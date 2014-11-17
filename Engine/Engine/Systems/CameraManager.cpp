#include "CameraManager.h"
#include <Engine/DebugTools/DebugMemHeader.h>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>

IMPLEMENT_SINGLETON(CameraManager);



CameraManager::CameraManager() : activeCam(nullptr)
{
	eventManager.Subscribe<ComponentRemovedEvent>([this](EventData*d,Object*o){
		ComponentRemovedEvent * data = (ComponentRemovedEvent*)d;
		if(allCams.Contains(data->beingTrashed)) {
			allCams.UnRegister(data->beingTrashed);
		}
	});
}

CameraComponent * CameraManager::ActiveCam()
{
	if(activeCam == nullptr || !activeCam->active) {//set new active can
		std::vector<Object*> tmp = allCams.getAll();
		if(tmp.size() == 0) activeCam = nullptr;
		else activeCam = (CameraComponent*)tmp[0];
	}
	return activeCam;
}

void CameraManager::ActiveCam(CameraComponent * val)
{
	activeCam = val;
}

CameraComponent * CameraManager::getNewCam(const char * name)
{
	auto ret = new CameraComponent(name);
	allCams.Register(ret);
	if(activeCam == nullptr) activeCam = ret;
	return ret;
}

CameraComponent * CameraManager::getCam(int index)
{
	return (CameraComponent *)allCams.getFirst(index);
}

CameraComponent * CameraManager::getCam(const char * name)
{
	return (CameraComponent *)allCams.getFirst(name);
}

std::vector<CameraComponent *> CameraManager::getAllCamMatches(const char * name)
{
	return Collections::RICVec<CameraComponent*>(allCams.getAll(name));
}

void CameraManager::removeCam(CameraComponent * c)
{
	allCams.UnRegister(c);
	if(activeCam == c) activeCam = nullptr;
}
