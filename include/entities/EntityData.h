#pragma once
#include <string>

enum class MoveDirection {
	Up,
	Down,
	Left,
	Right,
	None
};

MoveDirection calcReverseDir(MoveDirection cur) {
	switch (cur) {
		case MoveDirection::Up: {
			return MoveDirection::Down;
		}
		case MoveDirection::Down: {
			return MoveDirection::Up;
		}
		case MoveDirection::Right: {
			return MoveDirection::Left;
		}
		case MoveDirection::Left: {
			return MoveDirection::Down;
		}
	}
}

enum class GhostType {
	Blinky,
	Pinky,
	Inky,
	Clyde
};

std::string mapGhostType(GhostType type);
