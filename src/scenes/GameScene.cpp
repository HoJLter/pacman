#include "scenes/GameScene.h"
#include "utils/Log.h"

GameScene::GameScene(GameContext& context, ISceneSwitcher& ss) :
	Scene(context, ss)
{
	context.assetsManager.playSound("start");
	Log::debug(std::to_string(context.settings.viewWidth));
}


void GameScene::handleEvent(const sf::Event& event) {
}


void GameScene::update() {

}

void GameScene::render() {

}