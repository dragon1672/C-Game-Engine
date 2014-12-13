#include "EditorGame.h"
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <CorbinGui/Dependents/EditorComponents/EditorMasterSyncer.h>
#include <Engine/Entity/Entity.h>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>


EditorGame::EditorGame()
{
	isEditorObject = [this](Entity* o){
		return editorObjects.containsValue(o);
	};
	isGameObject = [this](Entity* o){
		return !isEditorObject(o);
	};
	eventManager.Subscribe<EntityRemovedEvent>([this](EventData*d,Object*) {
		EntityRemovedEvent * data = (EntityRemovedEvent*)d;
		if(editorObjects.containsValue(data->entity)) {
			editorObjects.removeValue(data->entity);
		}
	});
	gameManager.SelectorFunction(isEditorObject);
	currentEntity.editor = this;
	createEditorObjects();
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
	auto editorV = gameManager.AddEntity("Editor_"+curr->Name());
	editorV->addComponent<EditorMasterSyncer>()->init(curr,this);
	editorObjects.emplace(curr, editorV);
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

void EditorGame::paint(std::function<void(int startX,int startY,int width,int height)> setViewPort)
{
	gameManager.paint(setViewPort);
}

EditorGame::~EditorGame()
{
	gameManager.delInstance();
}

void EditorGame::createEditorObjects()
{
	auto ents = gameManager.getAllEntities();
	EditorCamera = gameManager.AddEntity("Editor Cam");
	EditorCamera->addComponent<CameraComponent>();
	editorObjects.emplace(nullptr,EditorCamera);
	for (uint i = 0; i < ents.size(); i++)
	{
		auto editorV = gameManager.AddEntity("Editor_"+ents[i]->Name());
		editorV->addComponent<EditorMasterSyncer>()->init(ents[i],this);
		editorObjects.emplace(ents[i],editorV);
	}
	activateEditorObjects();
}

void EditorGame::destoryEditorObjects()
{
	deactiveEditorObjects();
	while(editorObjects.size() > 0) {
		gameManager.RemoveEntity(editorObjects.getRandomValue());
	}
	editorObjects.clear();
}

void EditorGame::activateEditorObjects()
{
	gameManager.SelectorFunction(isEditorObject);
	editorObjects.foreachVal([](Entity*e){e->SetActive(true);});
}

void EditorGame::deactiveEditorObjects()
{
	gameManager.SelectorFunction(isGameObject);
	editorObjects.foreachVal([](Entity*e){e->SetActive(false);});
}

Entity * EditorGame::getEditorVersion(Entity * gameEntity)
{
	return editorObjects.getVal(gameEntity);
}

template<>
RenderableComponent * EditorGame::scoper::addComponent()
{
	auto ret = currentlySelectedEntity->addComponent<RenderableComponent>();
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

void EditorGame::scoper::EditName(std::string newName)
{
	currentlySelectedEntity->Name(newName);
}

Entity * EditorGame::scoper::GetCurrent() const
{
	return currentlySelectedEntity;
}

void EditorGame::scoper::DuplicateCurrent()
{
	currentlySelectedEntity->Clone();
}
