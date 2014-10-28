#include "EditorGame.h"
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>



EditorGame::EditorGame()
{
	uniqueName = Random::rString::Letters(4)+"EditorInstance"+Random::rString::Letters(4);
	auto tmpFunction = [this](Object* o){
		return StringManapulation::startsWith(o->Name(),this->uniqueName);
	};
	game.SelectorFunction(tmpFunction);
	game.ComponentSelectorFunction(tmpFunction);
	currentEntity.editor = this;
}

template<>
RenderableComponent * EditorGame::scoper::addComponent()
{
	auto ret = currentlySelectedEntity->addComponent<RenderableComponent>();
	auto editorV = currentlySelectedEntity->addComponent<RenderableComponent>();
	auto binder = currentlySelectedEntity->addComponent<EditorRenderableComponent>();
	binder->gameInstance = ret;
	binder->editorInstance = editorV;
	binder->setName(editor->uniqueName.c_str());
	editorV->shader = resourceManager.getDefault<ShaderProgram>();
	binder->sync();
	return ret;
}

MatrixInfo * EditorGame::scoper::getTrans()
{
	return currentlySelectedEntity->getTrans();
}

ScriptComponent * EditorGame::scoper::getScript()
{
	return currentlySelectedEntity->getComponent<ScriptComponent>();
}

RenderableComponent * EditorGame::scoper::getRenderable()
{
	return currentlySelectedEntity->getComponent<RenderableComponent>();
}

CameraComponent * EditorGame::scoper::getCamera()
{
	return currentlySelectedEntity->getComponent<CameraComponent>();
}

std::vector<ScriptComponent *> EditorGame::scoper::getAllScripts()
{
	return currentlySelectedEntity->getComponents<ScriptComponent>();
}

std::vector<RenderableComponent *> EditorGame::scoper::getAllRenderables()
{
	return currentlySelectedEntity->getComponents<RenderableComponent>();
}

std::vector<CameraComponent *> EditorGame::scoper::getAllCameras()
{
	return currentlySelectedEntity->getComponents<CameraComponent>();
}

void EditorGame::scoper::Parent(const char * name)
{
	int index = editor->game.entities.find([name](const Entity& e){ return e.Name() == name; });
	Entity * parent = (index < 0 ? nullptr : &(editor->game.entities[index]));
	currentlySelectedEntity->Parent(parent);
}
