#include "engine/core/Algorithms.h"


float calcDistance(sf::Vector2u pos1, sf::Vector2u pos2) {
	int dx = static_cast<int>(pos2.x) - static_cast<int>(pos1.x);
	int dy = static_cast<int>(pos2.y) - static_cast<int>(pos1.y);
	return std::sqrt(dx * dx + dy * dy);
	};