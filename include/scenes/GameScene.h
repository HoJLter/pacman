#pragma once
#include "entities/Maze.h"
#include "scenes/Scene.h"
#include "ui/Label.h"
#include "entities/Pacman.h"
#include "entities/Ghost.h"


class GameScene : public Scene {
private:
	float scale;

	Pacman pacman;
	Ghost blinky;
	Ghost pinky;
	Ghost inky;
	Ghost clyde;

	Maze maze;

public:
	GameScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(float dt) override;
	void render() override;
};