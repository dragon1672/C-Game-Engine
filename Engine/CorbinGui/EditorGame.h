#pragma once

#include <Engine/Systems/GameObjectManager.h>
#include <Engine/Tools/Random/StringRandom.h>

class EditorGame {
private:
	std::string uniqueName; // all editor components must have this as the name
	GameObjectManager game;
public:
	EditorGame() {
		uniqueName = Random::rString::Letters(4)+"EditorInstance"+Random::rString::Letters(4);
	}
};