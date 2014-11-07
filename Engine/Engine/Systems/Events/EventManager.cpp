#include "EventManager.h"
#include <Engine/Defines/Vectors.h>
#include <Engine/TypeDefs.h>

IMPLEMENT_SINGLETON(EventManager);

EventManager::EventHandle::EventHandle(std::string eventName, std::function<void(EventData*,Object*)> fun,EventManager * manager) : 
	eventName(eventName), fun(fun), manager(manager), ID(MasterID++)
{

}

void EventManager::EventHandle::UnRegister()
{
	manager->RemoveEvent(this);
}

void EventManager::EventHandle::Fire(EventData*data,Object * sender,float inNumSeconds /*= 0*/)
{
	manager->fire(this,data,sender,inNumSeconds);
}

int EventManager::EventHandle::MasterID = 0;

void EventManager::EventInstance::fire()
{
	handle.fun(evt,sender);
}

EventManager::EventInstance::EventInstance(EventHandle handle, EventData*evt,Object*sender,float timeLeft) :
	handle(handle),
	evt(evt),
	sender(sender),
	timeLeft(timeLeft)
{

}

float EventManager::EventInstance::TimeLeft() const
{
	return timeLeft;
}

EventManager * EventManager::EventInstance::Manager() const
{
	return handle.manager;
}

std::string EventManager::EventInstance::EventName() const
{
	return handle.eventName;
}

EventData * EventManager::EventInstance::Evt() const
{
	return evt;
}

Object * EventManager::EventInstance::Sender() const
{
	return sender;
}

void EventManager::update(float dt)
{
	for (uint i = 0; i < fireQ.size(); i++) {
		fireQ[i].timeLeft -= dt;
		if(fireQ[i].timeLeft <= 0 ) {
			fireQ[i].fire();
		}
	}
	//remove time
	VECTOR_REMOVE_CONDITION(fireQ,.timeLeft <= 0);
}

void EventManager::fire(EventHandle * event,EventData * data, Object * sender, float inNumSeconds /*= 0*/)
{
	fire(*event,data,sender,inNumSeconds);
}

void EventManager::fire(EventHandle& event,EventData * data, Object * sender, float inNumSeconds /*= 0*/)
{
	fire(event.eventName,data,sender,inNumSeconds);
}

void EventManager::fire(std::string event, EventData * data, Object * sender, float inNumSeconds /*= 0*/)
{
	if(functions.find(event)==functions.end()) return; // no one cares
	auto& list = functions[event].funs;
	if(inNumSeconds > 0) {
		for (uint i = 0; i < list.size(); i++) {
			fireQ.push_back(EventInstance(list[i],data,sender,inNumSeconds));
		}
	} else {
		for (uint i = 0; i < list.size(); i++) {
			EventInstance(list[i],data,sender,inNumSeconds).fire();
		}
	}
}

void EventManager::fire(std::string event, EventData& data, Object * sender, float inNumSeconds /*= 0*/)
{
	fire(event,&data,sender,inNumSeconds);
}

void EventManager::fire(EventHandle& event, EventData& data, Object * sender, float inNumSeconds /*= 0*/)
{
	fire(event,&data,sender,inNumSeconds);
}

void EventManager::fire(EventHandle * event, EventData& data, Object * sender, float inNumSeconds /*= 0*/)
{
	fire(event,&data,sender,inNumSeconds);
}

EventManager::EventHandle EventManager::Subscribe(std::string event,std::function<void(EventData*,Object*)> function)
{
	if(functions.find(event) == functions.end()) {
		functions[event] = ListOfFunctions();
	}
	auto ret = EventHandle(event,function,this);
	functions[event].funs.push_back(ret);
	return ret;
}

void EventManager::RemoveEvent(EventHandle*handle)
{
	if(functions.find(handle->eventName) == functions.end()) return; // not in map
	auto& list = functions[handle->eventName].funs;
	VECTOR_REMOVE_CONDITION(list,.ID == handle->ID);
}
