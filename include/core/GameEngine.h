#include "SFML/Graphics.hpp"


class GameEngine {
private:
	sf::RenderWindow window;

	void render();
	void update();
	void handleEvent();
public:
	GameEngine(int width, int height);
	void run();
};