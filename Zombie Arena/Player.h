#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {

private: 
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	// Where is the player
	Vector2f m_Position;

	// Sprite to load the texture from GPU
	Sprite m_Sprite;

	// And a texture
	Texture m_Texture;

	// What is the screen resolution
	Vector2f m_Resolution;

	// What size is the current arena
	IntRect m_Arena;

	// How big is each tile of the arena
	int m_TileSize;

	// Wich direction(s) is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// Current player health
	int m_Health;

	// Maximum health the palyer can have
	int m_MaxHealth;

	// When was the player last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;

public:
	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// Call this at the end of every game
	void resetPayerStats();

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	// Where is the center of the player
	Vector2f getCenter();

	// What angle is the player facing
	float getRotation();

	FloatRect getPosition();

	// Send a copy of the sprite to the main fucntion
	Sprite getSprite();

	// Move the player
	void moveLeft();

	// Move the player
	void moveRight();

	// Move the player
	void moveUp();
	
	// Move the player
	void moveDown();

	// Move the player
	void stopLeft();

	// Move the player
	void stopRight();

	// Move the player
	void stopUp();

	// Move the player
	void stopDown();

	// Called every frame
	void update(float elapsedTime, Vector2i mousePosition);
		
	// Give the player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

	// How much health has the player currently got?
	int getHealth();

};