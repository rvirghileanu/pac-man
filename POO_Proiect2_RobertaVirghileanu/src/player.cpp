#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Map.h"

Player::Player(int startX, int startY, float tileSize) 
    : row(startY), col(startX), tileSize(tileSize), moving(false), directionX(0), directionY(0) {

    shape.setRadius(tileSize / 2);  // dimensiunea cercului pentru personajele din joc
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(col * tileSize, row * tileSize);  // poziționez pacman-ul la început
}
void Player::handleInput(const Map& map) {
    if (!moving) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && row > 0) {
            directionX = 0;
            directionY = -1;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && row < map.getHeight() - 1) {
            directionX = 0;
            directionY = 1;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && col > 0) {
            directionX = -1;
            directionY = 0;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && col < map.getWidth() - 1) {
            directionX = 1;
            directionY = 0;
            moving = true;
        }
    }
}

void Player::update(Map& map) {
    if (moving) {
        if (moveClock.getElapsedTime().asSeconds() > 0.2f) {
            moveClock.restart();

            // verific dacă Pac-Man poate să meargă în direcția dorită fără a atinge peretele
            if (!map.isWall(row + directionY, col + directionX)) {
                row += directionY;
                col += directionX;
            }

            // actualizez poziția vizuală
            shape.setPosition(col * tileSize, row * tileSize);

            // după mișcare, Pac-Man nu mai este în mișcare
            // asta asigură că pac-man merge pătrățel cu pătrățel, nu dintr-un perete în altul
            moving = false;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

int Player::getRow() const {
    return row;
}

int Player::getCol() const {
    return col;
}

sf::Vector2i Player::getPosition() const {
    return sf::Vector2i(col, row);
}
