#pragma once
#include <SFML\Graphics.hpp>
#include "Colider.h"

class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }


private:
	sf::RectangleShape body;
};