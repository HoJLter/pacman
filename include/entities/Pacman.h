#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"

enum class MoveDirection {
	Up,
	Down,
	Left,
	Right,
};

class Pacman {
private:
	GameContext& context;

	sf::Texture pacmanMoveTexture;
	Animation pacmanMove;

	sf::Sprite pacman;
	MoveDirection curDirection;

	sf::Clock animationClock;
	float speedPerSec;

public:
	Pacman::Pacman(GameContext& context);

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};