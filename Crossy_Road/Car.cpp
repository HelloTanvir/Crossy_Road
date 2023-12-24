#include "Car.h"

void Car::initShape(const sf::RenderWindow& window, int carNumber, float y)
{
	this->shape.setSize(sf::Vector2f(40.f, 20.f));
	this->shape.setFillColor(sf::Color::Blue);

	float carPositionX = static_cast<float>(
		window.getSize().x + this->shape.getGlobalBounds().width + ((carNumber) * this->shape.getGlobalBounds().width * 1.5) + 100.f
		);
	float carPositionY = y;

	if (carNumber % 2 == 0)
		carPositionY -= this->shape.getGlobalBounds().height;
	else
		carPositionY += this->shape.getGlobalBounds().height;

	this->shape.setPosition(sf::Vector2f(
		carPositionX,
		carPositionY
	));
}

Car::Car(const sf::RenderWindow& window, int carNumber, float y)
{
	this->initShape(window, carNumber, y);
}

Car::~Car()
{
}

const sf::RectangleShape Car::getShape() const
{
	return this->shape;
}

void Car::move(const float x, const float y)
{
	this->shape.move(x, y);
}

bool Car::hasCollided(const sf::RectangleShape& player)
{
	return this->shape.getGlobalBounds().intersects(player.getGlobalBounds());
}

void Car::update()
{
}

void Car::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
