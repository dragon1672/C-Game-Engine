#include "EditorMasterSyncer.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Systems/GameObjectManager.h>

//events
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>

REGISTER_COMPONENT(EditorMasterSyncer);

void EditorMasterSyncer::lateUpdate()
{
	if(toSyncWith == nullptr) return;
	auto theirRens = toSyncWith->getComponents<RenderableComponent>();
	while(theirRens.size() > myRenderables.size()) {
		myRenderables.push_back(Parent()->addComponent<RenderableComponent>());
	}
	while(theirRens.size() < myRenderables.size()) {
		Parent()->removeComponent(myRenderables.back());
		myRenderables.pop_back();
	}
	for (uint i = 0; i < theirRens.size(); i++)
	{
		syncRens(theirRens[i],myRenderables[i]);
	}
	toSyncWith->getTrans()->CopyInto(Parent()->getTrans());
	Parent()->Parent(toSyncWith->Parent());
}

void EditorMasterSyncer::syncRens(RenderableComponent * gameRen, RenderableComponent * editorRen)
{
	editorRen->Geo(gameRen->Geo());
	editorRen->visable = gameRen->visable;
	editorRen->objUniforms = gameRen->objUniforms;
	editorRen->uniformParameters = gameRen->uniformParameters;
	editorRen->active = gameRen->active;
	editorRen->Shader(resourceManager.getDefault<ShaderProgram>());
}

EditorMasterSyncer::EditorMasterSyncer() : toSyncWith(nullptr)
{
	eventManager.Subscribe<EntityRemovedEvent>([this](EventData*d,Object*) {
		EntityRemovedEvent * data = (EntityRemovedEvent*)d;
		if(data->entity == toSyncWith) {
			gameManager.RemoveEntity(this->Parent());
		}
	});
}
