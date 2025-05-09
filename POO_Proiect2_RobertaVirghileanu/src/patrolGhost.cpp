#include "PatrolGhost.h"

PatrolGhost::PatrolGhost(int startX, int startY, float tileSize, int range, bool vertical)
    : Ghost(startX, startY, tileSize, sf::Color::Magenta), patrolRange(range),
      isVertical(vertical), direction(1) {}

void PatrolGhost::update(const sf::Vector2i& playerPos) {
    if (isVertical) {
        row += direction;
        if (row < 0 || row >= patrolRange) {
            direction = -direction;
            row += direction;
        }
    } else {
        col += direction;
        if (col < 0 || col >= patrolRange) {
            direction = -direction;
            col += direction;
        }
    }

    shape.setPosition(col * tileSize, row * tileSize);

}
Ghost* PatrolGhost::clone() const {
    return new PatrolGhost(col, row, tileSize, patrolRange, isVertical);
}
