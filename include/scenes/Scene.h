#pragma once
#include "SFML/Graphics.hpp"
#include "core/ISceneSwitcher.h"
#include "core/AssetsManager.h"

class Scene {
public:
	ISceneSwitcher& sceneSwitcher;
	AssetsManager& assetsManager;
	
	Scene(ISceneSwitcher& ss, AssetsManager& am) : 
		sceneSwitcher(ss),
		assetsManager(am){};
	virtual ~Scene() = default;

	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};