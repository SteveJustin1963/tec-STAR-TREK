# Star Trek game - Make it so!

not so yet! still a work in progress


![image](https://github.com/user-attachments/assets/4a36ce61-d774-4ce3-bb17-0ea3bcf334d0)

- clone and enhance the Mike Mayfield Star Trek 1971 for the TEC-1
- use all outputs, lcd, 7 seg, 8x8 and terminal, simple sound effects


### game logic :
1. **NAV**: Move between sectors using row, column format; movement costs energy.
2. **SRS**: Short-range scan reveals stars, planets, enemies (Klingons), and starbases.
3. **LRS**: Long-range scan shows nearby sectors, detecting Klingons (K), Starbases ($), and Stars (*); planets (x) are not detected.
4. **PHA**: Fire phasers at Klingons in the same sector; consumes energy.
5. **TOR**: Fire photon torpedoes at Klingons in the same sector; limited supply.
6. **SHE**: Adjust shields, raising or lowering for energy defense allocation.
7. **DOCK**: Docking at Starbases refuels and repairs the ship fully.
8. **Planets (x)**: Planets orbit stars and can be nearby for landing.
9. **Landing**: You can land on planets if nearby; the computer checks if the planet is habitable or hostile.
10. **Orbit Planets**: Orbiting planets allows surface scans for features, life, and civilizations.
11. **Klingon Detection**: Klingons cannot detect you if you're landed unless they are in orbit of the same planet.
12. **Klingon Avoidance**: Klingon ships (K) will not approach closer than one sector to a Starbase ($).
13. **Energy Management**: Energy is consumed for movement, phasers, and shields.
14. **Map Updates**: Player’s position is accurately reflected based on row, column coordinates.

### list of all symbols:
These symbols appear in the map to represent different objects and entities.

1. **O**: Your ship (USS Enterprise)
2. **K**: Klingon ship
3. **\***: Star
4. **$**: Starbase
5. **x**: Planet
6. **000**: Empty sector (in long-range scans, shows no Klingons, Starbases, or Stars)

### sudo code

Here’s the **pseudocode** for all the game logic implemented so far:

### Game Initialization:
```
Initialize map with 8x8 sectors
Place Klingon ships (K), Starbases ($), Stars (*), and Planets (x) randomly on the map
Set player's initial position (O)
Set initial energy, shields, and photon torpedoes
```

### Movement Logic (NAV):
```
function NAV(row, col):
    if (valid sector):
        move player to new sector (row, col)
        reduce energy based on distance moved
        update map
    else:
        display "Invalid move"
```

### Short-Range Scan (SRS):
```
function SRS():
    scan current sector
    display nearby stars (*), planets (x), Klingons (K), and starbases ($)
```

### Long-Range Scan (LRS):
```
function LRS():
    scan surrounding sectors (3x3 grid)
    display number of Klingons (K), stars (*), starbases ($), and empty sectors
    planets (x) are not shown in LRS
```

### Phaser Attack (PHA):
```
function PHA():
    if Klingon ship (K) is in the same sector:
        fire phasers, reduce energy
        calculate damage to Klingon ship
        if Klingon health <= 0:
            destroy Klingon ship
    else:
        display "No enemy in range"
```

### Photon Torpedo Attack (TOR):
```
function TOR():
    if Klingon ship (K) is in the same sector and photon torpedoes > 0:
        fire photon torpedo
        reduce photon torpedo count
        calculate damage to Klingon ship
        if Klingon health <= 0:
            destroy Klingon ship
    else:
        display "No enemy in range or no torpedoes left"
```

### Shields (SHE):
```
function SHE(action):
    if action == "raise":
        increase shield level, decrease available energy
    elif action == "lower":
        decrease shield level, increase available energy
```

### Docking (DOCK):
```
function DOCK():
    if at Starbase ($):
        fully restore energy and shields
        repair any damage
    else:
        display "No Starbase in this sector"
```

### Planet Landing Logic (LAND):
```
function LAND():
    if planet (x) is nearby:
        run computer analysis for habitability (oxygen, temperature)
        if planet is habitable:
            allow landing
        else:
            display "Planet is hostile"
    else:
        display "No planet nearby to land on"
```

### Orbiting Planets (ORBIT):
```
function ORBIT():
    if planet (x) is nearby:
        move into orbit
        perform surface scan for features, life, civilizations
    else:
        display "No planet nearby to orbit"
```

### Klingon Detection and Stealth:
```
function KlingonDetection():
    if player has landed on planet (x):
        Klingon ships (K) cannot detect the player
    else:
        normal Klingon behavior (pursue the player)
```

### Klingon Avoidance Near Starbases:
```
function KlingonAvoidance():
    if Klingon ship (K) is one sector away from a Starbase ($):
        Klingon ship does not move closer to the Starbase
    else:
        Klingon ship moves toward the player
```

### Energy Management:
```
function manageEnergy():
    deduct energy for each movement, phaser fire, and shield management
    display current energy levels
```

### Map Updates:
```
function updateMap():
    update player's position (row, col)
    display any changes in nearby sectors after each action
```

 
 
