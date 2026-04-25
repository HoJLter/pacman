#pragma once
#include "scenes/Scene.h"
#include "ui/Label.h"

class GameScene : public Scene {
private:
public:
	GameScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
};