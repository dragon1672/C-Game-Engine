#pragma once

#include <Engine/Systems/GameObjectManager.h>

#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Entity/Components/ScriptComponent.h>
#include <ExportHeader.h>

class ENGINE_SHARED EditorGame {
private:
	Entity * currentlySelectedEntity;
	Entity * EditorCamera;
	std::unordered_set<Object*> editorObjects;
	std::function<bool(Object*)> isEditorObject;
	std::function<bool(Object*)> isGameObject;
public:
	inline std::function<bool(Object*)>& IsEditorObject() { return isEditorObject; }
	inline std::function<bool(Object*)>& IsGameObject() { return isGameObject; }
	int width,height;
	EditorGame();
	~EditorGame();

	struct ENGINE_SHARED scoper {
	private:
		Entity * currentlySelectedEntity;
		EditorGame * editor;
	public:
		friend EditorGame;

		//adds component to current entity
		template<typename T> T * addComponent() {
			static_assert(false,"Component not valid, unable to add");
		}
		template<> ScriptComponent * addComponent<ScriptComponent>();
		template<> RenderableComponent * addComponent<RenderableComponent>();
		template<> CameraComponent * addComponent<CameraComponent>();
		//returns all the components on the current object
		std::vector<Component*> getAllComponents();
		MatrixInfo          * getTrans();
		ScriptComponent     * getScript();
		RenderableComponent * getRenderable();
		CameraComponent     * getCamera();
		std::vector<ScriptComponent     *> getAllScripts();
		std::vector<RenderableComponent *> getAllRenderables();
		std::vector<CameraComponent     *> getAllCameras();
		void SetCurrent(Entity * toSet);
		Entity * GetCurrent() const { return currentlySelectedEntity; }
		void EditName(std::string newName) {
			currentlySelectedEntity->Name(newName);
		}

		void Parent(const char * name);

	} currentEntity;


	void init();
	void initGl();
	void start();
	void update();
	void paint();
	void AddEntity(std::string name);
	void RemoveCurrentEntity();

	void deactiveEditorObjects() {
		gameManager.SelectorFunction(isGameObject);
		camManager.ActiveCam(nullptr);
	}
	void activateEditorObjects() {
		gameManager.SelectorFunction(isEditorObject);
		camManager.ActiveCam(EditorCamera->getComponent<CameraComponent>());
	}
};