#pragma once

#include <Engine/Entity/Components/RenderableComponent.h>

class EditorRenderableComponent : public Component {
	RenderableComponent * gameInstance;
	RenderableComponent * editorInstance;
public:
	EditorRenderableComponent(std::string name="", RenderableComponent * game = nullptr, RenderableComponent * editor = nullptr);
	void init(std::string name, RenderableComponent * gameInstance, RenderableComponent * editorInstance);


	virtual bool isValid();

	void sync();

	virtual void earlyUpdate();

	virtual void init();

	virtual void start();

	std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	virtual bool CopyInto(Component* that);

};