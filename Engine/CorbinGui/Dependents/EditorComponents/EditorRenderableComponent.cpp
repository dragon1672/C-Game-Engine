#include "EditorRenderableComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>


EditorRenderableComponent::EditorRenderableComponent(std::string myName, RenderableComponent * game, RenderableComponent * editor)
	: Component(myName)
{
	this->gameInstance = game;
	this->editorInstance = editor;
}

bool EditorRenderableComponent::isValid()
{
	return Name() != "" && gameInstance != nullptr && editorInstance != nullptr && gameInstance->isValid() && editorInstance->isValid();
}

void EditorRenderableComponent::sync()
{
	//editorInstance->material = gameInstance->material; // not required since uniforms are synced
	editorInstance->geo = gameInstance->geo;
	editorInstance->visable = gameInstance->visable;
	editorInstance->objUniforms = gameInstance->objUniforms;
	editorInstance->uniformParameters = gameInstance->uniformParameters;
	editorInstance->active = gameInstance->active;
}

void EditorRenderableComponent::earlyUpdate()
{
	sync();
}

void EditorRenderableComponent::init()
{
	sync();
}

void EditorRenderableComponent::init(std::string name, RenderableComponent * gameInstance, RenderableComponent * editorInstance)
{
	Name(name);
	this->gameInstance = gameInstance;
	this->editorInstance  = editorInstance;
	editorInstance->Name(name);
	eventManager.Subscribe<ComponentRemovedEvent>([=](EventData*d,Object*c){
		ComponentRemovedEvent * data = (ComponentRemovedEvent*)d;
		if(data->beingTrashed == gameInstance) {
			parent->removeComponent(editorInstance);
			parent->removeComponent(this);
		}
	});
}

void EditorRenderableComponent::start()
{
	sync();
}

std::vector<std::string> EditorRenderableComponent::getErrors()
{
	std::vector<std::string> ret;
	if(Name() == "") ret.push_back("name not assigned to renderable binding component");
	if(gameInstance == nullptr)    ret.push_back("game instance not set");
	if(editorInstance == nullptr)  ret.push_back("editor instance not set");
	return ret;
}

void EditorRenderableComponent::ChildSave(Stream& s)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void EditorRenderableComponent::ChildLoad(Stream& s)
{
	throw std::logic_error("The method or operation is not implemented.");
}
