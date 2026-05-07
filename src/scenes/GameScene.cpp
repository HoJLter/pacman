#include "scenes/GameScene.h"
#include "utils/Log.h"
	
GameScene::GameScene(GameContext& context, ISceneSwitcher& ss) :
	Scene(context, ss),
	scale(3.5f),
	map(context, scale),
	pacman(context, map, map.getSingleTile(tile::PacmanSpawn), scale),
	blinky(context, map, GhostType::Blinky, map.getSingleTile(tile::BlinkySpawn), scale),
	pinky(context, map, GhostType::Pinky, map.getSingleTile(tile::PinkySpawn), scale),
	inky(context, map, GhostType::Inky, map.getSingleTile(tile::InkySpawn), scale),
	clyde(context, map, GhostType::Clyde, map.getSingleTile(tile::ClydeSpawn), scale),
	score("Score: ", { 100.f, 20.f }, 16, sf::Color::Yellow, context.assetsManager)
{
	sf::Vector2u winSize = context.window.getSize();
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
	map.update(context.window, dt);
	score.setString("Score " + std::to_string(context.data.score));

	blinky.update(context.window, dt);
	pinky.update(context.window, dt);
	inky.update(context.window, dt);
	clyde.update(context.window, dt);
}

void GameScene::render() {

	
	pacman.render(context.window);
	map.render(context.window);

	blinky.render(context.window);
	pinky.render(context.window);
	inky.render(context.window);
	clyde.render(context.window);

	score.render(context.window);
}

bool GameScene::checkLoose() {
	return (pacman.getCurPos() == blinky.getCurPos() ||
			pacman.getCurPos() == pinky.getCurPos() ||
			pacman.getCurPos() == inky.getCurPos() ||
			pacman.getCurPos() == clyde.getCurPos());
}
