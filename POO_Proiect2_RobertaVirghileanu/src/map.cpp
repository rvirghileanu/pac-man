#include "Map.h"
#include "invalidPlayerException.h"
#include "emptyMapException.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Constructorul care încarcă harta
Map::Map(const char* filename, float tileSize) : tileSize(tileSize), width(0), height(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw MapLoadException("Nu pot deschide fișierul: " + std::string(filename));
    }

    char line[MAX_COLS + 1];
    bool foundSomething = false;
    bool foundPlayer = false;

    while (file.getline(line, MAX_COLS)) {
        int len = std::strlen(line);
        if (len > width) width = len;

        for (int col = 0; col < len; ++col) {
            char c = line[col];
            if (c == 'P') {
                if (foundPlayer) {
                    throw InvalidPlayerPositionException("Poziția jucătorului (P) apare de mai multe ori în fișierul hărții!");
                }
                playerStart = sf::Vector2i(col, height);
                mapData[height][col] = '.';  // înlocuiesc 'P' cu un punct
                foundPlayer = true;
            } else {
                mapData[height][col] = c;
            }
        }

        height++;
        if (height >= MAX_ROWS) break;
        foundSomething = true;
    }

    // Exceptie EmptyMapFileException dacă fișierul este gol
    if (!foundSomething || height == 0) {
        throw EmptyMapFileException("Fișierul este gol sau nu conține o hartă validă.");
    }

    // Dacă nu s-a găsit nicio poziție pentru jucător, aruncăm o excepție
    if (!foundPlayer) {
        throw InvalidPlayerPositionException("Poziția jucătorului (P) nu a fost găsită în fișierul hărții!");
    }

    // Inițializăm formele pentru perete și puncte
    wallShape.setSize(sf::Vector2f(tileSize, tileSize));
    wallShape.setFillColor(sf::Color::Blue);

    dotShape.setRadius(tileSize / 6);
    dotShape.setFillColor(sf::Color::White);
    dotShape.setOrigin(dotShape.getRadius(), dotShape.getRadius());
}

// Getteri
sf::Vector2i Map::getPlayerStart() const {
    return playerStart;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

float Map::getTileSize() const {
    return tileSize;
}

// Verificări și acțiuni asupra hărții
bool Map::isWall(int row, int col) const {
    return mapData[row][col] == '#';
}

bool Map::isDot(int row, int col) const {
    return mapData[row][col] == '.';
}

void Map::eatDot(int row, int col) {
    mapData[row][col] = ' ';  // Șterge punctul
}

// Desenarea hărții
void Map::draw(sf::RenderWindow& window) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (isWall(row, col)) {
                wallShape.setPosition(col * tileSize, row * tileSize);
                window.draw(wallShape);
            } else if (isDot(row, col)) {
                dotShape.setPosition(col * tileSize + tileSize / 2, row * tileSize + tileSize / 2);
                window.draw(dotShape);
            }
        }
    }
}
