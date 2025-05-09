#pragma once

#include "Ghost.h"

class PatrolGhost : public Ghost {
public:
    PatrolGhost(int startX, int startY, float tileSize, int range, bool vertical);

    void update(const sf::Vector2i& playerPos) override;
    Ghost* clone() const override;

private:
    int patrolRange;
    bool isVertical;
    int direction;
};
