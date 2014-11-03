#include "CameraManager.h"
#include <Engine/DebugTools/DebugMemHeader.h>

IMPLEMENT_SINGLETON(CameraManager);



CameraManager::CameraManager() : activeCam(nullptr)
{

}

CameraComponent * CameraManager::ActiveCam() const
{
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
	activeCam = ret;
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
