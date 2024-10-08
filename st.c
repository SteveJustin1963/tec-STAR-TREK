#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

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
void displayCommandList();
void displayMap();

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
    
    // Place Klingons
    for (int i = 0; i < MAX_KLINGONS; i++) {
        do {
            game.klingons[i].row = rand() % MAP_SIZE;
            game.klingons[i].col = rand() % MAP_SIZE;
        } while (game.map[game.klingons[i].row][game.klingons[i].col] != EMPTY);
        game.map[game.klingons[i].row][game.klingons[i].col] = KLINGON;
        game.klingons[i].health = 100;
    }

    // Place Starbases
    for (int i = 0; i < MAX_STARBASES; i++) {
        do {
            game.starbases[i].row = rand() % MAP_SIZE;
            game.starbases[i].col = rand() % MAP_SIZE;
        } while (game.map[game.starbases[i].row][game.starbases[i].col] != EMPTY);
        game.map[game.starbases[i].row][game.starbases[i].col] = STARBASE;
    }

    // Place Stars
    for (int i = 0; i < MAX_STARS; i++) {
        do {
            game.stars[i].row = rand() % MAP_SIZE;
            game.stars[i].col = rand() % MAP_SIZE;
        } while (game.map[game.stars[i].row][game.stars[i].col] != EMPTY);
        game.map[game.stars[i].row][game.stars[i].col] = STAR;
    }

    // Place Planets
    for (int i = 0; i < MAX_PLANETS; i++) {
        do {
            game.planets[i].row = rand() % MAP_SIZE;
            game.planets[i].col = rand() % MAP_SIZE;
        } while (game.map[game.planets[i].row][game.planets[i].col] != EMPTY);
        game.map[game.planets[i].row][game.planets[i].col] = PLANET;
    }
    
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
            printf("Moved to sector (%d, %d). Energy cost: %d\n", row, col, energy_cost);
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
            } else {
                printf("  ");
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
            int closest_distance = MAP_SIZE * 2;
            int closest_index = -1;
            for (int i = 0; i < MAX_KLINGONS; i++) {
                if (game.klingons[i].health > 0) {
                    int distance = abs(game.klingons[i].row - game.enterprise.row) +
                                   abs(game.klingons[i].col - game.enterprise.col);
                    if (distance < closest_distance) {
                        closest_distance = distance;
                        closest_index = i;
                    }
                }
            }
            
            if (closest_index != -1) {
                int damage = energy_to_use / (closest_distance + 1);
                game.klingons[closest_index].health -= damage;
                printf("Hit Klingon for %d damage!\n", damage);
                if (game.klingons[closest_index].health <= 0) {
                    printf("Klingon destroyed!\n");
                    game.map[game.klingons[closest_index].row][game.klingons[closest_index].col] = EMPTY;
                    game.klingons[closest_index].health = 0;
                }
            } else {
                printf("No Klingons in range.\n");
            }
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
        
        // Find closest Klingon
        int closest_distance = MAP_SIZE * 2;
        int closest_index = -1;
        for (int i = 0; i < MAX_KLINGONS; i++) {
            if (game.klingons[i].health > 0) {
                int distance = abs(game.klingons[i].row - game.enterprise.row) +
                               abs(game.klingons[i].col - game.enterprise.col);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_index = i;
                }
            }
        }
        
        if (closest_index != -1) {
            int hit_chance = 100 - (closest_distance * 10);
            if (rand() % 100 < hit_chance) {
                int damage = 50 + (rand() % 51);  // 50-100 damage
                game.klingons[closest_index].health -= damage;
                printf("Torpedo hit! Dealt %d damage to Klingon.\n", damage);
                if (game.klingons[closest_index].health <= 0) {
                    printf("Klingon destroyed!\n");
                    game.map[game.klingons[closest_index].row][game.klingons[closest_index].col] = EMPTY;
                    game.klingons[closest_index].health = 0;
                }
            } else {
                printf("Torpedo missed!\n");
            }
        } else {
            printf("No Klingons in range.\n");
        }
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
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = game.enterprise.row + i;
            int c = game.enterprise.col + j;
            if (r >= 0 && r < MAP_SIZE && c >= 0 && c < MAP_SIZE) {
                if (game.map[r][c] == STARBASE) {
                    starbase_nearby = true;
                    break;
                }
            }
        }
        if (starbase_nearby) break;
    }
    
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
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = game.enterprise.row + i;
            int c = game.enterprise.col + j;
            if (r >= 0 && r < MAP_SIZE && c >= 0 && c < MAP_SIZE) {
                if (game.map[r][c] == PLANET) {
                    planet_nearby = true;
                    break;
                }
            }
        }
        if (planet_nearby) break;
    }
    
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
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = game.enterprise.row + i;
            int c = game.enterprise.col + j;
            if (r >= 0 && r < MAP_SIZE && c >= 0 && c < MAP_SIZE) {
                if (game.map[r][c] == PLANET) {
                    planet_nearby = true;
                    break;
                }
            }
        }
        if (planet_nearby) break;
    }
    
    if (planet_nearby) {
        printf("Orbiting planet. Scanning surface...\n");
        // Perform surface scan
        printf("Scan complete. Planet has:\n");
        printf("- Atmosphere: %s\n", (rand() % 2 == 0) ? "Breathable" : "Toxic");
        printf("- Water: %s\n", (rand() % 2 == 0) ? "Present" : "Absent");
        printf("- Life signs: %s\n", (rand() % 2 == 0) ? "Detected" : "None detected");
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
    for (int i = 0; i < MAX_KLINGONS; i++) {
        if (game.klingons[i].health > 0) {
            for (int j = 0; j < MAX_STARBASES; j++) {
                int distance = abs(game.klingons[i].row - game.starbases[j].row) +
                               abs(game.klingons[i].col - game.starbases[j].col);
                if (distance <= 1) {
                    // Move Klingon away from Starbase
                    int dr = game.klingons[i].row - game.starbases[j].row;
                    int dc = game.klingons[i].col - game.starbases[j].col;
                    int new_row = game.klingons[i].row + (dr != 0 ? dr / abs(dr) : 0);
                    int new_col = game.klingons[i].col + (dc != 0 ? dc / abs(dc) : 0);
                    
                    if (new_row >= 0 && new_row < MAP_SIZE && new_col >= 0 && new_col < MAP_SIZE &&
                        game.map[new_row][new_col] == EMPTY) {
                        game.map[game.klingons[i].row][game.klingons[i].col] = EMPTY;
                        game.klingons[i].row = new_row;
                        game.klingons[i].col = new_col;
                        game.map[new_row][new_col] = KLINGON;
                    }
                }
            }
        }
    }
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
    
    // Update Klingon positions (simple movement)
    for (int i = 0; i < MAX_KLINGONS; i++) {
        if (game.klingons[i].health > 0) {
            int dr = rand() % 3 - 1;  // -1, 0, or 1
            int dc = rand() % 3 - 1;  // -1, 0, or 1
            int new_row = game.klingons[i].row + dr;
            int new_col = game.klingons[i].col + dc;
            
            if (new_row >= 0 && new_row < MAP_SIZE && new_col >= 0 && new_col < MAP_SIZE &&
                game.map[new_row][new_col] == EMPTY) {
                game.map[game.klingons[i].row][game.klingons[i].col] = EMPTY;
                game.klingons[i].row = new_row;
                game.klingons[i].col = new_col;
                game.map[new_row][new_col] = KLINGON;
            }
        }
    }
}

// Display the command list
void displayCommandList() {
    printf("\nCommand List:\n");
    printf("NAV <row> <col> - Navigate to a new position\n");
    printf("SRS - Short Range Scan\n");
    printf("LRS - Long Range Scan\n");
    printf("PHA - Fire Phasers\n");
    printf("TOR - Fire Photon Torpedoes\n");
    printf("SHE <raise/lower> - Manage Shields\n");
    printf("DOCK - Dock with a nearby Starbase\n");
    printf("LAND - Land on a nearby Planet\n");
    printf("ORBIT - Orbit a nearby Planet\n");
    printf("QUIT - Exit the game\n");
}

// Display the current map
void displayMap() {
    printf("\nCurrent Map:\n");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            switch(game.map[i][j]) {
                case EMPTY: printf(". "); break;
                case ENTERPRISE: printf("E "); break;
                case KLINGON: printf("K "); break;
                case STARBASE: printf("$ "); break;
                case STAR: printf("* "); break;
                case PLANET: printf("x "); break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Handle user input
void handleInput() {
    char command[10];
    int row, col;
    
    displayMap();
    displayCommandList();
    
    printf("\nEnergy: %d | Shields: %d | Torpedoes: %d\n", game.energy, game.shields, game.torpedoes);
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
    } else if (strcmp(command, "QUIT") == 0) {
        printf("Thanks for playing! Goodbye.\n");
        exit(0);
    } else {
        printf("Invalid command.\n");
    }
}

// Starbase Safe Zone
void StarbaseSafeZone() {
    for (int i = 0; i < MAX_KLINGONS; i++) {
        if (game.klingons[i].health > 0) {
            for (int j = 0; j < MAX_STARBASES; j++) {
                int distance = abs(game.klingons[i].row - game.starbases[j].row) +
                               abs(game.klingons[i].col - game.starbases[j].col);
                if (distance <= 1) {
                    // Move Klingon away from Starbase (same as in KlingonAvoidance)
                    int dr = game.klingons[i].row - game.starbases[j].row;
                    int dc = game.klingons[i].col - game.starbases[j].col;
                    int new_row = game.klingons[i].row + (dr != 0 ? dr / abs(dr) : 0);
                    int new_col = game.klingons[i].col + (dc != 0 ? dc / abs(dc) : 0);
                    
                    if (new_row >= 0 && new_row < MAP_SIZE && new_col >= 0 && new_col < MAP_SIZE &&
                        game.map[new_row][new_col] == EMPTY) {
                        game.map[game.klingons[i].row][game.klingons[i].col] = EMPTY;
                        game.klingons[i].row = new_row;
                        game.klingons[i].col = new_col;
                        game.map[new_row][new_col] = KLINGON;
                    }
                }
            }
        }
    }
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
        updateMap();
        
        // Check win/lose conditions
        int klingons_left = 0;
        for (int i = 0; i < MAX_KLINGONS; i++) {
            if (game.klingons[i].health > 0) {
                klingons_left++;
            }
        }
        
        if (klingons_left == 0) {
            printf("Congratulations! You've defeated all Klingons and won the game!\n");
            break;
        }
        
        if (game.energy <= 0) {
            printf("Game Over. Your ship has run out of energy.\n");
            break;
        }
    }
    
    return 0;
}
