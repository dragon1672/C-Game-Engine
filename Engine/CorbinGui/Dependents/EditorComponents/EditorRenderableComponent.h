#pragma once

#include <Engine/Entity/Components/RenderableComponent.h>

class EditorRenderableComponent : public Component {
public:
	RenderableComponent * gameInstance;
	RenderableComponent * editorInstance;
	EditorRenderableComponent();
	EditorRenderableComponent(std::string name, RenderableComponent * game, RenderableComponent * editor);
	void setName(std::string name);


	virtual bool isValid();

	void sync();

	virtual void earlyUpdate();

	virtual void init();

	virtual void start();

	std::vector<std::string> getErrors();

};