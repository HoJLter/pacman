#include "entities/EntityData.h"


std::string mapGhostType(GhostType type) {
	 switch (type) {
	 case GhostType::Blinky: return "blinky";
	 case GhostType::Pinky: return "pinky";
	 case GhostType::Inky: return "inky";
	 case GhostType::Clyde: return "clyde";
	 default: return "unknown";
	 }
}