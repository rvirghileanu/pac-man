#include "RandomGhost.h"
// randomGhost este o clasa care moștenește de la clasa de bază Ghost
// randomGhost este un tip de fantomă (Ghost) care se mișcă aleator pe hartă

// constructor (moștenire)
RandomGhost::RandomGhost(float startX, float startY, float tileSize)
    : Ghost(startX, startY, tileSize, sf::Color::Red) {}

// mișcare aleatorie
void RandomGhost::update(const sf::Vector2i& playerPos) {
    int moveDirection = rand() % 4;
    if (moveDirection == 0 && row > 0) {
        row--;
    } else if (moveDirection == 1 && row < 10) {
        row++;
    } else if (moveDirection == 2 && col > 0) {
        col--;
    } else if (moveDirection == 3 && col < 10) {
        col++;
    }

    shape.setPosition(col * tileSize, row * tileSize);
}

// desenare
void RandomGhost::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// constructor virtual (clone)
Ghost* RandomGhost::clone() const {
    return new RandomGhost(*this);
}
