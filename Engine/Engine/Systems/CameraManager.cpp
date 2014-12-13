#include "CameraManager.h"
#include <Engine/Entity/Entity.h>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>
#include <Engine/Systems/GameObjectManager.h>

#include <Engine/DebugTools/DebugMemHeader.h>

IMPLEMENT_SINGLETON(CameraManager);



CameraManager::CameraManager()
{
	//eventManager.Subscribe<ComponentRemovedEvent>([this](EventData*d,Object*o){
	//	ComponentRemovedEvent * data = (ComponentRemovedEvent*)d;
	//	if(allCams.Contains(data->beingTrashed)) {
	//		allCams.UnRegister(data->beingTrashed);
	//	}
	//});
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
}

std::vector<CameraComponent *> CameraManager::getAllActiveCams()
{
	auto tmp = Collections::Where<Object*>(allCams.getAll(),[](Object*o){
		CameraComponent * c = (CameraComponent*)o;
		return c->Active() && c->Parent()->GetActive() && gameManager.SelectorFunction()(c->Parent());
	});
	return Collections::RICVec<CameraComponent*,Object*>(tmp);
}
