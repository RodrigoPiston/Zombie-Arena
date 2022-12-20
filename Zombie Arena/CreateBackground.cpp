#include "ZombieArena.h"
#include <time.h>

int createBackground(VertexArray& rVA, IntRect arena) {
	// Anything we doto rVA we are really doing to background( in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	// Calculate the width and height of the world in the number of tiles not pixels.
	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	// Set the primitive tipe for the vertexArray
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int width = 0; width < worldWidth; width++)
	{
		for (int height = 0; height < worldHeight; height++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position =
				Vector2f(width * TILE_SIZE, height * TILE_SIZE);

			rVA[currentVertex + 1].position =
				Vector2f((width * TILE_SIZE) + TILE_SIZE, 
					height * TILE_SIZE);

			rVA[currentVertex + 2].position =
				Vector2f((width * TILE_SIZE) + TILE_SIZE, 
					(height * TILE_SIZE) + TILE_SIZE);

			rVA[currentVertex + 3].position =
				Vector2f(width * TILE_SIZE, 
					(height * TILE_SIZE) + TILE_SIZE);

			// Define the position in the Texture for current quad
			// Either grass, stone, brush or wall
			if (height == 0 || height == worldHeight - 1 ||
				width == 0 || width == worldWidth - 1) {

				// Use the wall texture on boundaries
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);

			}
			else {
				// Use a random floor texture
				srand((int)time(0) + height * width - height);
				// Mud or grass
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords =
					Vector2f(0, verticalOffset);

				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, verticalOffset);

				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + verticalOffset);
			}

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}