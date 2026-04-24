#pragma once
#include "SFML/Graphics.hpp"
#include "core/ISceneSwitcher.h"

class Scene {
public:
	ISceneSwitcher& sceneSwitcher;

	Scene(ISceneSwitcher& ss) : sceneSwitcher(ss) {};
	virtual ~Scene() = default;

	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};