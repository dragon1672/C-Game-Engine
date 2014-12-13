#pragma once

#include <Engine/Systems/GameObjectManager.h>

#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Entity/Components/ScriptComponent.h>
#include <ExportHeader.h>
#include <Engine/Tools/BiHashMap.h>

class ENGINE_SHARED EditorGame {
private:
	Entity * currentlySelectedEntity;
	Entity * EditorCamera;
	//game entity,editor entity
	BiHashMap<Entity *,Entity *> editorObjects;
	std::function<bool(Entity*)> isEditorObject;
	std::function<bool(Entity*)> isGameObject;
public:
	inline std::function<bool(Entity*)>& IsEditorObject() { return isEditorObject; }
	inline std::function<bool(Entity*)>& IsGameObject()   { return isGameObject; }
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
		Entity * GetCurrent() const;
		void EditName(std::string newName);

		void DuplicateCurrent();

		void Parent(const char * name);

	} currentEntity;


	void init();
	void initGl();
	void start();
	void update();
	void paint(std::function<void(int startX,int startY,int width,int height)> setViewPort);
	void AddEntity(std::string name);
	void RemoveCurrentEntity();

	void deactiveEditorObjects();
	void activateEditorObjects();
	void destoryEditorObjects();
	void createEditorObjects();
};