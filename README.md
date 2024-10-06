# Star Trek game - Make it so!

![image](https://github.com/user-attachments/assets/4a36ce61-d774-4ce3-bb17-0ea3bcf334d0)

- clone and enhance the Mike Mayfield Star Trek 1971
- on the TEC-1
- ASM output to 7 seg and 8x8 matrix
- MINT outout to terminal, 7 seg and 8x8 matrix
- simple sound effects
- 

```
The stardate is 1732. You are the captain of the USS Enterprise.  You have received word from Starfleet
command of a plot by Klingon spies to destroy all the Federation starbases in the region so the
Klingon Empire can assume control. The Federation is in danger and you are the only ship in range.
Your mission is to hunt down and destroy the 10 Klingon warships in the region. You must complete
your mission before stardate 1763, giving you 31 stardates to succeed. There are 2 Federation Starbases
in the region for refueling, restocking torpedoes, and repairs. Check the ship's computer to access the
captain's manual for a tutorial on how to complete your mission. Good luck, galactic peace is in your hands!
=============================
As you begin your mission, you find yourself in a sector clear of enemy ships.  You will have to use
navigation to jump to another sector to engage with the enemy. If the sectors adjacent to your ship
are unexplored, you can use your long range sensors to try and find the enemy.
```


![image](https://github.com/user-attachments/assets/8e12df7c-0f3e-4d11-8fb1-f3079e846eb8)


### MINT

### v2

### v1

1. Display: We now use both digits of the 7-segment display.
2. Keypad Input: The program reads input from the TEC-1's keypad using port #F800.
3. Game Logic: 
   - It's a simple "Space Game" where the player needs to hit the correct key when shown on the 7-segment display.
   - The game generates a random target (displayed on the terminal in hex) and then shows a random number on the 7-segment display.
   - The player needs to press the correct key (0-F) to match the displayed number.
   - Pressing 'F' skips the current round.
   - The game keeps track of the score over 10 rounds.
4. Sound: We use beeps to indicate correct answers and button presses.
5. Menu System: The program now has a main menu where the player can choose to play or view instructions.
6. Random Number Generation: We implement a simple pseudo-random number generator using the remainder of the last operation.

//////////



