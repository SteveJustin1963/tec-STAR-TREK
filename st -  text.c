// https://www.programiz.com/c-programming/online-compiler/
// text game

#include <stdio.h>

// Global variables
int x = 0, y = 0;          // Sector coordinates
int a = 0, b = 0;          // Subsector coordinates
int c = 31;                // Stardates remaining
int d = 10;                // Klingons remaining
int e = 2;                 // Starbases remaining
int ammo = 300;            // Photon torpedoes (ammo)
int shield_energy = 0;     // Shield energy
int free_energy = 3000;    // Free energy
char sector[8][8];         // Sector grid (8x8)
int lock_acquired = 0;     // Track if lock is acquired
int squelch_level = 0;     // Squelch level to remove background noise
int energy_levels[8][8];   // Energy levels for scanning
int last_scan_time = 0;    // Last time a full scan was performed

// Pseudo-random generator variables
unsigned long seed = 123456789;  // Initial seed value

// Function declarations
void delay(int milliseconds);
void display_status();
void map_display();
void scan_display();
void navigation();
void ammo_status();
int aim();
void fire();
void shield_control();
void initialize_sector();
void mission_menu();
unsigned long simple_random();
void list_klingons();

// Simple random number generator based on a linear congruential generator
unsigned long simple_random() {
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;  // LCG formula
    return seed;
}

int main() {
    printf("Star Trek Game\n");
    printf("You are the captain of the USS Enterprise.\n");
    printf("Your mission is to destroy 10 Klingon warships before stardate 1763.\n");
    printf("Use navigation to move between sectors.\n");
    printf("Good luck, Captain!\n");

    initialize_sector();  // Initialize the sector grid
    delay(1000);  // Adding dramatic effect

    mission_menu();  // Display the mission menu

    return 0;
}

// Delay function for dramatic effect
void delay(int milliseconds) {
    // Simulate delay using a simple loop
    for (long i = 0; i < milliseconds * 1000; i++) {}
}

// Display current status
void display_status() {
    printf("STARDATES REMAINING: %d\n", c);
    printf("SECTOR (X,Y): %d, %d\n", x, y);
    printf("SUBSECTOR (X,Y): %d, %d\n", a, b);
    printf("PHOTON TORPEDOES: %d\n", ammo);
    printf("SHIELD ENERGY: %d\n", shield_energy);
    printf("FREE ENERGY: %d\n", free_energy);
    printf("KLINGONS REMAINING: %d\n", d);
    printf("STARBASES REMAINING: %d\n", e);
}

// Display the sector map
void map_display() {
    printf("MAP: Sector Overview\n");
    printf("+-----------------------------------+\n");
    for (int i = 0; i < 8; i++) {
        printf("| ");
        for (int j = 0; j < 8; j++) {
            if (x == i && y == j && sector[i][j] == 'K') {
                printf("%%  ");  // Show '%' when both are in the same sector
            } else if (x == i && y == j) {
                printf("O  ");  // Show 'O' for the USS Enterprise
            } else {
                printf("%c  ", sector[i][j]);  // Show the sector content
            }
        }
        printf("|\n");
    }
    printf("+-----------------------------------+\n");
}

// Display the long-range scan with squelch feature
void scan_display() {
    int squelch_level;
    int squelch_percent;
    int current_time = c; // Assuming 'c' is the current stardate or time unit
    
    // Regenerate energy levels if it's been more than 2 time units since last scan
    if (current_time - last_scan_time > 2) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // Base energy level
                energy_levels[i][j] = 20 + (simple_random() % 30); // Base level between 20 and 49
                
                // Adjust energy levels based on map objects
                switch(sector[i][j]) {
                    case 'K': // Klingon ship
                        energy_levels[i][j] += 50 + (simple_random() % 20); // High energy
                        break;
                    case '$': // Starbase
                        energy_levels[i][j] += 40 + (simple_random() % 15); // Moderate-high energy
                        break;
                    case 'x': // Planet
                        energy_levels[i][j] += 30 + (simple_random() % 10); // Moderate energy
                        break;
                    case '*': // Star
                        energy_levels[i][j] += 35 + (simple_random() % 15); // Moderate-high energy
                        break;
                    case 'O': // Player's ship
                        energy_levels[i][j] += 45 + (simple_random() % 15); // High energy, but less than Klingon
                        break;
                }
                
                // Ensure energy level doesn't exceed 99
                if (energy_levels[i][j] > 99) energy_levels[i][j] = 99;
            }
        }
        last_scan_time = current_time;
    }
    
    // Ask for squelch level
    printf("Enter squelch level (0-9): ");
    scanf("%d", &squelch_level);
    
    // Ensure squelch level is between 0 and 9
    if (squelch_level < 0) squelch_level = 0;
    if (squelch_level > 9) squelch_level = 9;

    // Calculate squelch percentage
    squelch_percent = squelch_level * 10;

    printf("SCAN: Long-Range Energy Levels (Squelch: %d%%)\n", squelch_percent);
    printf("+-----------------------------------+\n");
    for (int i = 0; i < 8; i++) {
        printf("| ");
        for (int j = 0; j < 8; j++) {
            int energy_level = energy_levels[i][j];
            
            // Apply small random fluctuation
            energy_level += (simple_random() % 7) - 3; // -3 to +3 fluctuation
            if (energy_level < 0) energy_level = 0;
            if (energy_level > 99) energy_level = 99;
            
            // Apply squelch: Remove data below the squelch percentage
            if (energy_level < squelch_percent) {
                printf("   ");  // Empty space for squelched data
            } else {
                printf("%02d ", energy_level);  // Display energy level with two spaces
            }
        }
        printf("|\n");
    }
    printf("+-----------------------------------+\n");
}

// Handle navigation to a new sector
void navigation() {
    int new_x, new_y;
    char current_object;

    // Get the new sector coordinates
    printf("Enter new sector X coordinate (0-7): ");
    scanf("%d", &new_x);
    printf("Enter new sector Y coordinate (0-7): ");
    scanf("%d", &new_y);

    // Boundary checking
    if (new_x < 0) new_x = 0;
    if (new_x > 7) new_x = 7;
    if (new_y < 0) new_y = 0;
    if (new_y > 7) new_y = 7;

    // Store the object at the new location
    current_object = sector[new_x][new_y];

    // Clear the current position of the USS Enterprise
    sector[x][y] = '.';  // Clear the old position

    // Update the USS Enterprise position in the new sector
    x = new_x;
    y = new_y;

    if (current_object == 'K') {
        printf("Caution: Klingon ship detected in this sector!\n");
        // Don't overwrite the Klingon, just update player coordinates
    } else {
        sector[x][y] = 'O';  // Place the Enterprise in the new sector
    }

    // Decrease stardates
    c--;
    printf("Moved to sector (%d, %d).\n", x, y);
    
    // Display the updated map
    map_display();
}

// Display ammo status and attempt to lock on target
void ammo_status() {
    printf("Photon torpedoes in stock: %d\n", ammo);
    if (aim()) {
        printf("Lock acquired!\n");
    } else {
        printf("No lock acquired.\n");
    }
}

// Attempt to lock on target
int aim() {
    lock_acquired = simple_random() % 2;  // Simulate random lock (1 for lock, 0 for no lock)
    if (lock_acquired) {
        printf("Lock acquired!\n");
        
        // Check if a Klingon ship is in the same sector
        if (sector[x][y] == 'K') {
            printf("Target in your sector: Klingon ship detected at (%d, %d)\n", x, y);
        } else {
            printf("No Klingon ship in your sector (%d, %d). You may miss if you fire.\n", x, y);
        }
    } else {
        printf("No lock acquired.\n");
    }
    return lock_acquired;
}

// Fire photon torpedo if lock is acquired
void fire() {
    if (lock_acquired) {
        printf("Firing photon torpedo...\n");
        ammo--;
        printf("Photon torpedoes remaining: %d\n", ammo);

        // Check if a Klingon ship is in the same sector
        if (sector[x][y] == 'K') {
            printf("Klingon ship destroyed!\n");
            sector[x][y] = '.';  // Remove the Klingon ship from the sector
            d--;  // Decrease Klingon count
            printf("Klingons remaining: %d\n", d);
        } else {
            printf("The shot missed! No Klingon ship in this sector.\n");
        }

        lock_acquired = 0;  // Reset lock state after firing
    } else {
        printf("Cannot fire. No lock on target.\n");
    }
}

// Toggle shields and manage energy consumption
void shield_control() {
    char response;
    if (shield_energy == 0) {
        printf("Shields are currently DOWN.\n");
        printf("Do you want to raise shields? (y/n): ");
        scanf(" %c", &response);
        if (response == 'y') {
            shield_energy = 1;  // Raise shields
            printf("Shields UP. Increased energy consumption.\n");
        }
    } else {
        printf("Shields are currently UP.\n");
        printf("Do you want to lower shields to conserve energy? (y/n): ");
        scanf(" %c", &response);
        if (response == 'y') {
            shield_energy = 0;  // Lower shields
            printf("Shields DOWN. Energy slowly recharging...\n");
        }
    }
}

// Initialize the sector grid with objects
void initialize_sector() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sector[i][j] = '.';  // Empty sector by default
        }
    }
    sector[2][3] = 'K';  // Place Klingon ship
    sector[3][5] = '$';  // Place starbase
    sector[1][4] = 'x';  // Place planet
    sector[4][1] = '*';  // Place star
    sector[0][0] = 'O';  // Place player's ship (USS Enterprise)
}

// List all the Klingon ship locations (X, Y)
void list_klingons() {
    int found = 0;  // Flag to check if any Klingons are found
    printf("Klingon ships at the following locations:\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (sector[i][j] == 'K') {
                printf("Klingon ship at sector (%d, %d)\n", i, j);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("No Klingon ships found.\n");
    }
}

// Display the mission menu
void mission_menu() {
    char option;
    while (c > 0 && d > 0) {
        printf("\nENTER ONE OF THE FOLLOWING:\n");
        printf("1) navigation\n");
        printf("2) ammo\n");
        printf("3) aim\n");
        printf("4) fire\n");
        printf("5) shield control\n");
        printf("6) map\n");
        printf("7) scan\n");
        printf("K) List Klingon ships\n");
        scanf(" %c", &option);

        switch (option) {
            case '1': navigation(); break;
            case '2': ammo_status(); break;
            case '3': aim(); break;
            case '4': fire(); break;
            case '5': shield_control(); break;
            case '6': map_display(); break;
            case '7': scan_display(); break;
            case 'K': case 'k': list_klingons(); break;
            default: printf("Invalid option.\n"); break;
        }

        if (c == 0) {
            printf("Mission failed! Stardates depleted.\n");
        }
        if (d == 0) {
            printf("Victory! All Klingons destroyed.\n");
        }
    }
}
