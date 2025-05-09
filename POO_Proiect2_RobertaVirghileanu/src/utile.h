#pragma once
#include "Ghost.h"
#include <SFML/Graphics.hpp>

// funcție pentru actualizarea fantomelor
void updateGhosts(Ghost* ghosts[], int ghostCount, const sf::Vector2i& playerPos);

// funcție pentru desenarea fantomelor
void drawGhosts(Ghost* ghosts[], int ghostCount, sf::RenderWindow& window);

class Util {
public:
    static const float TILE_SIZE;  // dimensiunea constantă a tile-ului
};
