Key changes in this updated version:

Interrupt Handler:

We define an interrupt handler :Z that checks if the interrupt is from the keypad (RST 1) and reads the keypad input if so.
The handler stores the keypad input in a global variable ki.


Interrupt Setup:

The :E function sets up the interrupt handler and enables interrupts using the #FB /X command (which translates to the Z80 EI instruction).


Keypad Input:

The :K function now waits for the ki variable to be non-zero (set by the interrupt handler) instead of directly reading from the port.
After reading the input, it clears ki for the next input.


Main Program:

We've added a :M function that enables interrupts and starts the game.


Game Logic:

The game logic remains mostly the same, but now it uses the interrupt-driven keypad input method.



To use this program on your TEC-1:

Load the MINT interpreter onto your TEC-1.
Enter this program into MINT.
Run the program by typing M and pressing Enter to start the game with interrupts enabled.
