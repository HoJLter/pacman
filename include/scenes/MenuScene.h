#pragma once
#include "scenes/Scene.h"
#include "ui/Button.h"


class MenuScene : public Scene {
private:
	Button startButton;
public:
	MenuScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
};