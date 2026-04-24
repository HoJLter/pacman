#pragma once
#include "scenes/Scene.h"
#include "ui/Button.h"


class MenuScene : public Scene {
private:
	Button startButton;
public:
	MenuScene(sf::Vector2u windowSize, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};