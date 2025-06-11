#include <iostream>
#include "Map.h"

// Simple structure representing a game character
struct Character {
    int x, y, width, height;
};

// Print the map with a character
void printMap(const Map& map, const Character& player) {
    for (int y = 0; y < map.getHeight(); y++) {
        for (int x = 0; x < map.getWidth(); x++) {
            // Check if player is at this position
            bool isPlayer = (x >= player.x && x < player.x + player.width &&
                            y >= player.y && y < player.y + player.height);
            
            if (isPlayer) {
                std::cout << "P";
            } else {
                // Print tile based on its type
                switch (map.getTile(x, y).getType()) {
                    case Tile::Type::WALL:
                        std::cout << "#";
                        break;
                    case Tile::Type::WATER:
                        std::cout << "~";
                        break;
                    case Tile::Type::GRASS:
                        std::cout << ",";
                        break;
                    default:
                        std::cout << ".";
                        break;
                }
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // Create a 15x10 map
    Map gameMap(15, 10);
    
    // Set up some walls and different tile types
    for (int x = 0; x < gameMap.getWidth(); x++) {
        gameMap.setTile(x, 0, Tile::Type::WALL);
        gameMap.setTile(x, gameMap.getHeight() - 1, Tile::Type::WALL);
    }
    
    for (int y = 0; y < gameMap.getHeight(); y++) {
        gameMap.setTile(0, y, Tile::Type::WALL);
        gameMap.setTile(gameMap.getWidth() - 1, y, Tile::Type::WALL);
    }
    
    // Add some water
    gameMap.setTile(5, 5, Tile::Type::WATER);
    gameMap.setTile(6, 5, Tile::Type::WATER);
    gameMap.setTile(5, 6, Tile::Type::WATER);
    gameMap.setTile(6, 6, Tile::Type::WATER);
    
    // Add some grass
    for (int x = 8; x < 12; x++) {
        for (int y = 3; y < 7; y++) {
            gameMap.setTile(x, y, Tile::Type::GRASS);
        }
    }
    
    // Create a player character
    Character player = {2, 2, 1, 1};
    
    // Game loop
    char input;
    bool running = true;
    
    while (running) {
        // Clear screen (system-dependent, this is for Windows)
        system("cls");
        
        // Print map and player
        printMap(gameMap, player);
        
        // Display controls
        std::cout << "\nControls: WASD to move, Q to quit\n";
        std::cout << "Player position: (" << player.x << ", " << player.y << ")\n";
        
        // Get input
        std::cin >> input;
        
        // Store old position in case we need to revert due to collision
        int oldX = player.x;
        int oldY = player.y;
        
        // Handle input
        switch (input) {
            case 'w':
            case 'W':
                player.y--;
                break;
            case 'a':
            case 'A':
                player.x--;
                break;
            case 's':
            case 'S':
                player.y++;
                break;
            case 'd':
            case 'D':
                player.x++;
                break;
            case 'q':
            case 'Q':
                running = false;
                break;
        }
        
        // Check for collisions and revert movement if needed
        if (gameMap.checkCollision(player.x, player.y, player.width, player.height)) {
            player.x = oldX;
            player.y = oldY;
            std::cout << "Collision detected!" << std::endl;
        }
        
        // Optional: Save map to file
        // gameMap.saveToFile("map.txt");
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
