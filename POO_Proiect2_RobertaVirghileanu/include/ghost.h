#pragma once
#include <SFML/Graphics.hpp>

class Ghost {
public:
    // atribut static pentru a număra instanțele de fantome
    static int ghostCount;

    // constructor și destructor
    Ghost(float startX, float startY, float tileSize, sf::Color color);
    virtual ~Ghost();

    // funcții virtuale pure
    virtual void update(const sf::Vector2i& playerPos) = 0;
    virtual Ghost* clone() const = 0;

    virtual void draw(sf::RenderWindow& window);
    // pentru a accesa poziția
    sf::Vector2i getPosition() const;

protected:
    float tileSize;
    int row, col;
    sf::CircleShape shape;  // forma fantomei = cerc

    // setter poziția formei (folosită de fiecare tip de fantomă)
    void setPosition(int x, int y) {
        shape.setPosition(x * tileSize, y * tileSize);
    }

    // setter pentru culoarea formei
    void setColor(sf::Color color) {
        shape.setFillColor(color);
    }
};
