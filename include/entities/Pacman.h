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
	int TS;

	MoveDirection curDirection;
	float speedPerSec;
	float scale;

	Animation pacmanMove;
	sf::Texture pacmanMoveTexture;
	sf::Clock animationClock;
	
	std::vector<std::vector<int>>& tilemap;
	IMap& map;
public:
	Pacman(GameContext& context, IMap&, float scale);

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};