; c code for faster testing before we make mint code
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define MAP_SIZE 8
#define MAX_KLINGONS 3
#define MAX_STARBASES 3
#define MAX_STARS 5
#define MAX_PLANETS 3

// Game entities
typedef enum { EMPTY, ENTERPRISE, KLINGON, STARBASE, STAR, PLANET } EntityType;

typedef struct {
    int row;
    int col;
    int health;
} Entity;

// Game state
typedef struct {
    EntityType map[MAP_SIZE][MAP_SIZE];
    Entity enterprise;
    Entity klingons[MAX_KLINGONS];
    Entity starbases[MAX_STARBASES];
    Entity stars[MAX_STARS];
    Entity planets[MAX_PLANETS];
    int energy;
    int shields;
    int torpedoes;
    bool is_docked;
    bool is_landed;
} GameState;

GameState game;

// Function prototypes
void initializeGame();
void NAV(int row, int col);
void SRS();
void LRS();
void PHA();
void TOR();
void SHE(const char* action);
void DOCK();
void LAND();
void ORBIT();
bool KlingonDetection();
void KlingonAvoidance();
bool AIM();
void KlingonFire();
void manageEnergy(int amount);
void updateMap();
void handleInput();
void StarbaseSafeZone();

// Initialize the game
void initializeGame() {
    srand(time(NULL));
    
    // Clear the map
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            game.map[i][j] = EMPTY;
        }
    }
    
    // Place Enterprise
    game.enterprise.row = rand() % MAP_SIZE;
    game.enterprise.col = rand() % MAP_SIZE;
    game.map[game.enterprise.row][game.enterprise.col] = ENTERPRISE;
    
    // Place Klingons, Starbases, Stars, and Planets
    // (Implementation omitted for brevity, but would involve random placement)
    
    game.energy = 3000;
    game.shields = 100;
    game.torpedoes = 10;
    game.is_docked = false;
    game.is_landed = false;
}

// Move the Enterprise
void NAV(int row, int col) {
    if (row >= 0 && row < MAP_SIZE && col >= 0 && col < MAP_SIZE) {
        int distance = abs(row - game.enterprise.row) + abs(col - game.enterprise.col);
        int energy_cost = distance * 10;
        
        if (game.energy >= energy_cost) {
            game.map[game.enterprise.row][game.enterprise.col] = EMPTY;
            game.enterprise.row = row;
            game.enterprise.col = col;
            game.map[row][col] = ENTERPRISE;
            manageEnergy(-energy_cost);
            updateMap();
        } else {
            printf("Not enough energy for this move.\n");
        }
    } else {
        printf("Invalid move\n");
    }
}

// Short Range Scan
void SRS() {
    printf("Short Range Scan:\n");
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = game.enterprise.row + i;
            int c = game.enterprise.col + j;
            if (r >= 0 && r < MAP_SIZE && c >= 0 && c < MAP_SIZE) {
                switch(game.map[r][c]) {
                    case EMPTY: printf(". "); break;
                    case ENTERPRISE: printf("E "); break;
                    case KLINGON: printf("K "); break;
                    case STARBASE: printf("$ "); break;
                    case STAR: printf("* "); break;
                    case PLANET: printf("x "); break;
                }
            }
        }
        printf("\n");
    }
}

// Long Range Scan
void LRS() {
    printf("Long Range Scan:\n");
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int klingons = 0, starbases = 0, stars = 0;
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    int mapR = game.enterprise.row + (i * 3) + r - 1;
                    int mapC = game.enterprise.col + (j * 3) + c - 1;
                    if (mapR >= 0 && mapR < MAP_SIZE && mapC >= 0 && mapC < MAP_SIZE) {
                        switch(game.map[mapR][mapC]) {
                            case KLINGON: klingons++; break;
                            case STARBASE: starbases++; break;
                            case STAR: stars++; break;
                        }
                    }
                }
            }
            printf("[%d%d%d] ", klingons, starbases, stars);
        }
        printf("\n");
    }
}

// Phaser Attack
void PHA() {
    if (AIM()) {
        int energy_to_use;
        printf("Enter amount of energy to use: ");
        scanf("%d", &energy_to_use);
        
        if (energy_to_use > 0 && energy_to_use <= game.energy) {
            manageEnergy(-energy_to_use);
            
            // Find closest Klingon and apply damage
            // (Implementation omitted for brevity)
            
            printf("Phasers fired with %d energy.\n", energy_to_use);
        } else {
            printf("Invalid energy amount.\n");
        }
    } else {
        printf("No lock-on, can't fire.\n");
    }
}

// Torpedo Attack
void TOR() {
    if (AIM() && game.torpedoes > 0) {
        game.torpedoes--;
        
        // Calculate hit probability and damage
        // (Implementation omitted for brevity)
        
        printf("Torpedo fired.\n");
    } else {
        printf("No lock-on or no torpedoes left.\n");
    }
}

// Shield Management
void SHE(const char* action) {
    if (strcmp(action, "raise") == 0) {
        int amount;
        printf("Enter shield energy: ");
        scanf("%d", &amount);
        if (amount > 0 && amount <= game.energy) {
            game.shields += amount;
            manageEnergy(-amount);
            printf("Shields raised to %d.\n", game.shields);
        } else {
            printf("Invalid shield energy amount.\n");
        }
    } else if (strcmp(action, "lower") == 0) {
        int amount = game.shields;
        game.shields = 0;
        manageEnergy(amount);
        printf("Shields lowered. Energy restored.\n");
    }
}

// Docking
void DOCK() {
    bool starbase_nearby = false;
    // Check if a starbase is in an adjacent sector
    // (Implementation omitted for brevity)
    
    if (starbase_nearby) {
        game.is_docked = true;
        game.energy = 3000;
        game.shields = 100;
        game.torpedoes = 10;
        printf("Docked at starbase. Ship repaired and restocked.\n");
    } else {
        printf("No starbase in adjacent sectors.\n");
    }
}

// Planet Landing
void LAND() {
    bool planet_nearby = false;
    // Check if a planet is in the same sector
    // (Implementation omitted for brevity)
    
    if (planet_nearby) {
        // Analyze planet for habitability
        bool is_habitable = (rand() % 2 == 0);  // 50% chance of being habitable
        
        if (is_habitable) {
            game.is_landed = true;
            printf("Landed on habitable planet.\n");
        } else {
            printf("Planet is hostile. Cannot land.\n");
        }
    } else {
        printf("No planet in this sector.\n");
    }
}

// Planet Orbiting
void ORBIT() {
    bool planet_nearby = false;
    // Check if a planet is in the same sector
    // (Implementation omitted for brevity)
    
    if (planet_nearby) {
        printf("Orbiting planet. Scanning surface...\n");
        // Perform surface scan (implementation omitted)
    } else {
        printf("No planet nearby to orbit.\n");
    }
}

// Klingon Detection
bool KlingonDetection() {
    if (game.is_landed) {
        return false;  // Klingons can't detect the player when landed
    }
    return true;  // Otherwise, normal Klingon behavior
}

// Klingon Avoidance near Starbases
void KlingonAvoidance() {
    // For each Klingon, check proximity to Starbases and adjust movement
    // (Implementation omitted for brevity)
}

// Aiming and Lock-On
bool AIM() {
    // Simulate aiming with a random chance of success
    return (rand() % 100 < 80);  // 80% chance of successful lock-on
}

// Klingon Firing on Player
void KlingonFire() {
    for (int i = 0; i < MAX_KLINGONS; i++) {
        if (game.klingons[i].health > 0) {
            int distance = abs(game.klingons[i].row - game.enterprise.row) + 
                           abs(game.klingons[i].col - game.enterprise.col);
            
            if (distance <= 2) {  // Klingons can fire if within 2 sectors
                int damage = rand() % 100 + 50;  // Random damage between 50-149
                
                if (game.shields > 0) {
                    int absorbed = (damage * game.shields) / 100;
                    game.shields -= absorbed;
                    damage -= absorbed;
                }
                
                manageEnergy(-damage);
                printf("Klingon attack! Damage: %d\n", damage);
            }
        }
    }
}

// Energy Management
void manageEnergy(int amount) {
    game.energy += amount;
    if (game.energy < 0) {
        game.energy = 0;
        printf("Warning: Energy depleted!\n");
    }
}

// Update Map
void updateMap() {
    // Clear enterprise's old position
    game.map[game.enterprise.row][game.enterprise.col] = EMPTY;
    
    // Update enterprise's new position
    game.map[game.enterprise.row][game.enterprise.col] = ENTERPRISE;
    
    // Update Klingon positions (movement logic omitted for brevity)
}

// Handle Input
void handleInput() {
    char command[10];
    int row, col;
    
    printf("Enter command: ");
    scanf("%s", command);
    
    if (strcmp(command, "NAV") == 0) {
        printf("Enter row and column: ");
        scanf("%d %d", &row, &col);
        NAV(row, col);
    } else if (strcmp(command, "SRS") == 0) {
        SRS();
    } else if (strcmp(command, "LRS") == 0) {
        LRS();
    } else if (strcmp(command, "PHA") == 0) {
        PHA();
    } else if (strcmp(command, "TOR") == 0) {
        TOR();
    } else if (strcmp(command, "SHE") == 0) {
        char action[10];
        printf("Enter shield action (raise/lower): ");
        scanf("%s", action);
        SHE(action);
    } else if (strcmp(command, "DOCK") == 0) {
        DOCK();
    } else if (strcmp(command, "LAND") == 0) {
        LAND();
    } else if (strcmp(command, "ORBIT") == 0) {
        ORBIT();
    } else {
        printf("Invalid command.\n");
    }
}

// Starbase Safe Zone
void StarbaseSafeZone() {
    // Prevent Klingons from entering sectors adjacent to Starbases
    // (Implementation omitted for brevity)
}

int main() {
    initializeGame();
    
    while (1) {
        handleInput();
        if (!game.is_docked && !game.is_landed) {
            KlingonAvoidance();
            if (KlingonDetection()) {
                KlingonFire();
            }
        }
        StarbaseSafeZone();
        
        // Check win/lose conditions (implementation omitted)
    }
    
    return 0;
}
