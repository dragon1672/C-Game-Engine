#include "EditorGame.h"
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <CorbinGui/Dependents/EditorComponents/EditorMasterSyncer.h>
#include <Engine/Entity/Entity.h>



EditorGame::EditorGame()
{
	isEditorObject = [this](Object* o){
		return editorObjects.find(o) != editorObjects.end();
	};
	isGameObject = [this](Object* o){
		return editorObjects.find(o) == editorObjects.end();
	};
	gameManager.SelectorFunction(isEditorObject);
	currentEntity.editor = this;
	EditorCamera = gameManager.AddEntity();
	EditorCamera->addComponent<CameraComponent>();
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
	auto curr = gameManager.AddEntity(name);
	gameManager.AddEntity("Editor_"+name)->addComponent<EditorMasterSyncer>()->init(curr);
	currentEntity.currentlySelectedEntity = curr;
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
	//auto editorV = currentlySelectedEntity->addComponent<RenderableComponent>();
	//auto binder = currentlySelectedEntity->addComponent<EditorRenderableComponent>();
	//binder->init(editor->uniqueName,ret,editorV);
	//editorV->Shader(resourceManager.getDefault<ShaderProgram>());
	//binder->sync();
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

void EditorGame::scoper::SetCurrent(Entity * toSet)
{
	currentlySelectedEntity = toSet;
}
