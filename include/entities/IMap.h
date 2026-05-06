#pragma once
#include "SFML/Graphics.hpp"
#include "entities/EntityData.h"


class IMap {
public:
	virtual ~IMap() = default;

	virtual sf::Vector2u getSize() = 0;
	virtual const std::vector<std::vector<int>>& getTilemap() = 0;

	virtual sf::Vector2u posToGrid(sf::Vector2f pos) = 0;
	virtual sf::Vector2f gridToPos(sf::Vector2u gridPos) = 0;

	virtual bool isFree(sf::Vector2u pos) = 0;
	virtual bool isMoney(sf::Vector2u pos) = 0;
	virtual bool isTeleport(sf::Vector2u pos) = 0;

	virtual sf::Vector2u getSingleTile(tile spawnTile) = 0;
};


