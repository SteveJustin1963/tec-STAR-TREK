; c code for faster testing before we make mint code
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Game Variables
int energy = 3000;
int shields = 1000;
int photonTorpedoes = 5;
bool shieldsUp = false;
int playerRow = 2;
int playerCol = 1;

// Galaxy Map (NxN Grid)
char map[3][5] = {
    {'0', '0', '0', '0', '0'},
    {'*', '$', '0', '0', '0'},
    {'*', '*', 'K', '0', '0'}
};

// Function to display the map
void displayMap() {
    printf("Galaxy Map:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == playerRow && j == playerCol) {
                printf("O ");
            } else {
                printf("%c ", map[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Movement Logic
void movePlayer(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 5) {
        printf("Moving to Sector (%d, %d)\n", row, col);
        playerRow = row;
        playerCol = col;
        energy -= 100;  // Energy cost for movement
        displayMap();
    } else {
        printf("Invalid Sector\n");
    }
}

// Short Range Scan
void shortRangeScan() {
    printf("Short-Range Scan Results for Sector (%d, %d):\n", playerRow, playerCol);
    if (map[playerRow][playerCol] == '*') {
        printf("Star detected\n");
    }
    if (map[playerRow][playerCol] == '$') {
        printf("Starbase detected\n");
    }
    if (map[playerRow][playerCol] == 'K') {
        printf("Klingon ship detected\n");
    }
    printf("\n");
}

// Long Range Scan
void longRangeScan() {
    printf("Long-Range Scan Results:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] != '0') {
                printf("Sector (%d, %d) contains %c\n", i, j, map[i][j]);
            }
        }
    }
    printf("\n");
}

// Phaser Attack
void firePhasers() {
    if (map[playerRow][playerCol] == 'K') {
        printf("Firing phasers at Klingon ship!\n");
        map[playerRow][playerCol] = '0';  // Destroy Klingon ship
        energy -= 200;  // Energy cost for firing
        printf("Klingon ship destroyed!\n");
    } else {
        printf("No Klingon ship in this sector.\n");
    }
    printf("\n");
}

// Photon Torpedo Attack
void firePhotonTorpedoes() {
    if (map[playerRow][playerCol] == 'K' && photonTorpedoes > 0) {
        printf("Firing photon torpedoes at Klingon ship!\n");
        map[playerRow][playerCol] = '0';  // Destroy Klingon ship
        photonTorpedoes--;
        printf("Klingon ship destroyed!\n");
    } else {
        printf("No Klingon ship in this sector or no torpedoes left.\n");
    }
    printf("\n");
}

// Adjust Shields
void adjustShields(bool raise) {
    if (raise && !shieldsUp) {
        shieldsUp = true;
        printf("Shields are now up.\n");
        energy -= 50;  // Energy cost to raise shields
    } else if (!raise && shieldsUp) {
        shieldsUp = false;
        printf("Shields are now down.\n");
    } else {
        printf("Shields already in desired state.\n");
    }
    printf("\n");
}

// Klingon Attack
void klingonAttack() {
    if (map[playerRow][playerCol] == 'K') {
        printf("Klingon ship is firing!\n");
        if (shieldsUp) {
            shields -= 100;
            printf("Shields absorbed the attack. Shields left: %d\n", shields);
        } else {
            energy -= 100;
            printf("Direct hit! Energy left: %d\n", energy);
        }
    } else {
        printf("No Klingon ships nearby.\n");
    }
    printf("\n");
}

// Main Game Loop
int main() {
    int choice, row, col;

    printf("Welcome to the Space Game!\n");
    displayMap();

    while (true) {
        printf("Choose an action:\n");
        printf("1. Move\n");
        printf("2. Short-Range Scan\n");
        printf("3. Long-Range Scan\n");
        printf("4. Fire Phasers\n");
        printf("5. Fire Photon Torpedoes\n");
        printf("6. Raise/Lower Shields\n");
        printf("7. Klingon Attack\n");
        printf("8. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter row and column (row, col): ");
                scanf("%d %d", &row, &col);
                movePlayer(row, col);
                break;
            case 2:
                shortRangeScan();
                break;
            case 3:
                longRangeScan();
                break;
            case 4:
                firePhasers();
                break;
            case 5:
                firePhotonTorpedoes();
                break;
            case 6:
                printf("Enter 1 to raise shields, 0 to lower shields: ");
                int raise;
                scanf("%d", &raise);
                adjustShields(raise);
                break;
            case 7:
                klingonAttack();
                break;
            case 8:
                printf("Exiting game...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }

        // Check if energy is too low to continue
        if (energy <= 0) {
            printf("You are out of energy. Game over!\n");
            break;
        }
    }

    return 0;
}
