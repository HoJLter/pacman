#pragma once
#include "engine/assets/AssetsManager.h"
#include "engine/GameContext.h"
#include <vector>

class Maze() {
private:
	void calculateTile();
	std::vector < std::vector<sf::Sprite> sprites;
	std::vector<std::vector<int>>& tilemap;
public:
	Maze(GameContext& context);
	void handleEvent(const sf::Event& event);
	void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow & window, float dt);
}