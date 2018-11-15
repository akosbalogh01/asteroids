# Asteroids

University assignment - asteroid field game on a EFM32 Giant Gecko microcontroller.
Project source files are available in the [sources](https://github.com/akosbalogh01/asteroids/tree/master/asteroids/src) directory. Created by Ákos Balogh, Dániel Balogh.

## Game logic

Upon controller restart, the game initialises the used hardware components (LCD, UART0, TIMER0), creates required data structures (program logic, global interrupt variables). The game logic is controlled by a state machine. LCD control is using Simplicity Studio's built-in SegmentLCD functions to display alphanumerical characters, and uses the university provided individual segment control function to display asteroids, and the spaceship. Display, and spaceship control is updated at every game logic cycle, based on global variables, only modifiable by interrupt functions. To prevent modifying these descriptor variables during a game cycle, each cycle creates an atomic copy of these parameters. Moving the spaceship happens at TIMER0 interrupts, modifying descriptor parameters happen at UART0 interrupts.

##### Controlling the game

Connect to the microcontroller with a PuTTY terminal (COM port, 115200 baud rate, serial port). Starting up the program sends a test character to the terminal, then at every timer interrupt, sends a character to indicate the connection is still alive. Starting the game requires pressing the 'S' key, quitting is available with the 'R' key, turning the spaceship is done with the 'J' (turn right), 'B' (turn left) buttons. Available turns are based on the spaceship's orientation, and current location. Passing to the next level decreases time between TIMER0 interrupts, thus decreasing time between moves.

###### LCD segments and digits

On the microcontroller's integrated LCD display, 7 alphanumerical digits are available to display text, or the generated asteroid field and the spaceship. 4 additional digits are also used, to indicate the current level. Segment indexing is done via 2-digit decimal numbers, ie. 13. First digit selects the digit (0 - leftmost, 6-rightmost), second digit selects one from the available segments (horizontal, and two vertical segments). Consequently, moving the spaceship is essentially adding 10 to the coordinate, if a horizontal move is detected, or modifying the last digit is the move was vertical.

###### Legacy code

Even though in the current version, the built-in text and number displaying functions are used, the initial release used the university provided LCD control functions, which controls individual segments. As such, he character and number displaying bitmaps were coded, but are now not used. These bitmaps, and functions are marked as deprecated in the code.

