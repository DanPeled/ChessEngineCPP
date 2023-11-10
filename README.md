# ChessEngineCPP

> A chess game desgined in the C++ programming language
# Init
The code starts by initializing the board, using stringified plotting, going each character and plotting the right piece on the board for it, the basic board string is `rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR`, which places a Rook (`r`), a Knight (`n`), a Bishop (`b`), a Queen (`q`), a King (`k`), the player's pawns, goes down 4 rows (`dddd`), and puts the others for the other player.

# Game Loop
## Getting user Input
The game loop starts by getting the user input in the form of <from> <to> e.g 1a 2a which translates to moving the piece on 1a and moving it to 2a.
## Moving the pieces
The code gets the user input, checks wheter the from spot is empty and if the positions are inside of the board (Checking if the movement is valid), if it isn't then it gets back to getting the user input, if it is valid, it does the following steps (`makeMove()`): 
- Check if the positions are valid : </br>
```
  Check if the move is inside of a generated moves int vector (`std::vector<int> possibleMoves`).
  Check if the player is moving a piece of the right player's color according to the turn value.
```
- Check if a piece was eaten due to the movement, and there was, prints a text matching to what happend (E.G Black Rook Ate White Queen).
- Increase The turn values and switch to the other's player turn.
- Print the board again.
