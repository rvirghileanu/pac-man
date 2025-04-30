#pragma once
#include "Ghost.h"
#include <cstdlib> // pentru rand()

class RandomGhost : public Ghost {
public:
    RandomGhost(float startX, float startY, float tileSize);

    void update(const sf::Vector2i& playerPos) override;
    void draw(sf::RenderWindow& window) override;

    // constructor de copiere (necesar pentru clone)
    RandomGhost(const RandomGhost&) = default;

    // funcție clone (constructor virtual)
    Ghost* clone() const override;
};
