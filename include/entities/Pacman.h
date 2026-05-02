#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"
#include "entities/EntityData.h"


class Pacman {
private:
	GameContext& context;

	sf::Texture pacmanMoveTexture;
	Animation pacmanMove;

	sf::Sprite pacman;
	MoveDirection curDirection;

	sf::Clock animationClock;
	float speedPerSec;
	float scale;

	float mapOffsetX;
	float mapOffsetY;

	std::vector<std::vector<int>>& tilemap;
	sf::Vector2u posToSqr(sf::Vector2f pos);
public:
	Pacman(GameContext& context, float scale);

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};