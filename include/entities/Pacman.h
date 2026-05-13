#pragma once
#include "SFML/Graphics.hpp"
#include "engine/assets/Animation.h"
#include "engine/GameContext.h"
#include "entities/IMap.h"
#include "entities/EntityData.h"


class Pacman {
private:
	GameContext& context;
	sf::Sprite pacman;

	Animation pacmanMove;
	sf::Texture pacmanMoveTexture;
	sf::Clock animationClock;
	
	MoveDirection curDirection;
	MoveDirection nextDirection;

	float speedPerSec;
	float scale;

	IMap& map;
public:
	Pacman(GameContext& context, IMap&, sf::Vector2u initPos, float scale);

	sf::Vector2u getCurPos();
	MoveDirection getCurDir() { return curDirection; }

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};