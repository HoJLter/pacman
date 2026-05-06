#pragma once
#include "SFML/Graphics.hpp"


struct SpawnCoords {
	sf::Vector2u pacman;
	sf::Vector2u blinky;
	sf::Vector2u pinky;
	sf::Vector2u inky;
	sf::Vector2u clyde;
};

class IMap {

public:
	virtual ~IMap() = default;

	virtual sf::Vector2u getSize() = 0;
	virtual sf::Vector2u posToGrid(sf::Vector2f pos) = 0;
	virtual sf::Vector2f gridToPos(sf::Vector2i gridPos) = 0;
};