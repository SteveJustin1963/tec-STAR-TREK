

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

```

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


  
