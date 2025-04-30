#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "ChaseGhost.h"
#include "utile.h"
#include "MapLoadException.h"

int main() {
    try {
        float tileSize = 32.0f;
        Map gameMap("map.txt", tileSize);

        sf::Vector2i startPos = gameMap.getPlayerStart();
        Player pacman(startPos.x, startPos.y, tileSize);

        Ghost* ghosts[1000];
        int ghostCount = 0;

        ghosts[ghostCount++] = new RandomGhost(5, 5, tileSize);
        ghosts[ghostCount++] = new ChaseGhost(7, 7, tileSize);

        int windowWidth = gameMap.getWidth() * tileSize;
        int windowHeight = gameMap.getHeight() * tileSize;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pac-Man");

        window.setFramerateLimit(60);

        sf::Clock ghostClock;
        float ghostMoveInterval = 0.6f;

        bool isGameOver = false;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (!isGameOver) {
                pacman.handleInput(gameMap);
                pacman.update(gameMap);

                if (gameMap.isDot(pacman.getRow(), pacman.getCol())) {
                    gameMap.eatDot(pacman.getRow(), pacman.getCol());
                }

                if (ghostClock.getElapsedTime().asSeconds() > ghostMoveInterval) {
                    updateGhosts(ghosts, ghostCount, pacman.getPosition());
                    ghostClock.restart();
                }

                for (int i = 0; i < ghostCount; i++) {
                    sf::Vector2i ghostPos = ghosts[i]->getPosition();
                    if (ghostPos == pacman.getPosition()) {
                        if (auto* chase = dynamic_cast<ChaseGhost*>(ghosts[i])) {
                            isGameOver = true;
                            break;
                        }
                        if (auto* random = dynamic_cast<RandomGhost*>(ghosts[i])) {
                            ghostMoveInterval = 1.2f;
                        }
                    }
                }

                window.clear(sf::Color::Black);
                gameMap.draw(window);
                pacman.draw(window);
                drawGhosts(ghosts, ghostCount, window);
                window.display();
            } else {
                window.clear(sf::Color::Red);
                window.display();
                sf::sleep(sf::seconds(3));
                window.close();
            }
        }

        for (int i = 0; i < ghostCount; i++) {
            delete ghosts[i];
        }

        return 0;

    } catch (const MapLoadException& ex) {
        std::cerr << "Eroare la încărcarea hărții: " << ex.what() << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << "Eroare neașteptată: " << ex.what() << std::endl;
        return 2;
    }
}
