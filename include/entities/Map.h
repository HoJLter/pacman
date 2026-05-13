#pragma once
#include "engine/assets/AssetsManager.h"
#include "entities/IMap.h"
#include "engine/GameContext.h"
#include "utils/Log.h"
#include <vector>

class Map: public IMap {
private:
	sf::Vector2f mapOffset;
	GameContext& context;
	float scale;
	int TS;
	

	std::vector<std::vector<sf::Sprite>> sprites;
	std::vector<std::vector<int>> tilemap;
	sf::Vector2i tilemapSize;

	sf::IntRect calcWallType(int x, int y, tile tiletype);
	sf::Vector2f calcOffset();
public:
	Map(GameContext& context, float scale);

	sf::Vector2i getSize() override { return tilemapSize; };
	const std::vector<std::vector<int>>& getTilemap() override { return tilemap; };

	sf::Vector2i posToGrid(sf::Vector2f pos) override;
	sf::Vector2f gridToPos(sf::Vector2i gridPos) override;
	sf::Vector2i getSingleTile(tile spawnTile) override;

	bool isFree(sf::Vector2i pos) override;
	bool isMoney(sf::Vector2i pos) override;
	bool isTeleport(sf::Vector2i pos) override;
	bool isFreeDirection(sf::Vector2i pos, MoveDirection dir) override;

	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window);
};