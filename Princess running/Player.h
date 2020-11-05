#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include "Colider.h"
#include <iostream>
class Player
{
public:
	Player(sf::Texture* texture, sf::Texture* slideTexture,sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation normalAnimation;
	Animation slideAnimation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	sf::Texture* normalTexture, *slideTexture;

	int statePlayer = 0;
	/*
		state = 0 : normal
		state = 1 : silde
	*/
};