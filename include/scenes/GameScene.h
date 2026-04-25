#pragma once
#include "scenes/Scene.h"
#include "ui/Label.h"
#include "entities/Pacman.h"

class GameScene : public Scene {
private:
	Pacman pacman;
public:
	GameScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(float dt) override;
	void render() override;
};