#pragma once
#include "entities/Map.h"
#include "scenes/Scene.h"
#include "ui/Label.h"
#include "entities/Pacman.h"
#include "entities/Ghost.h"


class GameScene : public Scene {
private:
	float scale;

	Map map;

	Pacman pacman;
	Ghost blinky;
	Ghost pinky;
	Ghost inky;
	Ghost clyde;

	Label score;
	Label gameOverLabel;
	Label winLabel;
	Label pressEnterLabel;
	Label resultScoreLabel;

	std::optional<std::reference_wrapper<Ghost>> checkGhostCollision();
	bool isGameOver;
	bool isWin;
public:
	GameScene(GameContext& context, ISceneSwitcher& ss);
	void handleEvent(const sf::Event& event) override;
	void update(float dt) override;
	void render() override;
};