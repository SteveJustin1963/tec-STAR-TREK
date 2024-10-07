#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global game state variables
int x = 0, y = 0;      // Current sector coordinates
int sx = 0, sy = 0;    // Current subsector coordinates
int sd = 31;           // Stardates remaining
int k = 10;            // Klingons remaining
int b = 2;             // Starbases remaining
int t = 10;            // Photon torpedoes
int se = 0;            // Shield energy
int e = 3000;          // Free energy

// Function prototypes (declarations)
void print_string(const char *str);
void print_newline();
void print_number(int num);
char get_input();
int random_number();
void short_range_scan();
void long_range_scan();
void sensors();
void beep();
void navigate();
void display_stats();
void display_map();
void game_loop();
void start_game();
void not_implemented();

// Function to simulate a beep sound
void beep() {
    printf("Beep!\n");
}

// Function to print a string (null-terminated)
void print_string(const char *str) {
    while (*str) {
        putchar(*str);
        str++;
    }
}

// Function to print a newline
void print_newline() {
    putchar('\n');
}

// Function to print a number
void print_number(int num) {
    printf("%d", num);
}

// Function to get user input (single character)
char get_input() {
    char input;
    input = getchar();
    getchar();  // Consume the newline character
    beep();     // Simulate beep on keypress
    return input;
}

// Function to generate a random number between 1 and 10
int random_number() {
    return (rand() % 10) + 1;
}

// Function to perform a short-range scan (SRS)
void short_range_scan() {
    print_string("Short Range Scan (SRS):"); print_newline();
    print_string("Current Sector (X,Y): "); print_number(x); print_string(", "); print_number(y); print_newline();
    print_string("+-------------------+"); print_newline();
    for (int i = 0; i < 10; i++) {
        if (i == sx && i == sy) {
            print_string("|   Ship detected   |"); print_newline();  // Simulate detecting an object (e.g., Klingon)
        } else {
            print_string("|                   |"); print_newline();
        }
    }
    print_string("+-------------------+"); print_newline();
}

// Function to perform a long-range scan (LRS)
void long_range_scan() {
    print_string("Long Range Scan (LRS):"); print_newline();
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            print_string("| Quadrant "); print_number(i); print_string(", "); print_number(j);
            print_string(" | Klingons: "); print_number(random_number());
            print_string(" | Starbases: "); print_number(random_number() % 2);  // Randomize for now
            print_newline();
        }
    }
}

// Function to handle SENSORS option
void sensors() {
    print_string("Select scan type:"); print_newline();
    print_string("1) Short Range Scan (SRS)"); print_newline();
    print_string("2) Long Range Scan (LRS)"); print_newline();
    
    int choice = get_input() - '0';  // Wait for input
    
    if (choice == 1) {
        short_range_scan();
    } else if (choice == 2) {
        long_range_scan();
    } else {
        print_string("Invalid selection."); print_newline();
    }
    
    // Pause for input to allow the user to see the scan result before returning to the main menu
    getchar();  // Wait for Enter to avoid immediate return to the main menu
}

// Function to handle non-implemented features
void not_implemented() {
    print_string("Not implemented");
    print_newline();
    getchar();  // Pause for input so user can see the message
}

// Function for navigation
void navigate() {
    print_string("Enter new sector X coordinate (0-9): ");
    x = get_input() - '0';  // Convert input to integer
    print_string("Enter new sector Y coordinate (0-9): ");
    y = get_input() - '0';  // Convert input to integer
    sx = random_number();  // Randomly set subsector
    sy = random_number();
    sd--;  // Decrease stardate
    display_map();
    display_stats();
}

// Function to display game stats
void display_stats() {
    print_string("STARDATES REMAINING "); print_number(sd); print_newline();
    print_string("SECTOR (X,Y)       "); print_number(x); print_string(", "); print_number(y); print_newline();
    print_string("SUBSECTOR (X,Y)    "); print_number(sx); print_string(", "); print_number(sy); print_newline();
    print_string("PHOTON TORPEDOES   "); print_number(t); print_newline();
    print_string("SHIELD ENERGY      "); print_number(se); print_newline();
    print_string("FREE ENERGY        "); print_number(e); print_newline();
    print_string("KLINGONS REMAINING "); print_number(k); print_newline();
    print_string("STARBASES REMAINING"); print_number(b); print_newline();
}

// Function to display sector map
void display_map() {
    print_string("SECTOR : "); print_number(x); print_string(", "); print_number(y); print_newline();
    print_string("+-------------------+"); print_newline();
    for (int i = 0; i < 10; i++) {
        print_string("|                   |"); print_newline();
    }
    print_string("+-------------------+"); print_newline();
}

// Main game loop
void game_loop() {
    while (1) {
        print_string("ENTER ONE OF THE FOLLOWING:"); print_newline();
        print_string("1) NAVIGATION"); print_newline();
        print_string("2) WEAPONS"); print_newline();
        print_string("3) SHIELD CONTROL"); print_newline();
        print_string("4) SENSORS"); print_newline();
        print_string("5) SHIP'S COMPUTER"); print_newline();
        
        int choice = get_input() - '0';
        
        if (choice == 1) {
            navigate();  // Navigation
        } else if (choice == 2) {
            not_implemented();  // Weapons not implemented
        } else if (choice == 3) {
            not_implemented();  // Shield control not implemented
        } else if (choice == 4) {
            sensors();  // Call sensors function
        } else if (choice == 5) {
            not_implemented();  // Ship's computer not implemented
        }

        // Check for game end conditions
        if (sd == 0) {
            print_string("Mission failed!"); print_newline();
            break;
        }
        if (k == 0) {
            print_string("Victory! All Klingons destroyed!"); print_newline();
            break;
        }
    }
}

// Instructions and game start
void start_game() {
    print_string("Star Trek Game"); print_newline();
    print_string("You are the captain of the USS Enterprise."); print_newline();
    print_string("Your mission is to destroy 10 Klingon warships"); print_newline();
    print_string("before stardate 1763."); print_newline();
    print_string("Use navigation to move between sectors."); print_newline();
    print_string("Good luck, Captain!"); print_newline();
    
    // Simulate delay for 10000 cycles (this can be skipped in real C)
    for (int i = 0; i < 10000000; i++) {}

    game_loop();  // Start the game loop
}

int main() {
    srand(time(0));  // Seed the random number generator
    start_game();    // Start the game
    return 0;        // Exit the program
}
