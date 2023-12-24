#include "Road.h"

void Road::initShape(const sf::RenderWindow& window, int roadNumber)
{
	this->shape.setSize(sf::Vector2f(800.f, 200.f));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(sf::Vector2f(
		0.f,
		static_cast<float>(
			(window.getSize().y / 2) - this->shape.getGlobalBounds().height -  (roadNumber * this->shape.getGlobalBounds().height * 1.5)
		)
	));
}

Road::Road(const sf::RenderWindow& window, int roadNumber)
{
	this->initShape(window, roadNumber);
}

Road::~Road()
{
}

const sf::RectangleShape Road::getShape() const
{
	return this->shape;
}

void Road::move(const float x, const float y)
{
	this->shape.move(x, y);
}

void Road::update()
{
}

void Road::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
