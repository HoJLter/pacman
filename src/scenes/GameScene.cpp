#include "scenes/GameScene.h"
#include "utils/Log.h"

GameScene::GameScene(GameContext& context, ISceneSwitcher& ss) :
	Scene(context, ss),
	pacman(context),
	blinky(context, GhostType::Blinky),
	pinky(context, GhostType::Pinky),
	inky(context, GhostType::Inky),
	clyde(context, GhostType::Clyde)

{
	context.assetsManager.playSound("start");
	Log::debug(std::to_string(context.settings.viewWidth));
}


void GameScene::handleEvent(const sf::Event& event) {
	pacman.handleEvent(event);

	blinky.handleEvent(event);
	pinky.handleEvent(event);
	inky.handleEvent(event);
	clyde.handleEvent(event);

}


void GameScene::update(float dt) {
	pacman.update(context.window, dt);

	blinky.update(context.window, dt);
	pinky.update(context.window, dt);
	inky.update(context.window, dt);
	clyde.update(context.window, dt);

}

void GameScene::render() {
	pacman.render(context.window);

	blinky.render(context.window);
	pinky.render(context.window);
	inky.render(context.window);
	clyde.render(context.window);
}