#include "EditorGame.h"
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <CorbinGui/Dependents/EditorComponents/EditorMasterSyncer.h>
#include <Engine/Entity/Entity.h>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>



EditorGame::EditorGame()
{
	isEditorObject = [this](Object* o){
		return editorObjects.find(o) != editorObjects.end();
	};
	isGameObject = [this](Object* o){
		return editorObjects.find(o) == editorObjects.end();
	};
	eventManager.Subscribe<EntityRemovedEvent>([this](EventData*d,Object*) {
		EntityRemovedEvent * data = (EntityRemovedEvent*)d;
		if(editorObjects.find(data->entity) != editorObjects.end()) {
			editorObjects.erase(data->entity);
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
	editorV->addComponent<EditorMasterSyncer>()->init(curr);
	editorObjects.emplace(editorV);
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
	editorObjects.emplace(EditorCamera);
	for (uint i = 0; i < ents.size(); i++)
	{
		auto editorV = gameManager.AddEntity("Editor_"+ents[i]->Name());
		editorV->addComponent<EditorMasterSyncer>()->init(ents[i]);
		editorObjects.emplace(editorV);
	}
	activateEditorObjects();
}

void EditorGame::destoryEditorObjects()
{
	deactiveEditorObjects();
	while(editorObjects.size() > 0) {
		std::unordered_set<Object*>::iterator itr = editorObjects.begin();
		gameManager.RemoveEntity((Entity*)(*itr));
	}
	editorObjects.clear();
}

void EditorGame::activateEditorObjects()
{
	gameManager.SelectorFunction(isEditorObject);
	//camManager.ActiveCam(EditorCamera->getComponent<CameraComponent>());
	for(auto e : editorObjects) {
		((Entity*)e)->SetActive(true);
	}
}

void EditorGame::deactiveEditorObjects()
{
	gameManager.SelectorFunction(isGameObject);
	for(auto e : editorObjects) {
		((Entity*)e)->SetActive(false);
	}
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
