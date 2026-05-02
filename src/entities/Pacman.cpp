#include "entities/Pacman.h"
#include "utils/Log.h"


Pacman::Pacman(GameContext& context, float scale) :
	context(context),
	scale(scale),
	speedPerSec(400.f),
	pacmanMoveTexture(context.assetsManager.getTexture("pacmanMove")),
	pacmanMove(
		pacmanMoveTexture, // texture
		2,                 // frames
		16,                // frameWidth
		16,                // frameHeight
		0,                 // row
		0.1f			   // animation speed (in seconds)
	),
	tilemap(context.assetsManager.getTilemap())
{
	curDirection = MoveDirection::None;

	int TS = 16;
	sf::Vector2f viewSize = context.window.getView().getSize();
	int tilesY = context.assetsManager.getTilemap().size();
	int tilesX = context.assetsManager.getTilemap()[0].size();
	
	sf::View view = context.window.getView();

	sf::Vector2f viewCenter = view.getCenter();

	float viewLeft = viewCenter.x - viewSize.x / 2.0f;
	float viewTop = viewCenter.y - viewSize.y / 2.0f;

	mapOffsetX = viewLeft + (viewSize.x - (tilesX * 16 * scale)) / 2.0f;
	mapOffsetY = viewTop + (viewSize.y - (tilesY * 16 * scale)) / 2.0f;

	Log::debug("Pacman has been created");
	pacman.setTexture(pacmanMoveTexture);
	pacman.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
	pacman.setPosition({context.settings.viewWidth/2.f, context.settings.viewHeight/2.f});
	pacman.setScale({ scale, scale });
}

void Pacman::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Up: {
				pacmanMove.changeRow(2);
				curDirection = MoveDirection::Up;
				break;
			}
			case sf::Keyboard::Down: {
				pacmanMove.changeRow(3);
				curDirection = MoveDirection::Down;
				break;
			}
			case sf::Keyboard::Left: {
				pacmanMove.changeRow(1);
				curDirection = MoveDirection::Left;
				break;
			}
			case sf::Keyboard::Right: {
				pacmanMove.changeRow(0);
				curDirection = MoveDirection::Right;
				break;
			}
		}
	}
}
void Pacman::update(sf::RenderWindow& window, float dt) {
	sf::Vector2f curPosition = pacman.getPosition();
	sf::Vector2f newPosition = curPosition;

	switch (curDirection) {
	case MoveDirection::Up:
		newPosition.y -= speedPerSec * dt;
		break;

	case MoveDirection::Down:
		newPosition.y += speedPerSec * dt;
		break;

	case MoveDirection::Left:
		newPosition.x -= speedPerSec * dt;
		break;

	case MoveDirection::Right:
		newPosition.x += speedPerSec * dt;
		break;
	}


	float size = 16.0f * scale;
	float inset = 3.f * scale; 

	sf::Vector2f p1 = { newPosition.x + inset, newPosition.y + inset };
	sf::Vector2f p2 = { newPosition.x + size - inset, newPosition.y + inset };
	sf::Vector2f p3 = { newPosition.x + inset, newPosition.y + size - inset };
	sf::Vector2f p4 = { newPosition.x + size - inset, newPosition.y + size - inset };

	sf::Vector2u t1 = posToSqr(p1);
	sf::Vector2u t2 = posToSqr(p2);
	sf::Vector2u t3 = posToSqr(p3);
	sf::Vector2u t4 = posToSqr(p4);
	sf::Vector2u center = posToSqr({ newPosition.x + size/ 2.f, newPosition.y + size/ 2.f });


	auto isFree = [&](sf::Vector2u pos) {
		return pos.y < tilemap.size() &&
			pos.x < tilemap[0].size() &&
			tilemap[pos.y][pos.x] != tile::Wall &&
			tilemap[pos.y][pos.x] != tile::Border;
		};

	sf::Vector2u moneyPos;
	auto isMoney = [&](sf::Vector2u pos) {
		if (pos.y < tilemap.size() &&
			pos.x < tilemap[0].size() &&
			tilemap[pos.y][pos.x] == tile::Money) {
				moneyPos = pos;
				return true;
		}
		return false;
		};

	sf::Vector2u tpPos;
	auto isTeleport = [&](sf::Vector2u pos) {
		if (pos.y < tilemap.size() &&
			pos.x < tilemap[0].size() &&
			tilemap[pos.y][pos.x] == tile::Teleport) {
			tpPos = pos;
			return true;
		}
		return false;
		};


	if (isFree(t1) && isFree(t2) && isFree(t3) && isFree(t4)) {
		pacman.setPosition(newPosition);
	}

	if (isMoney(center)) {
		context.eventQueue.push(GameEvent{ EventType::CoinCollected, {moneyPos.x, moneyPos.y} });
		Log::debug("Event CoinCollected has been pushed");
	};

	if (isTeleport(center)) {
		sf::Vector2u rightTpPos = { 31, 9 };
		sf::Vector2u leftTpPos = { 0, 9 };
		if (tpPos.x == leftTpPos.x &&
			tpPos.y == leftTpPos.y) {
			Log::debug("Left teleport has been used");
			pacman.setPosition({
				static_cast<float>((rightTpPos.x-1) * 16 * scale + size / 2),
				static_cast<float>(rightTpPos.y*16*scale + size/2)});
		}
		else if (tpPos.x == rightTpPos.x &&
			tpPos.y == rightTpPos.y){
			Log::debug("Right teleport has been used");
			pacman.setPosition({ 
				static_cast<float>((leftTpPos.x+2) * 16 * scale + size / 2),
				static_cast<float>(leftTpPos.y*16*scale + size / 2)});
		}
	}

	pacmanMove.update(dt);
	pacmanMove.applyToSprite(pacman);
}

sf::Vector2u Pacman::posToSqr(sf::Vector2f pos) {
	int TS = 16;
	sf::Vector2u sqrNum = {
		static_cast<unsigned>(((pos.x - mapOffsetX)) / (16 * scale)),
		static_cast<unsigned>(((pos.y - mapOffsetY)) / (16 * scale))
	};

	return sqrNum;
}



void Pacman::render(sf::RenderWindow& window) {
	window.draw(pacman);
}