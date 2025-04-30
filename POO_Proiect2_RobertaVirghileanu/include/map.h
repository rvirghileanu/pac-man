#pragma once
#include <SFML/Graphics.hpp>
#include "MapLoadException.h"  // pentru excepția personalizată MapLoadException

#define MAX_ROWS 100
#define MAX_COLS 100

class Map {
public:
    // constructor care poate arunca excepții dacă fișierul nu este valid
    Map(const char* filename, float tileSize);

    // desenarea hărții
    void draw(sf::RenderWindow& window);

    // verificări și acțiuni asupra hărții
    bool isWall(int row, int col) const;
    bool isDot(int row, int col) const;
    void eatDot(int row, int col);

    // getteri pentru obținerea informațiilor despre hartă
    sf::Vector2i getPlayerStart() const;
    int getWidth() const;
    int getHeight() const;
    float getTileSize() const;

private:
    char mapData[MAX_ROWS][MAX_COLS];
    int width;
    int height;
    float tileSize;

    sf::RectangleShape wallShape;
    sf::CircleShape dotShape;
    sf::Vector2i playerStart;
};
