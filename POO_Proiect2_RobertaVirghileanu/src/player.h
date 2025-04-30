#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Player {
public:
    Player(int startX, int startY, float tileSize);

    void handleInput(const Map& map);
    void update(Map& map);
    void draw(sf::RenderWindow& window);

    int getRow() const;
    int getCol() const;

    sf::Vector2i getPosition() const;

private:
    sf::CircleShape shape;
    int row, col;
    float tileSize;

    // direcțiile curente
    int directionX, directionY;

    // mișcare în curs (pentru a face mișcarea să fie pe grilă)
    bool moving;
    sf::Clock moveClock;
};