#pragma once
#include "SFML/Graphics.hpp"
#include "engine/GameContext.h"
#include "engine/scene/ISceneSwitcher.h"

class Scene {
public:
	GameContext& context;
	ISceneSwitcher& sceneSwitcher;

	Scene(GameContext& context, ISceneSwitcher& ss) : 
		context(context),
		sceneSwitcher(ss){};
	virtual ~Scene() = default;

	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};