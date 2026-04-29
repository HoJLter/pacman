#pragma once
#include "scenes/Scene.h"
#include "ui/Label.h"
#include "entities/Pacman.h"
#include "entities/Ghost.h"


class GameScene : public Scene {
private:
	Pacman pacman;
	Ghost blinky;
	Ghost pinky;
	Ghost inky;
	Ghost clyde;

public:
	GameScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(float dt) override;
	void render() override;
};