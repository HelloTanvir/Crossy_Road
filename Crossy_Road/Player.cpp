#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 10.f;
	this->playerLevel = 0;
	this->playerLives = 1;
	this->playerLivesMax = 3;
}

void Player::initShape()
{
	this->shape.setSize(sf::Vector2f(20.f, 50.f));
	this->shape.setFillColor(sf::Color::Green);
}

Player::Player()
{
	this->shape.setPosition(sf::Vector2f(200.f, 600.f));

	this->initVariables();
	this->initShape();
}

Player::Player(float x = 200.f, float y = 600.f)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

const int Player::getPlayerLevel() const
{
	return this->playerLevel;
}

const int Player::getPlayerLives() const
{
	return this->playerLives;
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->shape.move(0.f, -movementSpeed);
		this->updatePlayerLevel();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->shape.move(0.f, movementSpeed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->shape.move(-movementSpeed, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->shape.move(movementSpeed, 0.f);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);

	// Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	// Top (300.f, because of the player needs to see roads coming)
	if (this->shape.getGlobalBounds().top <= 300.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 300.f);

	// Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::updatePlayerLevel()
{
	this->playerLevel++;
}

void Player::updatePlayerLives()
{
	this->playerLives++;
}

void Player::resetPlayerPosition()
{
	this->shape.setPosition(200.f, 600.f);
}

void Player::update(const sf::RenderTarget* target)
{
	// Keyboard input
	this->updateInput();

	// Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
