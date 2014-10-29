#include "EditorRenderableComponent.h"




void EditorRenderableComponent::setName(const char * name)
{
	this->name = name;
	if(editorInstance != nullptr) editorInstance->Name(name);
}

EditorRenderableComponent::EditorRenderableComponent(const char * myName, RenderableComponent * game, RenderableComponent * editor)
{
	this->name = myName;
	this->gameInstance = game;
	this->editorInstance = editor;
}

EditorRenderableComponent::EditorRenderableComponent() :
	gameInstance(nullptr),editorInstance(nullptr)
{

}

bool EditorRenderableComponent::isValid()
{
	return name != "" && gameInstance != nullptr && editorInstance != nullptr && gameInstance->isValid() && editorInstance->isValid();
}

void EditorRenderableComponent::sync()
{
	editorInstance->material = gameInstance->material;
	editorInstance->geo = gameInstance->geo;
	editorInstance->visable = gameInstance->visable;
}

void EditorRenderableComponent::earlyUpdate()
{
	sync();
}

void EditorRenderableComponent::init()
{
	sync();
}

void EditorRenderableComponent::start()
{
	sync();
}
