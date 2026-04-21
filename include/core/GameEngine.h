#include "SFML/Grahpics.hpp"


class GameEngine {
	GameEngine(int height, int width);

	sf::RenderWindow window;
private:

	void render();
	void update();
	void handleEvent();
public:
	void run();
};