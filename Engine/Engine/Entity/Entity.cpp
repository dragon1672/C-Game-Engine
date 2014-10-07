#include "Entity.h"
#include "Component.h"
#include <Engine\unsigned.h>

void Entity::removeComponent(int toKill) {
	if(toKill >= 0 && toKill < components.size()) {
		Component * c = components[toKill];
		components.erase(components.begin() + toKill);
	}
}
void Entity::addComponent(Component * toAdd) {
	toAdd->parent = this;
	components.push_back(toAdd);
}
template<typename T> void Entity::removeComponent() {
	int idToKill = -1;
	for(uint i=0;i<components.size() && idToKill < 0;i++) {
		if(typeid(*components[i]) == typeid(T)) idToKill = i;
	}
	removeComponent(idToKill); 
}
void Entity::removeComponent(Component * toKill) {
	int idToKill = -1;
	for(uint i=0;i<components.size() && idToKill< 0;i++) {
		if(components[i] == toKill) idToKill = i;
	}
	removeComponent(idToKill); 
}
void Entity::init()        { for(uint i=0; i<components.size(); i++) components[i]->init();        }
void Entity::earlyUpdate() { for(uint i=0; i<components.size(); i++) components[i]->earlyUpdate(); }
void Entity::update()      { for(uint i=0; i<components.size(); i++) components[i]->update();      }
void Entity::lateUpdate()  { for(uint i=0; i<components.size(); i++) components[i]->lateUpdate();  }