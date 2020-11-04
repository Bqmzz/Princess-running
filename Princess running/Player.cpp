#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(150.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.0f;
	//sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	//movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//movement.x += speed * deltaTime;
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = 0;
		velocity.y = -sqrtf(2.0f * 1000.0f * jumpHeight);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = 0;
		velocity.y = -sqrtf(2.0f * 2000.0f * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 0;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//collision on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision on the top
		velocity.y = 0.0f;
	}
}