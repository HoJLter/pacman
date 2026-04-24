#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

enum class SceneID {
	Initial,
	DotCountInput,
	DotInput,
	Result,
	Tests
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