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

void EventManager::EventHandle::Fire(EventData*data,Object * sender,std::function<void(EventData*)> destructor,float inNumSeconds /*= 0*/)
{
	manager->fire(data,sender,destructor,inNumSeconds);
}

int EventManager::EventHandle::MasterID = 0;

void EventManager::EventInstance::fire()
{
	handle.fun(evt,sender);
	destructor(evt);
}

EventManager::EventInstance::EventInstance(EventHandle handle, EventData*evt,Object*sender,std::function<void(EventData*)> destructor,float timeLeft) :
	handle(handle),
	evt(evt),
	sender(sender),
	timeLeft(timeLeft),
	destructor(destructor)
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
	if(disable) return;
	for (uint i = 0; i < fireQ.size(); i++) {
		fireQ[i].timeLeft -= dt;
		if(fireQ[i].timeLeft <= 0 ) {
			fireQ[i].fire();
		}
	}
	//remove time
	VECTOR_REMOVE_CONDITION(fireQ,.timeLeft <= 0);
}

void EventManager::fire(EventData * data, Object * sender, std::function<void(EventData*)> destructor /*= [](EventData*e){delete e;}*/, float inNumSeconds /*= 0*/)
{
	std::string event = data->getEventName();
	if(disable || functions.find(event)==functions.end()) { // no one cares
		destructor(data);
		return;
	}
	auto& list = functions[event].funs;

	std::function<void(EventData*)> dummy = [](EventData*){};

	if(inNumSeconds > 0) {
		for (uint i = 0; i < list.size(); i++) {
			std::function<void(EventData*)> toUse = i==list.size()-1 ? destructor:dummy;
			fireQ.push_back(EventInstance(list[i],data,sender,toUse,inNumSeconds));
		}
		if(list.size()==0) destructor(data);
	} else {
		for (uint i = 0; i < list.size(); i++) {
			EventInstance(list[i],data,sender,dummy,inNumSeconds).fire();
		}
		destructor(data);
	}
}
void EventManager::fire(EventData& data, Object * sender, float inNumSeconds /*= 0*/)
{
	//assume that person who fired know about data
	fire(&data,sender,[](EventData*){},inNumSeconds);
}

EventManager::EventHandle EventManager::Subscribe(std::string event,std::function<void(EventData*,Object*)> function)
{
	if(functions.find(event) == functions.end()) {
		functions.emplace(event,ListOfFunctions());
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

void EventManager::Disable()
{
	disable = true;
}

void EventManager::Enable()
{
	disable = false;
}

EventManager::EventManager() : disable(false)
{

}
