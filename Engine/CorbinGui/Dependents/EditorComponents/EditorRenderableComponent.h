#pragma once

#include <Engine/Entity/Components/RenderableComponent.h>

class EditorRenderableComponent : public Component {
public:
	RenderableComponent * gameInstance;
	RenderableComponent * editorInstance;
	EditorRenderableComponent(const char * myName, RenderableComponent * game, RenderableComponent * editor) {
		this->name = myName;
		this->gameInstance = game;
		this->editorInstance = editor;
	}


	virtual bool isValid()
	{
		return gameInstance->isValid();
	}

	virtual void earlyUpdate()
	{
		editorInstance->material = gameInstance->material;
		editorInstance->geo = gameInstance->geo;
		editorInstance->visable = gameInstance->visable;
	}

};