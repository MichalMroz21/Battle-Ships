<h3>This project is a simple Battleship game with some interesting rules.</h3>

To play the game specific commands have to be written in console.

The board has a default size of 10,21 (x, y), that can be changed using a command: BOARD_SIZE y x, with choosen y and x integer values.

Ships are represented as ASCII characters in console, for example a ship of size 5 can look like this: +++++. '+' means a not broken part of the ship, where 'x' denotes a broken part of ship.

Each player has exactly: 1 ship of size 5, 2 ships of size 4, 3 ships of size 3, 4 ships of size 2 by default, with names respectively: CARRIER, BATTLESHIP, CRUISER, DESTROYER. Default number of ships can be changed using: SET_FLEET P a1 a2 a3 a4, where P is a player (A or B) and a1, a2, a3, a4 correspond to number of ships, as written above in sequence.

Players can place ships on the map. Player A can put ships in y = <0; 9> and player B in y = <11, 20>.
To place a ship use: PLACE_SHIP y x D i C - Place a ship at (y, x), D - direction (N, S, E, W), i - denotes which ship will be placed, C - Class (CAR, BAT, CRU, DES).

Players can shoot at enemy's ships using command: SHOOT y x. It can be done once per move. 
To print the state of the game simply use PRINT 0.

Commands related to the state of the game such as: SET_FLEET, PRINT have to be between [state]. Commands related to the move of a player have to be between [playerA] or [playerB]. 

Described above is the <strong>BASIC</strong> logic of the game, here is an example on how it looks like in action:


![Przechwytywanie](https://user-images.githubusercontent.com/125133223/225187785-bfb39af5-d437-4e24-b512-ff9b0d40dce3.PNG)
![Przechwytywanie](https://user-images.githubusercontent.com/125133223/225188502-a580fdb6-5a39-4f70-8f9d-7d365a0c0cd7.PNG)
