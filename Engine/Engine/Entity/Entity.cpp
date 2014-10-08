#include "Entity.h"
#include "Component.h"
#include <Engine\unsigned.h>

void Entity::removeComponent(int toKill) {
	if(toKill >= 0 && toKill < (int)components.size()) {
		Component * c = components[toKill];
		delete(c);
		components.erase(components.begin() + toKill);
	}
}
void Entity::addComponent(Component * toAdd) {
	toAdd->parent = this;
	components.push_back(toAdd);
}
void Entity::removeComponent(Component * toKill) {
	removeComponent(getIndex(toKill)); 
}
void Entity::init()        { for(uint i=0; i<components.size(); i++) components[i]->init();        }
void Entity::earlyUpdate() { for(uint i=0; i<components.size(); i++) components[i]->earlyUpdate(); }
void Entity::update()      { for(uint i=0; i<components.size(); i++) components[i]->update();      }
void Entity::lateUpdate()  { for(uint i=0; i<components.size(); i++) components[i]->lateUpdate();  }

int Entity::getIndex(Component * toFind) {
	for(uint i=0;i<components.size();i++) {
		if(components[i] == toFind) return i;
	}
	return -1;
}
