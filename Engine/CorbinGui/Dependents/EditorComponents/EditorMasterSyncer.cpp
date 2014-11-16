#include "EditorMasterSyncer.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Components/RenderableComponent.h>

REGISTER_COMPONENT(EditorMasterSyncer);

void EditorMasterSyncer::lateUpdate()
{
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
