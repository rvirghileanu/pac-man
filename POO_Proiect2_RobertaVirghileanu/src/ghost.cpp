#include "Ghost.h"

// inițializare atribut static pentru contorul de fantome
int Ghost::ghostCount = 0;

// constructor
Ghost::Ghost(float startX, float startY, float tileSize, sf::Color color)
    : tileSize(tileSize), row(startY), col(startX) {
    shape.setRadius(tileSize / 2);
    shape.setFillColor(color);
    shape.setPosition(col * tileSize, row * tileSize);

    // cresc contorul pentru fiecare instanță de fantomă creată
    ghostCount++;
}

// destructor
Ghost::~Ghost() {
    // scad contorul atunci când o instanță de fantomă este distrusă
    ghostCount--;
}

// funcție de desenare a fantomei
void Ghost::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// getter pentru poziția fantomei
sf::Vector2i Ghost::getPosition() const {
    return sf::Vector2i(col, row);
}
