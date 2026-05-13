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
	score("Score: ", { 100.f, 20.f }, 16, sf::Color::Yellow, context.assetsManager),
	isGameOver(false),
	isWin(false),
	gameOverLabel(
		"GAME OVER",
		{ context.settings.viewWidth / 2.f,
		context.settings.viewHeight / 2 - 300.f },
		100,
		sf::Color::Yellow,
		context.assetsManager
	),
	winLabel(
		"CONGATULATIONS!",
		{ context.settings.viewWidth / 2.f,
		context.settings.viewHeight / 2 - 300.f },
		100,
		sf::Color::Yellow,
		context.assetsManager
	),
	resultScoreLabel(
		"Your score: 000000",
		{ context.settings.viewWidth / 2.f,
		context.settings.viewHeight / 2},
		30,
		sf::Color::Yellow,
		context.assetsManager
	),
	pressEnterLabel(
		"press ENTER to continue",
		{ context.settings.viewWidth / 2.f,
		context.settings.viewHeight - 100.f },
		15,
		sf::Color::Yellow,
		context.assetsManager
	)

{
	sf::Vector2i winSize = {
		static_cast<int>(context.window.getSize().x),
		static_cast<int>(context.window.getSize().y)
	};
	context.assetsManager.playSound("start");
	Log::debug(std::to_string(context.settings.viewWidth));
}


void GameScene::handleEvent(const sf::Event& event) {
	if (!isGameOver) {
		pacman.handleEvent(event);

		blinky.handleEvent(event);
		pinky.handleEvent(event);
		inky.handleEvent(event);
		clyde.handleEvent(event);
	}
	else {
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Enter) {
			sceneSwitcher.requestSwitchScene(SceneID::Menu);
		}
	}
}


void GameScene::update(float dt) {
	if (context.data.lastMoney <= 0) {
		resultScoreLabel.setString("Your score: " + std::to_string(context.data.score));
		context.data.lastMoney++;
		isWin = true;
		isGameOver = true;
	}

	if (!context.eventQueue.empty()) {
		GameEvent event = context.eventQueue.front();
		context.eventQueue.pop();

		if (event.type == EventType::EnergizerCollected) {
			Log::debug("Energizer pickup event");
			blinky.scare();
			pinky.scare();
			inky.scare();
			clyde.scare();
		}
	}

	if (!isGameOver) {
		auto collisionGhost = checkGhostCollision();
		if (collisionGhost.has_value()) {
			if (collisionGhost.value().get().isScared()) {
				context.data.score += 200;
				collisionGhost.value().get().returnToHouse();
			}
			else {
				context.assetsManager.playSound("pacmanDeath");
				isGameOver = true;
				resultScoreLabel.setString("Your score: " + std::to_string(context.data.score));
				context.data.score = 0;
			}
		}
		pacman.update(context.window, dt);
		map.update(context.window, dt);
		score.setString("Score " + std::to_string(context.data.score));

		sf::Vector2i pacmanPos = pacman.getCurPos();
		MoveDirection pacmanDir = pacman.getCurDir();
		blinky.update(context.window, pacmanPos, pacmanDir, {}, dt);
		pinky.update(context.window, pacmanPos, pacmanDir, {}, dt);
		inky.update(context.window, pacmanPos, pacmanDir, blinky.getCurPos(), dt);
		clyde.update(context.window, pacmanPos, pacmanDir, {}, dt);
	}
	else {
		
	}
}

void GameScene::render() {
	if (!isGameOver) {
		pacman.render(context.window);
		map.render(context.window);

		blinky.render(context.window);
		pinky.render(context.window);
		inky.render(context.window);
		clyde.render(context.window);

		score.render(context.window);
	}
	else {
		if (isWin) {
			winLabel.render(context.window);
		}
		else {
			gameOverLabel.render(context.window);
		}
		resultScoreLabel.render(context.window);
		pressEnterLabel.render(context.window);
	}
}

std::optional<std::reference_wrapper<Ghost>> GameScene::checkGhostCollision() {
	sf::Vector2i pacmanPos = pacman.getCurPos();

	if (pacmanPos == blinky.getCurPos())
		return blinky;

	if (pacmanPos == pinky.getCurPos())
		return pinky;

	if (pacmanPos == inky.getCurPos())
		return inky;

	if (pacmanPos == clyde.getCurPos())
		return clyde;


	return std::nullopt;
}