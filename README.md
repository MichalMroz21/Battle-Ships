# Ships

State commands - start with [state], they are provided until another [state].

PRINT x - Print state of the game. Basic version for x = 0 <br/>
SET_FLEET P a b c d - Number of ships (4 classes) from carrier to destroyer for player P  <br/>
NEXT_PLAYER P - Sets next move for player P  <br/>
BOARD_SIZE y x - Sets the board size  <br/>
INIT_POSITION P y1 x1 y2 x2 - Player P can place ships in rectangle defined by left upper point - (y1, x1) and right lower point (y2, x2)  <br/>
REEF y x - Sets reef at (y, x)  <br/>
EXTENDED_SHIPS - turn the extended logic of ships  <br/>
SAVE - saves state of the game  <br/>

Player commands - start with [playerX], where X is A or B, until another [playerX]  <br/>

PLACE_SHIP y x D i C - Place the i-th ship of class C at (y,x) with direction D.  <br/>
SHOOT y, x - Shoots at (y,x), can only start if all the ships were placed.  <br/>
PRINT x - Print the state as seen by the player. x = 1 advanced printing.  <br/>
SPY i y x - Send a spy plane from i-th carrier at (y,x)  <br/>
MOVE i C F - Move i-th ship of class C Forward

ex.

[state]\
SET_FLEET A 0 1 0 0\
SET_FLEET B 0 0 1 1\
[state]\
[playerA]\
PLACE_SHIP 6 0 N 0 BAT\
[playerA]\
[playerB]\
PLACE_SHIP 16 0 N 0 CRU\
PLACE_SHIP 16 2 N 0 DES\
[playerB]\
[state]\
PRINT 0\
[state]\
[playerA]\
SHOOT 17 0\
[playerA]\
[playerB]\
SHOOT 7 0\
[playerB]\
[state]\
PRINT 0\
SAVE\
[state]
