#pragma once
#include "SFML/Graphics.hpp"
#include "entities/EntityData.h"


class IMap {
public:
	virtual ~IMap() = default;

	virtual sf::Vector2i getSize() = 0;
	virtual const std::vector<std::vector<int>>& getTilemap() = 0;

	virtual sf::Vector2i posToGrid(sf::Vector2f pos) = 0;
	virtual sf::Vector2f gridToPos(sf::Vector2i gridPos) = 0;

	virtual bool isFree(sf::Vector2i pos) = 0;
	virtual bool isMoney(sf::Vector2i pos) = 0;
	virtual bool isEnergizer(sf::Vector2i pos) = 0;
	virtual bool isTeleport(sf::Vector2i pos) = 0;
	virtual bool isFreeDirection(sf::Vector2i pos, MoveDirection dir) = 0;
	virtual bool isInHouse(sf::Vector2i pos) = 0;
	virtual bool isOnCenter(sf::Vector2f pos) = 0;

	virtual sf::Vector2i getSingleTile(tile spawnTile) = 0;
};


