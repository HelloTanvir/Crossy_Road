#pragma once

#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

class Player
{
private:
	// Variables
	sf::RectangleShape shape;
	float movementSpeed;
	int playerLevel;
	int playerLives;

	// Initialization
	void initVariables();
	void initShape();

public:
	// Constructors and destructors
	Player();
	Player(float x, float y);
	virtual ~Player();

	// Variables
	int playerLivesMax;

	// Accessors
	const sf::RectangleShape getShape() const;
	const int getPlayerLevel() const;
	const int getPlayerLives() const;

	// Functions
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updatePlayerLevel();
	void updatePlayerLives();
	void resetPlayerPosition();
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

