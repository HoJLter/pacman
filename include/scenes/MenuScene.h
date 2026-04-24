#pragma once
#include "scenes/Scene.h"
#include "ui/Button.h"


class MenuScene : public Scene {
private:
	Button startButton;
public:
	MenuScene(sf::Vector2u windowSize, ISceneSwitcher& ss, AssetsManager& am);
	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};