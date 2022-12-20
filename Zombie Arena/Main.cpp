#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"

using namespace sf;
int main()
{
	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	// Start with the game_over state
	State state = State::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Clock for timing everything
	Clock clock;

	// How long has the playing state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to screen coordinates;
	Vector2i mouseScreenPosition;

	// Where is the mouse in relation to the world view;
	Vector2f mouseWorldPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaires of the arena
	IntRect arena;

	// Create the background
	VertexArray background;

	// Load the texture for background vertex array
	Texture textureBackground;
	textureBackground.loadFromFile("assets/graphics/background_sheet.png");

	// The main game loop
	while (window.isOpen()) {
		/*
		* * * * * * * * * *
		Handle Input
		* * * * * * * * * *
		*/

		// Handle events by polling
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				// Pause a game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
					state = State::PLAYING;
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING) {

				}
			}
		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// HAndle WASD while playing
		if (state == State::PLAYING) {
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.moveUp();
			}
			else {
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.moveDown();
			}
			else {
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.moveLeft();
			}
			else {
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.moveRight();
			}
			else {
				player.stopRight();
			}
		}// End WASD while playing

		// Handle the LEVELING up state
		if (state == State::LEVELING_UP) {
			// Handle the player LEVELING UP
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}

			if (state == State::PLAYING) {
				// Prepare the level
				arena.width = 1000;
				arena.height = 1000;
				arena.left = 0;
				arena.top = 0;

				// Pass the vertex array by reference
				// to the create background function
				int tileSize = createBackground(background, arena);
				
				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Reset the clock so there isn't a frame jump
				clock.restart();
			} // END STATE PLAYING
		}// End LEVELING UP

		/*
		* * * * * * * * * *
		Update the frame
		* * * * * * * * * *
		*/
		if (state == State::PLAYING) {

			// Update the delta time
			Time dt = clock.restart();

			// Update the total game time
			gameTimeTotal += dt;

			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				mouseScreenPosition, mainView);

			// Update the player
			player.update(dtAsSeconds, mouseScreenPosition);

			// Make a not of the player new position

			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player
			mainView.setCenter(player.getCenter());

		} // End updating the scene


		/*
		* * * * * * * * * *
		Draw the scene
		* * * * * * * * * *
		*/

		switch (state)
		{
			case State::PAUSED:
				break;
			case State::LEVELING_UP:
				break;
			case State::GAME_OVER:
				break;
			case State::PLAYING:
				window.clear();
				// Set the mainView to be dispalyer in the window
				// Draw everything realted to it
				window.setView(mainView);

				// Draw the background
				window.draw(background, &textureBackground);

				// Draw the player
				window.draw(player.getSprite());
				break;
			default:
				break;
		}
		window.display();

	} // End Game Loop

	return 0;
}
