#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

enum class SceneID {
	Menu,
	Game
};

struct SharedData {

};

class ISceneSwitcher {
public:
	SharedData shared;
	virtual void requestSwitchScene(SceneID id) = 0;
};