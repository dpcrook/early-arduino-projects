early-arduino-projects
======================

Arduino-based sketches

These were only tested on Arduino 1.0.3+ (and Rev3 boards).
Most require additional hardware to work.

The directory structure

    .
    ├── Hunt_The_Wumpus
    ├── four_bit_maze
    └── rainbowduino
        └── PlasmaCubeImpr

Games
------

### `four_bit_maze`

A simple "guess-the-sequence" game with switches and LEDs.

Idea (and source) found on the web: [src](http://cs.gettysburg.edu/~tneller/mazes/oskar4bit/arduino.html)
 

### `Hunt_The_Wumpus`

Another simple graph traversal game.

Designed for the Adafruit RGB LCD shield - [learn.adafruit.com](http://learn.adafruit.com/arduino-hunt-the-wumpus/overview-and-parts)


Rainbowduino
------------

### `PlasmaCubeImpr` ###

Based on code from

 - <http://www.seeedstudio.com/wiki/images/4/43/Rainbowduino_for_Arduino1.0.zip>
 - <http://seeedstudio.com/wiki/Rainbowduino_v3.0>

Updates made by: 

  * 19-May-2013: Fixed color gradient code and gradient traversal code.
    - David Crook <david.crook@gmail.com>
