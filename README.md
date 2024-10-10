# Star Trek game - Make it so!

not so yet! still a work in progress


![image](https://github.com/user-attachments/assets/4a36ce61-d774-4ce3-bb17-0ea3bcf334d0)

- clone and enhance the Mike Mayfield Star Trek 1971 for the TEC-1
- use terminal first , later all outputs; lcd, 7 seg, 8x8 and terminal
- use simple 1bit sound effects, later sound chip
- 

### list of all symbols:
> map
```
SECTOR: 1, 1
+-------------------+
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . K . . . .
. . O * . . . . . .
. . . x . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
+-------------------+
```



- `O` Your ship (USS Enterprise)
- K Klingon ship
- `*` Star
- $ Starbase, and it orbits * on each map update
- x Planet
- `.` dots are empty sectors (in long-range scans, shows no Klingons, Starbases, or Stars)
-  


 

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

 
 
