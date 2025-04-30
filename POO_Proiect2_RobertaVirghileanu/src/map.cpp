#include "Map.h"
#include "MapLoadException.h"
#include <fstream>
#include <iostream>
#include <cstring>

// constructor care încarcă harta din fișier
Map::Map(const char* filename, float tileSize) : tileSize(tileSize), width(0), height(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw MapLoadException("Nu pot deschide fișierul: " + std::string(filename));
    }

    char line[MAX_COLS + 1];

    bool foundSomething = false;

    while (file.getline(line, MAX_COLS)) {
        int len = std::strlen(line);
        if (len > width) width = len;

        for (int col = 0; col < len; ++col) {
            char c = line[col];
            if (c == 'P') {
                playerStart = sf::Vector2i(col, height);
                mapData[height][col] = '.';  // înlocuiesc 'P' cu un punct
            } else {
                mapData[height][col] = c;
            }
        }

        height++;
        if (height >= MAX_ROWS) break;
        foundSomething = true;
    }
    // exceptie cu throw
    if (!foundSomething || height == 0) {
        throw MapLoadException("Fișierul este gol sau nu conține o hartă validă.");
    }

    // inițializez formele pentru perete și puncte
    wallShape.setSize(sf::Vector2f(tileSize, tileSize));
    wallShape.setFillColor(sf::Color::Blue);

    dotShape.setRadius(tileSize / 6);
    dotShape.setFillColor(sf::Color::White);
    dotShape.setOrigin(dotShape.getRadius(), dotShape.getRadius());
}

// desenez harta pe fereastra dată
void Map::draw(sf::RenderWindow& window) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            sf::Vector2f position(col * tileSize, row * tileSize);

            if (mapData[row][col] == '#') {
                wallShape.setPosition(position);
                window.draw(wallShape);
            } else if (mapData[row][col] == '.') {
                // ajustez poziția doturilor (mâncării)
                position.x += tileSize / 2;  // mut dotul pe axa X pentru a-l centra
                position.y += tileSize / 2;  // mut dotul pe axa Y pentru a-l centra
                dotShape.setPosition(position);
                window.draw(dotShape);
            }
        }
    }
}
// verific dacă o celulă (un pătrățel) este un perete
bool Map::isWall(int row, int col) const {
    return (mapData[row][col] == '#');
}

// verific dacă o celulă (un pătrățel) conține un punct
bool Map::isDot(int row, int col) const {
    return (mapData[row][col] == '.');
}

// funcție pentru ca pac-man să mănânce un punct dintr-o celulă
void Map::eatDot(int row, int col) {
    if (isDot(row, col)) {
        mapData[row][col] = ' ';  // Înlăturăm punctul
    }
}

// getter pentru coordonatele de start ale jucătorului
sf::Vector2i Map::getPlayerStart() const {
    return playerStart;
}

// getter pentru lățimea hărții
int Map::getWidth() const {
    return width;
}

// getter pentru înălțimea hărții
int Map::getHeight() const {
    return height;
}

// getter pentru dimensiunea fiecărui tile
float Map::getTileSize() const {
    return tileSize;
}
