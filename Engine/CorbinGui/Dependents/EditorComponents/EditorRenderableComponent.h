#pragma once

#include <Engine/Entity/Components/RenderableComponent.h>

class EditorRenderableComponent : public Component {
public:
	RenderableComponent * gameInstance;
	RenderableComponent * editorInstance;
	EditorRenderableComponent();
	EditorRenderableComponent(const char * myName, RenderableComponent * game, RenderableComponent * editor);
	void setName(const char * name);


	virtual bool isValid();

	void sync();

	virtual void earlyUpdate();

	virtual void init();

	virtual void start();

};