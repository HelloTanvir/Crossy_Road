#pragma once

#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

class Car
{
private:
	// Variables
	sf::RectangleShape shape;

	// Initialization
	void initShape(const sf::RenderWindow& window, int carNumber, float y);

public:
	// Constructors and destructors
	Car(const sf::RenderWindow& window, int carNumber, float y = 0.f);
	virtual ~Car();

	// Accessors
	const sf::RectangleShape getShape() const;

	// Functions
	void move(const float x, const float y);
	bool hasCollided(const sf::RectangleShape& player);
	void update();
	void render(sf::RenderTarget* target);
};

