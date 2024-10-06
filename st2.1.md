
```mint
// Define 7-segment patterns for digits 0-9 and some letters
[#3F #06 #5B #4F #66 #6D #7D #07 #7F #6F #77 #7C #39 #5E #79 #71] d !

// Game state variables
0 x ! 0 y !  // Current sector coordinates
0 sx ! 0 sy !  // Current subsector coordinates
31 sd !  // Stardates remaining
10 k !  // Klingons remaining
2 b !  // Starbases remaining
10 t !  // Photon torpedoes
0 se !  // Shield energy
3000 e !  // Free energy
0 ki !   // Keypad input variable

// Interrupt handler for keypad
:Z
  /v 8 = (  // Check if it's RST 1 (keypad interrupt)
    #F800 /I ki !  // Read keypad input and store in ki
  )
;

// Enable interrupts and set up interrupt handler
:E
  :Z Z ;  // Define and assign interrupt handler
  #FB /X  // Enable interrupts (EI instruction)
;

// Define a function to output to 7-segment display
:S
  #F807 /O  // Select left digit
  d $ ? #F80F /O  // Output segment pattern for left digit
  #F806 /O  // Select right digit
  d $ ? #F80F /O  // Output segment pattern for right digit
;

// Define a function to wait for and get keypad input
:K
  0 ki !  // Clear previous input
  /U ( ki 0 > /W )  // Wait until ki is non-zero
  ki "  // Duplicate ki value
  0 ki !  // Clear ki for next input
  #0F &  // Mask to get only the lower 4 bits
;

// Define a function to generate a random number
:R
  /r 1 + 10 %  // Use remainder of last operation, add 1, mod 10
;

// Function to display game stats
:D
  `STARDATES REMAINING` sd . /N
  `SECTOR (X,Y)      ` x . `,` y . /N
  `SUBSECTOR (X,Y)   ` sx . `,` sy . /N
  `PHOTON TORPEDOES  ` t . /N
  `SHIELD ENERGY     ` se . /N
  `FREE ENERGY       ` e . /N
  `KLINGONS REMAINING` k . /N
  `STARBASES REMAINING` b . /N
;

// Function to display sector map
:M
  `SECTOR : ` x . `,` y . /N
  `=-1-=-2-=-3-=-4-=-5-=-6-=-7-=-8-=-9-=-10` /N
  10 (
    /i 1 + .
    `|                    |` /N
  )
  `=-1-=-2-=-3-=-4-=-5-=-6-=-7-=-8-=-9-=-10` /N
  sx sy S  // Display subsector on 7-segment
;

// Function for navigation
:N
  `Enter new sector X coordinate (0-9):` /N
  K x !
  `Enter new sector Y coordinate (0-9):` /N
  K y !
  R sx ! R sy !  // Randomly set subsector
  sd 1 - sd !  // Decrease stardate
  M D  // Display new map and stats
;

// Main game loop
:G
  /U (
    `ENTER ONE OF THE FOLLOWING:` /N
    `1) NAVIGATION` /N
    `2) WEAPONS` /N
    `3) SHIELD CONTROL` /N
    `4) SENSORS` /N
    `5) SHIP'S COMPUTER` /N
    K
    1 = ( N )  // Navigation
    2 = ( `Weapons not implemented` /N )
    3 = ( `Shield control not implemented` /N )
    4 = ( `Sensors not implemented` /N )
    5 = ( `Ship's computer not implemented` /N )
    sd 0 = ( `Mission failed!` /W )
    k 0 = ( `Victory! All Klingons destroyed!` /W )
  )
;

// Instructions and game start
:I
  `Star Trek Game` /N
  `You are the captain of the USS Enterprise.` /N
  `Your mission is to destroy 10 Klingon warships` /N
  `before stardate 1763.` /N
  `Use navigation to move between sectors.` /N
  `Good luck, Captain!` /N
  1000 (  // Delay
  )
  G  // Start game
;

// Main program
:M
  E  // Enable interrupts and set up handler
  I  // Start the game
;

// Run the main program
M

```
