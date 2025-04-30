#pragma once
#include "Ghost.h"

class ChaseGhost : public Ghost {
public:
    ChaseGhost(float startX, float startY, float tileSize);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    // constructor de copiere (necesar pentru clone)
    ChaseGhost(const ChaseGhost&) = default;

    // funcție clone (constructor virtual)
    Ghost* clone() const override;
};
