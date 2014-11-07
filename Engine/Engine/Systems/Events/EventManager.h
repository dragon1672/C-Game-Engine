#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Systems/Object.h>
#include <functional>
#include <ExportHeader.h>
#include <vector>
#include <map>

#define eventManager EventManager::getInstance()
#define emitEvent(event,data) eventManager.fire(#event,data,this)
#define emitTimedEvent(event,data,time) eventManager.fire(#event,data,this,time)
#define subscribeToEvent(event,function) eventManager.Subscribe(#event,function)

class ENGINE_SHARED EventManager {
	class EventInstance;
	class ENGINE_SHARED EventHandle {
		static int MasterID;
		int ID;
		std::string eventName;
		std::function<void(EventData*,Object*)> fun;
		EventManager * manager;
	public:
		EventHandle(std::string eventName, std::function<void(EventData*,Object*)> fun,EventManager * manager);
		void UnRegister();
		void Fire(EventData*data,Object * sender,float inNumSeconds = 0);
		friend EventManager;
		friend EventInstance;
	};
	class EventInstance {
		EventHandle handle;
		EventData*evt;
		Object*sender;
		EventManager * manager;
		float timeLeft;
		void fire();
	public:
		EventInstance(EventHandle handle, EventData*evt,Object*sender,float timeLeft);
		float TimeLeft()        const;
		EventManager * Manager() const;
		std::string EventName() const;
		EventData  * Evt()    const;
		Object * Sender() const;
		friend EventManager;
	};
	struct ListOfFunctions{ std::vector<EventHandle> funs; };
	std::map<std::string,ListOfFunctions> functions;
	std::vector<EventInstance> fireQ;
	DEFINE_SINGLETON(EventManager);
public:
	void update(float dt);

	void fire(EventHandle * event, EventData * data, Object * sender, float inNumSeconds = 0);
	void fire(EventHandle&  event, EventData * data, Object * sender, float inNumSeconds = 0);
	void fire(std::string   event, EventData * data, Object * sender, float inNumSeconds = 0);
	void fire(EventHandle * event, EventData&  data, Object * sender, float inNumSeconds = 0);
	void fire(EventHandle&  event, EventData&  data, Object * sender, float inNumSeconds = 0);
	void fire(std::string   event, EventData&  data, Object * sender, float inNumSeconds = 0);
	EventHandle Subscribe(std::string event,std::function<void(EventData*,Object*)> function);
	void RemoveEvent(EventHandle*handle);
};