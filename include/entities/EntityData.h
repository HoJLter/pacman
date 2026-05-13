#pragma once
#include <string>
#include "SFML/Graphics.hpp"

enum class MoveDirection {
	Up,
	Down,
	Left,
	Right,
	None
};

MoveDirection calcReverseDir(MoveDirection dir);
sf::Vector2i dirToVector(MoveDirection dir);
std::string mapDirection(MoveDirection dir);

enum class GhostType {
	Blinky,
	Pinky,
	Inky,
	Clyde,
	None
};

std::string mapGhostType(GhostType type);
