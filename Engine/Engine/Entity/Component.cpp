#include "Component.h"
#include <map>
#include <functional>
#include <memory>

namespace {
	template<typename T>
	class cleaner {
	public:
		T * data;
		~cleaner() {
			delete data;
		}
	};

	cleaner<std::map<std::string,std::function<Component*()>>> creationMap;
}



void Component::Save(Stream& s)
{
	Object::ObjectSave(s);
	ChildSave(s);
}

void Component::Load(Stream& s)
{
	Object::ObjectLoad(s);
	ChildLoad(s);
}

Component::Component(std::string name /*= ""*/) : Object(name), active(true), parent(nullptr)
{

}

bool Component::RegisterComponentConstructor(std::string name, std::function<Component*()> createMethod)
{
	static bool first = true;
	if(first) {
		creationMap.data = new std::map<std::string,std::function<Component*()>>();
	}
	(*creationMap.data)[name] = createMethod;
	//(*creationMap).emplace(name,createMethod);
	first = false;
	return true;
}

Component * Component::GetInstanceFromTypeString(std::string name)
{
	return (*creationMap.data)[name]();
}

std::string Component::Class_Name()
{
	return std::string(typeid(*this).name());
}
