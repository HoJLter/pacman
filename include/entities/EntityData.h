#pragma once
#include <string>

enum class MoveDirection {
	Up,
	Down,
	Left,
	Right,
	None
};

enum class GhostType {
	Blinky,
	Pinky,
	Inky,
	Clyde
};

std::string mapGhostType(GhostType type);
