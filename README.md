# Star Trek game - Make it so!

not so yet! still a work in progress


![image](https://github.com/user-attachments/assets/4a36ce61-d774-4ce3-bb17-0ea3bcf334d0)

- clone and enhance the Mike Mayfield Star Trek 1971 for the TEC-1
- use all outputs, lcd, 7 seg, 8x8 and terminal, simple sound effects

### list of all symbols:
These symbols appear in the map to represent different objects and entities.

1. **O**: Your ship (USS Enterprise)
2. **K**: Klingon ship
3. **\***: Star
4. **$**: Starbase
5. **x**: Planet
6. **000**: Empty sector (in long-range scans, shows no Klingons, Starbases, or Stars)
7. 


 

### Game Mechanics:
This covers all the implemented game logic so far

1. **NAV**: Move between sectors using row, column format (input row, then column). Movement costs energy.
2. **SRS**: Short-range scan reveals stars, planets, enemies (Klingons), and starbases within the current sector.
3. **LRS**: Long-range scan displays a 3x3 grid of surrounding sectors, showing Klingons (K), Starbases ($), and Stars (*). Planets (x) are not detectable in LRS.
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

 



###  *pseudocode**  
```
// Game Initialization:

Initialize galaxy map with sectors (NxN grid)
Place Klingon ships (K), Starbases ($), Stars (*), and Planets (x) randomly on the map
Set player's initial position (O)
Set initial energy, shields, and photon torpedoes
 

// Movement Logic (NAV):

function NAV(row, col):
    if (valid sector):
        move player to new sector (row, col)
        reduce energy based on distance moved
        update map
    else:
        display "Invalid move"
// Short-Range Scan (SRS):

function SRS():
    scan current sector
    display stars (*), planets (x), Klingon ships (K), and Starbases ($) within the current sector

// Long-Range Scan (LRS):

function LRS():
    scan surrounding sectors (3x3 grid)
    display Klingons (K), Starbases ($), and Stars (*)
    planets (x) do not appear on LRS

// Phaser Attack (PHA):

function PHA():
    if locked-on to Klingon ship (K):
        fire phasers, reduce energy
        calculate damage to Klingon ship
        if Klingon health <= 0:
            destroy Klingon ship
        else:
            display "No lock-on, can't fire"
// Photon Torpedo Attack (TOR):

function TOR():
    if locked-on to Klingon ship (K) and photon torpedoes > 0:
        fire torpedo
        reduce photon torpedo count
        calculate damage to Klingon ship
        if Klingon health <= 0:
            destroy Klingon ship
    else:
        display "No lock-on or no torpedoes left"


// Shields (SHE):

function SHE(action):
    if action == "raise":
        raise shields, reduce energy
    elif action == "lower":
        lower shields, energy is saved
// Docking (DOCK):

function DOCK():
    if at Starbase ($):
        refuel and repair ship (restore energy and shields)
    else:
        display "No Starbase in this sector"

// Planet Landing Logic (LAND):

function LAND():
    if planet (x) is nearby:
        analyze planet for habitability
        if planet is habitable:
            allow landing
        else:
            display "Planet is hostile"

// Orbit Planets (ORBIT):

function ORBIT():
    if planet (x) is nearby:
        orbit planet
        perform surface scan for life, features, civilizations
    else:
        display "No planet nearby to orbit"

// Klingon Detection and Stealth:

function KlingonDetection():
    if player has landed on planet (x):
        Klingon ships (K) cannot detect the player
    else:
        normal Klingon behavior (pursue or attack player)

// Klingon Avoidance Near Starbases:

function KlingonAvoidance():
    if Klingon ship (K) is near a Starbase ($):
        Klingon will not approach closer than one sector to the Starbase
    else:
        Klingon ship may move toward player

// Aiming and Lock-On:

function AIM():
    if targeting system locks-on (random chance based on Klingon movement):
        allow player to fire
    else:
        display "Lock-on failed"

// Klingon Firing on Player:

function KlingonFire():
    if player is in range:
        if player shields are up:
            reduce damage to player
            update player shields and energy
        else:
            player takes full damage
            update player energy

// Energy Management:

function manageEnergy():
    deduct energy for movement, phaser fire, torpedoes, and shields
    if energy is too low, restrict actions like firing and movement

// Map Updates:

function updateMap():
    update player's position on map based on row, column
    display changes in nearby sectors after each action (NAV, SRS, etc.)

// Row, Column Input Format:

function handleInput(row, col):
    process all navigation and actions based on row, column format (input row first, then column)

// Starbase Safe Zones:

function StarbaseSafeZone():
    if player is near a Starbase ($):
        prevent Klingons (K) from entering the sector or approaching closer than one sector

// Summary of Game Logic:
- Player must **aim** and **lock-on** before firing phasers or torpedoes.
- **Klingons** can fire back, and player shields must be managed carefully.
- **Klingons avoid** Starbases, and the player can use **Starbases** for safe zones and repairs.
- **Planets** can be orbited or landed on if nearby.
- **Energy** is consumed for movement, shields, and firing weapons.

```
