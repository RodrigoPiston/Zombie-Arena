#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum ZombieType {
	BLOATER,
	CHASER,
	CRAWLER
};

class Zombie
{
private:
	
	// How fast is each zombie type
	const float BLOATER_SPEED = 50;
	const float CHASER_SPEED = 95;
	const float CRAWLER_SPEED = 30;

	// How tough is each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 50;
	const int OFFSET = 500 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

public:
	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, ZombieType type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLoaction);

};

