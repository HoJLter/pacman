#include "utils/Log.h"
#include "engine/core/GameEngine.h"

int main() {
	Log::setLogger(LoggerType::Console);
	GameEngine game(1600, 900);
	game.run();
}