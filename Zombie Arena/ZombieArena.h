#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include "Zombie.h"

using namespace sf;
int createBackground(VertexArray& rva, IntRect arena);
Zombie* createHorde(int numZombies, IntRect arena);