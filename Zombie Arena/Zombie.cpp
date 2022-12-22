#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

bool Zombie::hit()
{
	m_Health--;
	if (m_Health < 0) {
		// Dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"assets/graphics/blood.png"
		));
		return true;
	}
	// Not dead yet
	return false;
}

bool Zombie::isAlive()
{
    return m_Alive;
}

void Zombie::spawn(float startX, float startY, ZombieType type, int seed)
{
	switch (type)
	{
	case BLOATER:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets/graphics/bloater.png"));
		m_Speed = BLOATER_SPEED;
		m_Speed = BLOATER_HEALTH;
		break;
	case CHASER:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets/graphics/chaser.png"));
		m_Speed = CHASER_SPEED;
		m_Speed = CHASER_HEALTH;
		break;
	case CRAWLER:
		m_Sprite = Sprite(TextureHolder::GetTexture("assets/graphics/crawler.png"));
		m_Speed = CRAWLER_SPEED;
		m_Speed = CRAWLER_HEALTH;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);

	// Somewhere between 80 and 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;

	// Express this as a fraction of 1
	modifier /= 100; // Now between .7 and 1
	m_Speed *= modifier;

	// Initialize its location
	m_Position.x = startX;
	m_Position.y = startY;

	// Sets its origin to its center
	m_Sprite.setOrigin(25, 25);

	// Set its position
	m_Sprite.setPosition(m_Position);
}

FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
    return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > m_Position.x) {
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y) {
		m_Position.y = m_Position.y + m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x) {
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y) {
		m_Position.y = m_Position.y - m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y, 
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}
