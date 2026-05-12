#include "entities/EntityData.h"


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

sf::Vector2i dirToVector(MoveDirection dir) {
	switch (dir) {
	case MoveDirection::Up:    return { 0, -1 };
	case MoveDirection::Down:  return { 0,  1 };
	case MoveDirection::Left:  return { -1,  0 };
	case MoveDirection::Right: return { 1,  0 };
	}
	return { 0, 0 };
}


std::string mapGhostType(GhostType type) {
	 switch (type) {
	 case GhostType::Blinky: return "blinky";
	 case GhostType::Pinky: return "pinky";
	 case GhostType::Inky: return "inky";
	 case GhostType::Clyde: return "clyde";
	 default: return "unknown";
	 }
}

std::string mapDirection(MoveDirection dir) {
	switch (dir) {
	case MoveDirection::Up: return "Up";
	case MoveDirection::Down: return "Down";
	case MoveDirection::Left: return "Left";
	case MoveDirection::Right: return "Right";
	default: return "unknown";
	}
}

