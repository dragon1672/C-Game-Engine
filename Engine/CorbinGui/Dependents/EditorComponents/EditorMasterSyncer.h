#pragma once

#include <Engine/Entity/Component.h>
#include <ExportHeader.h>
#include <vector>


class RenderableComponent;
class ENGINE_SHARED MAKE_COMPONENT_CLASS(EditorMasterSyncer) {
	Entity * toSyncWith;
	std::vector<RenderableComponent*> myRenderables;
public:
	EditorMasterSyncer();
	void init(Entity * that) {
		toSyncWith = that;
	}
	void shutdown() {
		toSyncWith = nullptr;
		myRenderables.clear();
	}
	void lateUpdate();
	virtual void ChildSave(Stream& s)
	{
		//throw std::logic_error("Editor Component should not be saved.");
	}

	virtual void ChildLoad(Stream& s)
	{
		//throw std::logic_error("Editor Component should not be Loaded.");
	}

	virtual bool isValid()
	{
		return toSyncWith != nullptr;
	}

	virtual std::vector<std::string> getErrors()
	{
		std::vector<std::string> ret;
		if(!isValid()) ret.push_back("Editor Sync Component not initialized");
		return ret;
	}

	virtual bool CopyInto(Component* that)
	{
		throw std::logic_error("Editor Component, Should not be copied.");
	}

	void syncRens(RenderableComponent * gameRen, RenderableComponent * editorRen);

	Component * getNewInstanceOfCurrentType() {
		return nullptr;
	}

};