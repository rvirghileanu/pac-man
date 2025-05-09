#include "utile.h"

void updateGhosts(Ghost* ghosts[], int ghostCount, const sf::Vector2i& playerPos) {
    for (int i = 0; i < ghostCount; i++) {
        ghosts[i]->update(playerPos);  // apel virtual pentru fiecare tip de fantomă
    }
}

void drawGhosts(Ghost* ghosts[], int ghostCount, sf::RenderWindow& window) {
    for (int i = 0; i < ghostCount; i++) {
        ghosts[i]->draw(window);  // apel virtual pentru fiecare tip de fantomă
    }
}

const float Util::TILE_SIZE = 32.0f;  // definirea valorii pentru TILE_SIZE
