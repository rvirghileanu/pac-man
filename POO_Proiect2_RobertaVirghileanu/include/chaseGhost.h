#pragma once
#include "Ghost.h"

class ChaseGhost : public Ghost {
public:
    ChaseGhost(float startX, float startY, float tileSize);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    // Constructor de copiere (necesar pentru clone)
    ChaseGhost(const ChaseGhost&) = default;

    // Funcție clone (constructor virtual)
    Ghost* clone() const override;
};
