#include "EditorRenderableComponent.h"




void EditorRenderableComponent::setName(std::string name)
{
	Name(name);
	if(editorInstance != nullptr) editorInstance->Name(name);
}

EditorRenderableComponent::EditorRenderableComponent(std::string myName, RenderableComponent * game, RenderableComponent * editor)
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
	//editorInstance->material = gameInstance->material; // not required since uniforms are synced
	editorInstance->geo = gameInstance->geo;
	editorInstance->visable = gameInstance->visable;
	editorInstance->objUniforms = gameInstance->objUniforms;
	editorInstance->uniformParameters = gameInstance->uniformParameters;
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

std::vector<std::string> EditorRenderableComponent::getErrors()
{
	std::vector<std::string> ret;
	if(name == "") ret.push_back("name not assigned to renderable binding component");
	if(gameInstance == nullptr)    ret.push_back("game instance not set");
	if(editorInstance == nullptr)  ret.push_back("editor instance not set");
	return ret;
}
