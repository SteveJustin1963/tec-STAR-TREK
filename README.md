

# Star Trek game - Make it so!

not so yet! still a work in progress..do not use...under construction



![image](https://github.com/user-attachments/assets/4a36ce61-d774-4ce3-bb17-0ea3bcf334d0)

- clone and enhance the Mike Mayfield Star Trek 1971 for the TEC-1
- MINT
  - use terminal, 1 bit sound
- ASM 1 uses
  - 6x 7 Seg LEDS, LCD, 8x8 and hex pad
  - 1 bit sound effects
- ASM 2 uses
  - https://github.com/SteveJustin1963/tec-POV
  - https://github.com/SteveJustin1963/tec-SPEECH
  - https://github.com/SteveJustin1963/tec-76489-Sound-Generator 

### symbols / details
 such as stars, planets, enemies (Klingons), and starbases within the current sector.
 
- `O` Your ship (USS Enterprise)
- K Klingon ship
- `*` Star
- $ Starbase, and it orbits * on each map update
- x Planet
- `.` dots are empty sectors (in long-range scans, shows no Klingons, Starbases, or Stars)

### commands
- commands entered at mint console `> `


### `map` command
- `map` shopw where are as `O`, is approx in the middle
- whe called its refeshed and dynamic based on scan data 
- scale is 10x10 light hours, about 72 AU (astronomical units)
- its the same as a SRS (short-range scan)
-  



SECTOR: 1, 1
  +-------------------+
  |     *   K   *     |
  |                   |
  |   *               |
  |                   |
  |               *   |
  |                   |
  |   O   K           |  <-- last action
  |                   |
  +-------------------+
```


 

### Game Mechanics:
This covers all the implemented game logic so far

1. **NAV**: Move between sectors using row, column format (input row, then column). Movement costs energy.
2. **Map**: is short-range scan that reveals stars, planets, enemies (Klingons), and starbases within the current sector.
3. **Scan**: is a long-range scan displays a 3x3 grid of surrounding sectors, showing Klingons (K), Starbases ($), and Stars (*). Planets (x) are not detectable in LRS.
4. **PHA**: Fire phasers at Klingon ships in the same sector. Phasers cost energy and require a lock-on.
5. **TOR**: Fire photon torpedoes at Klingons in the same sector. Torpedoes are limited in supply.
6. **SHE**: Adjust shields, raising or lowering them to manage energy for defense. Shields absorb damage if raised during attacks.
7. **DOCK**: Dock at Starbases ($) to refuel and repair the ship, restoring energy and shields fully.
8. **Energy Management**: Energy is consumed for movement, phaser attacks, and shield management. Docking restores energy and shields.

### Planet and Landing Logic:
9. **Planets (x)**: Planets orbit stars and are visible in short-range scans. They move in either clockwise or counterclockwise orbits during each update.
10. **Landing on Planets**: The player can land on nearby planets if conditions are safe. The computer calculates if the planet is habitable or hostile.
11. **Orbit Planets**: The player can choose to orbit a planet to perform surface scans for life, civilizations, or features.
12. **Klingon Detection on Planets**: Klingon ships cannot detect the player when landed on a planet unless they are in orbit of the same planet.

### Klingon Behavior and Combat:
13. **Klingon Ships (K)**: Klingon ships may attack the player, and the player must first acquire a lock-on before firing. Klingons may move defensively or stay in place during combat, based on random factors.
14. **Klingon Firing**: Klingon ships can fire on the player. If shields are raised, damage is reduced; if not, full damage is taken.
15. **Klingon Avoidance Near Starbases**: Klingon ships will not approach closer than one sector to a Starbase ($).

### Battle Logic:
16. **Aiming**: Aiming is not perfect; lock-on success depends on random factors, and Klingon ships may move defensively to avoid lock-ons.
17. **Damage Handling**: If hit, the player’s energy and shields are updated based on whether the shields were up or down during the attack.

### Miscellaneous:
18. **Row, Column Input**: All navigation and input use row, then column format.
19. **Map Updates**: The player’s position is accurately reflected in short-range and long-range scans based on row, column coordinates.
20. **Lock-On Logic**: Before firing, the player must successfully acquire a lock-on to the target Klingon ship.
21. **Starbase Safe Zones**: Starbases act as safe zones, where Klingons will not approach closer than one sector away.



This code is a basic **Star Trek-themed game** written in the **MINT programming language**, where the player takes on the role of the captain of the USS Enterprise. The main objective is to **navigate between sectors** and **destroy Klingon warships** before the stardate runs out. Here's a detailed breakdown of the key components and functionality of the code:

### Main Objective:
The player's mission is to destroy **10 Klingon warships** before the stardate reaches 0. The player navigates between sectors, and various actions can be taken from the mission menu, such as moving to different sectors or checking the ship's status. The game ends with either victory (all Klingons destroyed) or failure (if the stardate runs out).

```
```
### Code Breakdown:

#### 1. **Variables and Initialization (`:B`)**
This section initializes the game's variables, setting up the initial conditions:
- **x, y**: Sector coordinates for the ship's position.
- **a, b**: Subsector coordinates.
- **c**: Stardates remaining (initially set to 31).
- **d**: Klingon warships remaining (initially set to 10).
- **e**: Starbases remaining (set to 2).
- **f**: Photon torpedoes (initially 10).
- **g**: Shield energy.
- **h**: Free energy (3000 units to manage the ship).

Arrays (`i!`, `j!`) store sector maps (8x8 grids) used for tracking objects in each sector.

#### 2. **Delay Function (`:Delay`)**
This is a utility function that acts as a **wait or delay** mechanism. It counts down a number of cycles to simulate a time delay between actions, such as waiting between turns or game events.

#### 3. **Game Logic (`:A`)**
The `:A` function handles a specific action involving output to an I/O port (`/O`). It simulates a process where a device is activated, then deactivated after a delay (perhaps representing some hardware event in the game like firing torpedoes or activating shields).

#### 4. **Command Input (`:C`)**
This function continuously checks for input from the player (`/C` reads a character from input). It waits until valid input is provided.

#### 5. **Displaying Data (`:D`)**
The `:D` function is used to output data to the display or console.

#### 6. **Status Display (`:G`)**
This function prints the ship's current status to the console, including:
- Stardates remaining (`c`),
- Sector coordinates (`x`, `y`),
- Subsector coordinates (`a`, `b`),
- Photon torpedoes (`f`),
- Shield energy (`g`),
- Free energy (`h`),
- Klingons remaining (`d`),
- Starbases remaining (`e`).

#### 7. **Map Display (`:H`)**
This function draws a visual representation of the current sector, displaying icons for:
- **Klingons (`K`)**,
- **Stars (`*`)**,
- **Player's ship (`x`)**,
- **Starbases (`O`)**,
with `.` representing empty space. It helps the player visualize where objects are in the sector.

#### 8. **Orbit Logic (`:Orbit`)**
The `Orbit` function checks if the player is in the correct subsector to orbit a planet or starbase. It ensures that the player's coordinates are valid and updates them accordingly.

#### 9. **Navigation (`:I`)**
This function handles the player's **movement**:
- The player is prompted to enter new **X and Y coordinates** for the sector.
- The input values are bounded between 0 and 7 (valid sector range).
- It updates the ship's position (`x`, `y`), reduces the stardates (`c`), and calls the **Orbit** and **Map Display** functions to reflect the player's movement in the game.

#### 10. **Mission Menu (`:L`)**
This function displays a menu where the player can select actions:
- **1) Navigation**: Allows the player to move between sectors.
- **2) Weapons**: (Not implemented) placeholder message.
- **3) Shield Control**: (Not implemented) placeholder message.
- **4) Sensors**: (Not implemented) placeholder message.
- **5) Ship's Computer**: (Not implemented) placeholder message.

The menu also checks for mission completion conditions:
- If **stardates** reach 0, the player fails (`Mission failed!`).
- If all **Klingons** are destroyed, the player wins (`Victory! All Klingons destroyed!`).

#### 11. **Game Introduction and Start (`:M`)**
The `:M` function provides an introduction to the game, setting the scene for the player:
- The player is given their mission: to **destroy 10 Klingon warships** before the stardate runs out.
- After the introduction, the **Mission Menu** (`:L`) is displayed, allowing the player to start interacting with the game.

---

### Flow of the Game:
1. The game starts by printing a mission briefing.
2. The player is given options to navigate, use weapons, shields, sensors, or the ship's computer.
3. Each turn, the player can navigate to a different sector, view the map, or check their ship's status.
4. The player's stardates decrease as they make moves.
5. The player must destroy Klingons to win, but the exact mechanism for combat is not implemented yet.
6. The game ends with either victory or failure, based on stardates or Klingons.

---

### Key Missing Features:
1. **Weapons, Shields, and Sensors**: These are marked as "not implemented." These would involve adding functionality for the player to engage in combat, raise shields, and scan sectors for Klingons or starbases.
2. **Combat System**: The logic for firing photon torpedoes or fighting Klingons is not present. Implementing this would require additional game mechanics for combat.

---

In summary, this code sets up the basic structure of a Star Trek-like game, allowing the player to move between sectors, keep track of resources, and visualize their surroundings. It's a work in progress, and additional features like weapons and combat need to be added to fully realize the game's potential.
 
