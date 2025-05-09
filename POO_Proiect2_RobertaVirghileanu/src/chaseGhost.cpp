#include "chaseGhost.h"

// constructor
ChaseGhost::ChaseGhost(float startX, float startY, float tileSize)
    : Ghost(startX, startY, tileSize, sf::Color::Green) {}

// funcția de actualizare (urmărește jucătorul)
void ChaseGhost::update(const sf::Vector2i& playerPos) {
    if (playerPos.x > col) {
        col++;
    } else if (playerPos.x < col) {
        col--;
    }

    if (playerPos.y > row) {
        row++;
    } else if (playerPos.y < row) {
        row--;
    }

    shape.setPosition(col * tileSize, row * tileSize);
}

// funcția de desenare
void ChaseGhost::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// funcția clone (constructor virtual)
Ghost* ChaseGhost::clone() const {
    return new ChaseGhost(*this);
}
