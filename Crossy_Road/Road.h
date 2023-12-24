#pragma once

#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

class Road
{
private:
	// Variables
	sf::RectangleShape shape;

	// Initialization
	void initShape(const sf::RenderWindow& window, int roadNumber);

public:
	// Constructors and destructors
	Road(const sf::RenderWindow& window, int roadNumber);
	virtual ~Road();

	// Accessors
	const sf::RectangleShape getShape() const;

	// Functions
	void move(const float x, const float y);
	void update();
	void render(sf::RenderTarget* target);
};

