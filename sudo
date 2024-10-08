 
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
