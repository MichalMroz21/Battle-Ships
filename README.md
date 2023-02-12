# Ships

State commands - start with [state], they are provided until another [state].

PRINT x - Print state of the game. Basic version for x = 0
SET_FLEET P a b c d - Number of ships (4 classes) from carrier to destroyer for player P
NEXT_PLAYER P - Sets next move for player P
BOARD_SIZE y x - Sets the board size
INIT_POSITION P y1 x1 y2 x2 - Player P can place ships in rectangle defined by left upper point - (y1, x1) and right lower point (y2, x2) 
REEF y x - Sets reef at (y, x)
EXTENDED_SHIPS - turn the extended logic of ships
SAVE - saves state of the game

Player commands - start with [playerX], where X is A or B, until another [playerX]

PLACE_SHIP y x D i C - Place the i-th ship of class C at (y,x) with direction D.
SHOOT y, x - Shoots at (y,x), can only start if all the ships were placed.
PRINT x - Print the state as seen by the player. x = 1 advanced printing.
SPY i y x - Send a spy plane from i-th carrier at (y,x)
