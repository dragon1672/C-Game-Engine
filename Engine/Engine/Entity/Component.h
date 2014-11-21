#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>
#include <string>
#include <vector>
#include <functional>

#include <Engine/IO/StreamableObject.h>

//place in CPP file of each component
#define REGISTER_COMPONENT(class_name) namespace { int RegisterSuccessful = Component::RegisterComponentConstructor(typeid(class_name).name(),[](){ return new class_name(); }); }

class Entity;
class ENGINE_SHARED Component : public Object, public ShaderObject, public StreamableObject { 
protected:
	friend Entity;
	Entity * parent;
	virtual void ChildSave(Stream& s) = 0;
	virtual void ChildLoad(Stream& s) = 0;
public:
	bool active;
	Component(std::string name = "");
	virtual ~Component(){}
	inline Entity * Parent() { return parent; }
	virtual void init()        {} // called once
	virtual void start()       {} // called every scene load before update starts
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
	virtual void saveValues()  {}
	virtual void restoreValues()  {}
	virtual bool isValid() = 0;
	virtual std::vector<std::string> getErrors() = 0;
	void Save(Stream& s);
	void Load(Stream& s);
	virtual bool CopyInto(Component* that) = 0;
	virtual Component * Clone() = 0;
	virtual Component * getNewInstanceOfCurrentType() = 0;

	static Component * GetInstanceFromTypeString(std::string name);

	static bool RegisterComponentConstructor(std::string name, std::function<Component*()> createMethod);
	std::string Class_Name();
};


#define MAKE_COMPONENT_CLASS(name) name : public Component_CRTP<name>

template<typename Derived>
class Component_CRTP : public Component {
public:
	Component_CRTP(std::string name = "") : Component(name) {}
	Component * Clone() {
		auto ret = new Derived(dynamic_cast<Derived const&>(*this));
		Object::generateNewIdForObject(ret);
		return ret;
	}
	Component * getNewInstanceOfCurrentType() {
		return new Derived();
	}
};



