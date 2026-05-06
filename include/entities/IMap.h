#pragma once
#include "SFML/Graphics.hpp"


class IMap {
public:
	virtual ~IMap() = default;

	virtual sf::Vector2u getSize() = 0;
	virtual sf::Vector2u posToGrid(sf::Vector2f pos) = 0;
	virtual sf::Vector2f gridToPos(sf::Vector2u gridPos) = 0;
};