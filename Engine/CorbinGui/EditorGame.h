#pragma once

#include <Engine/Systems/GameObjectManager.h>

#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Entity/Components/ScriptComponent.h>
#include <ExportHeader.h>

#include <CorbinGui/Dependents/EditorComponents/EditorRenderableComponent.h>

class ENGINE_SHARED EditorGame {
private:
	std::string uniqueName; // all editor components must have this as the name
	GameObjectManager game;
	Entity * currentlySelectedEntity;
public:
	GameObjectManager * Game() { return &game; }
	int width,height;
	EditorGame();

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
		std::vector<Component*> getAllGameComponents();
		MatrixInfo          * getTrans();
		ScriptComponent     * getScript();
		RenderableComponent * getRenderable();
		CameraComponent     * getCamera();
		std::vector<ScriptComponent     *> getAllScripts();
		std::vector<RenderableComponent *> getAllRenderables();
		std::vector<CameraComponent     *> getAllCameras();
		void SetCurrent(Entity * toSet);

		void Parent(const char * name);

	} currentEntity;


	void init() {
		game.init();
	}
	void initGl() {
		game.initGl();
	}
	void start() {
		game.start();
	}
	void update() {
		game.update();
		game.width = width;
		game.height = height;
	}
	void paint() {
		game.paint();
	}
	void AddEntity(const char * name) {
		currentEntity.currentlySelectedEntity = game.AddEntity(name);
	}
};