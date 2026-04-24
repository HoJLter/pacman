#pragma once
#include "scenes/Scene.h"


class GameScene : public Scene {
private:
public:
	GameScene(sf::Vector2u windowSize, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};