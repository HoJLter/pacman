#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

enum class SceneID {
	Menu,
	Game
};

struct SharedData {
	int dotCount;
	sf::ConvexShape contour;
	sf::VertexArray dots;
};

class ISceneSwitcher {
public:
	SharedData shared;
	virtual void requestSwitchScene(SceneID id) = 0;
};