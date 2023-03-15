<h3>This project is a simple Battleship game with some interesting rules.</h3>

To play the game specific commands have to be written in console.

The board has a default size of 10,21 (x, y), that can be changed using a command: BOARD_SIZE y x, with choosen y and x integer values.

Ships are represented as ASCII characters in console, for example a ship of size 5 can look like this: +++++. '+' means a not broken part of the ship, where 'x' denotes a broken part of ship. Player wins when all enemy's parts are destroyed. 

Each player has exactly: 1 ship of size 5, 2 ships of size 4, 3 ships of size 3, 4 ships of size 2, with names respectively: CARRIER, BATTLESHIP, CRUISER, DESTROYER. Default number of ships can be changed using: SET_FLEET P a1 a2 a3 a4, where P is a player (A or B) and a1, a2, a3, a4 correspond to number of ships, as written above in sequence.

Players can place ships on the map. Player A can put ships in y = <0; 9> and player B in y = <11, 20>.
To place a ship use: PLACE_SHIP y x D i C - Place a ship at (y, x), D - direction (N, S, E, W), i - denotes which ship will be placed, C - Class (CAR, BAT, CRU, DES).

Players can shoot at enemy's ships using command: SHOOT y x. It can be done once per move. 
To print the state of the game simply use PRINT 0.

Commands related to the state of the game such as: SET_FLEET, PRINT have to be between [state]. Commands related to the move of a player have to be between [playerA] or [playerB]. 

Described above is just the **BASIC** logic of the game. 
<h3>Here is an example on how it looks like in action:</h3>


![Przechwytywanie](https://user-images.githubusercontent.com/125133223/225187785-bfb39af5-d437-4e24-b512-ff9b0d40dce3.PNG) &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 
![Przechwytywanie](https://user-images.githubusercontent.com/125133223/225188502-a580fdb6-5a39-4f70-8f9d-7d365a0c0cd7.PNG)

<h3>Advanced logic of the game</h3>

To turn the extended logic write: EXTENDED_SHIPS.

Printing can be extended by using PRINT 1.

Saving - using SAVE, all the state commands can be obtained for re-creating current game.

Rectangle in which a player can place ships can be bounded using: INIT_POSITION P y1 x1 y2 x2 inside of [state].
Map can contain reefs, represented as: '#'. No ship can be placed, present on a reef. For stating a reef use: REEF y x inside of [state].
Players can move ships forward by one field, using: MOVE i C F - where i denotes which ship will be moved and C means class (CAR, BAT, CRU, DES) inside of [playerX].
Players can shoot using command: SHOOT i C y x, which shoots from i-th ship of class C (CAR, BAT, CRU, DES) at position (y, x) inside of [playerX].

Ships can be placed, stated inside of [state] as a following command: SHIP P y x D i C a1...a1 . Where P means a player (A, B), y and x are coordinates, D is direction (N, S, E, W), i and C mean: i-th ship of class C (CAR, BAT, CRU, DES). and a1 ... a1 mean parts of the ship, where 0 means part is destroyed and 1 means it is not.
For example: SHIP A 9 4 W 0 BAT 1011.


PRINT 0 command can be now used inside of [playerX] and it prints the current state of the game as seen by the player X. '?' means an unknown field. Each ship has a radar and can send spies as described below.

Each ship contains additional sections:
  - Cannon - as a field after head, denoted as '!', cannon as every other part can be destroyed, if it's destroyed the ship cannot shoot. Additionaly, the range of the cannon is determined by the size of the ship, but for Carriers it is infinite.
  - Engine - as a field on the back, denoted as '%', if the engine is destroyed then ship can't move.
  - Radar - as a field on the head, denoted as '@', uncovers the unknown '?' fields when printed from a player perspective. Range of radar is equal to the length of the ship and when radar is destroyed then range becomes 1.

Carriers can send spy planes, which reveal enemy ships in 3x3 square, sending spies counts as shooting. This can be done using: SPY i y x, where i denotes from which Carrier spies will be sent and (y, x) is the position.

<h3>Simple example of extended logic:</h3> <br/> <br/>

![Przechwytywanie](https://user-images.githubusercontent.com/125133223/225200808-f1ac091f-3611-4cfa-9a87-c2512d6b5738.PNG)
