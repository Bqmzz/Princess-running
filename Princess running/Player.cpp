#include "Player.h"

Player::Player(sf::Texture* texture, sf::Texture* slideTexture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	normalAnimation(texture, imageCount, switchTime),
	slideAnimation(slideTexture, sf::Vector2u(4, 1), switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(150.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);

	this->slideTexture = slideTexture;
	this->normalTexture = texture;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->statePlayer = 1;
	}
	else {
		this->statePlayer = 0;
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

	switch (this->statePlayer)
	{
	case 0:
		body.setTexture(this->normalTexture);
		normalAnimation.Update(row, deltaTime, faceRight);
		body.setTextureRect(normalAnimation.uvRect);
		this->body.setScale(sf::Vector2f(1, 1));
		break;
	case 1:
		body.setTexture(this->slideTexture);
		slideAnimation.Update(row, deltaTime, faceRight);
		body.setTextureRect(slideAnimation.uvRect);
		this->body.setScale(sf::Vector2f(0.7, 0.8));
		//this->body.setPosition(this->body.getPosition().x, 400.0f);
		//std::cout << "do state1" << std::endl;
		break;
	default:
		break;
	}
	
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