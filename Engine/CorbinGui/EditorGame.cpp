#include "EditorGame.h"
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <CorbinGui/Dependents/EditorComponents/EditorCam.h>



EditorGame::EditorGame()
{
	uniqueName = Random::rString::Letters(4)+"EditorInstance"+Random::rString::Letters(4);
	isEditorObject = [this](Object* o){
		return StringManapulation::startsWith(o->Name(),this->uniqueName);
	};
	isGameObject = [this](Object* o){
		return !StringManapulation::startsWith(o->Name(),this->uniqueName);
	};
	gameManager.ComponentSelectorFunction(isEditorObject);
	currentEntity.editor = this;
	EditorEntity = gameManager.AddEntity(uniqueName);
	auto tmp = EditorEntity->addComponent<EditorCam>();
	tmp->Name(uniqueName);
}

void EditorGame::RemoveCurrentEntity()
{
	if(currentEntity.currentlySelectedEntity != nullptr) {
		gameManager.RemoveEntity(currentEntity.currentlySelectedEntity);
	}
	currentEntity.currentlySelectedEntity = nullptr;
}

void EditorGame::AddEntity(std::string name)
{
	currentEntity.currentlySelectedEntity = gameManager.AddEntity(name);
}

void EditorGame::initGl()
{
	gameManager.initGl();
}

void EditorGame::init()
{
	gameManager.init();
}

void EditorGame::start()
{
	gameManager.start();
}

void EditorGame::update()
{
	gameManager.update();
	gameManager.width = width;
	gameManager.height = height;
}

void EditorGame::paint()
{
	gameManager.paint();
}

EditorGame::~EditorGame()
{
	gameManager.delInstance();
}

template<>
RenderableComponent * EditorGame::scoper::addComponent()
{
	auto ret = currentlySelectedEntity->addComponent<RenderableComponent>();
	auto editorV = currentlySelectedEntity->addComponent<RenderableComponent>();
	auto binder = currentlySelectedEntity->addComponent<EditorRenderableComponent>();
	binder->gameInstance = ret;
	binder->editorInstance = editorV;
	binder->setName(editor->uniqueName);
	editorV->shader = resourceManager.getDefault<ShaderProgram>();
	binder->sync();
	return ret;
}

template<>
ScriptComponent * EditorGame::scoper::addComponent()
{
	auto ret = currentlySelectedEntity->addComponent<ScriptComponent>();
	return ret;
}

template<>
CameraComponent * EditorGame::scoper::addComponent()
{
	auto ret = currentlySelectedEntity->addComponent<CameraComponent>();

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
	Entity * parent = gameManager.getEntity(name);
	currentlySelectedEntity->Parent(parent);
}

std::vector<Component*> EditorGame::scoper::getAllComponents()
{
	return currentlySelectedEntity->getAllComponents();
}

std::vector<Component*> EditorGame::scoper::getAllGameComponents()
{
	return Collections::Where<Component*>(currentlySelectedEntity->getAllComponents(),[this](Component*c){ return !(gameManager.ComponentSelectorFunction()(c)); });
}

void EditorGame::scoper::SetCurrent(Entity * toSet)
{
	currentlySelectedEntity = toSet;
}
