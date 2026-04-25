#include "scenes/GameScene.h"
#include "utils/Log.h"

GameScene::GameScene(GameContext& context, ISceneSwitcher& ss) :
	Scene(context, ss),
	pacman(context)
{
	context.assetsManager.playSound("start");
	Log::debug(std::to_string(context.settings.viewWidth));
}


void GameScene::handleEvent(const sf::Event& event) {
	pacman.handleEvent(event);
}


void GameScene::update(float dt) {
	pacman.update(context.window, dt);
}

void GameScene::render() {
	pacman.render(context.window);
}