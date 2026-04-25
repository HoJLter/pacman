

class Entity {
public:
	virtual void handleEvent(const sf::Event& event) {};
	virtual void update(sf::RenderWindow& window) {};
	virtual void render(sf::RenderWindow& window) = 0;


};