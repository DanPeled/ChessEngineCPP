# ChessEngineCPP

> A chess game desgined in the C++ programming language
# Init
The code starts by initializing the board, using [FEN](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation#:~:text=Forsyth%E2%80%93Edwards%20Notation%20(FEN),Scottish%20newspaper%20journalist%20David%20Forsyth.)-like stringified plotting, going each character and plotting the right piece on the board for it, the basic board string is `rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR`, which places a Rook (`r`), a Knight (`n`), a Bishop (`b`), a Queen (`q`), a King (`k`), the player's pawns, goes down 4 rows (`dddd`), and puts the others for the other player. </br></br>
<picture>
<img src="https://raw.githubusercontent.com/DanPeled/ChessEngineCPP/main/README%20FILES/StartBoard.png" width="458.66666666666666666666666666667" height="328" style="pointer-events: none;"/>
</picture>
</br>
# Game Loop
## Getting user Input
The game loop starts by getting the user input in the form of <from> <to> e.g 1a 2a which translates to moving the piece on 1a and moving it to 2a.
### Keywords
- `exit` - Stops the game.
- `show <pos>` - Shows the possible moves of the piece on the given position, e.g 2b in the start of the game will result in this: </br>
<picture>
<img src="https://raw.githubusercontent.com/DanPeled/ChessEngineCPP/main/README%20FILES/ShowKeyword.png" width="444.66666666666666666666666666667" height="338"/>
</picture> </br> </br>

## Moving the pieces
The code gets the user input, checks wheter the from spot is empty and if the positions are inside of the board (Checking if the movement is valid), if it isn't then it gets back to getting the user input, if it is valid, it does the following steps (`makeMove()`): 
- Check if the positions are valid : </br>
&nbsp;&nbsp;&nbsp;Check if the move is inside of a generated moves int vector (`std::vector<int> possibleMoves`). </br>
&nbsp;&nbsp;&nbsp;Check if the player is moving a piece of the right player's color according to the turn value.
- Check if a piece was eaten due to the movement, and there was, prints a text matching to what happend (E.G Black Rook Ate White Queen).
- Increase The turn values and switch to the other's player turn.
- Print the board again.
