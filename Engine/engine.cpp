#include "engine.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
void printBoard(std::string board[], int size)
{
    std::cout << "  | A | B | C | D | E | F | G | H |" << std::endl;
    std::cout << "  |___|___|___|___|___|___|___|___|" << std::endl;

    for (int i = 0; i < size; i++)
    {
        if (i % 8 == 0)
        {
            std::cout << " " << (i / 8) + 1 << "|";
        }

        if (board[i] == "")
        {
            std::cout << "   |"; // Print a blank space for an empty cell
        }
        else
        {
            std::cout << " " << (isupper(board[i][0]) ? "\033[31;1m" : "\033[1m") << board[i] << "\033[0m"
                      << " |";
        }

        if (i % 8 == 7)
        {
            std::cout << " " << (i / 8) + 1 << std::endl;
            std::cout << "  |___|___|___|___|___|___|___|___|" << std::endl;
        }
    }
}

void initBoard(std::string board[], std::string pieces)
{
    int boardIndex = 0; // Use a separate index for the board array

    for (int i = 0; i < pieces.length(); i++)
    {
        if (isdigit(pieces[i]) || pieces[i] == 'd')
        {
            int num = isdigit(pieces[i]) ? pieces[i] - '0' : (pieces[i] == 'd' ? 8 : 0);
            // Fill multiple board positions with empty strings
            for (int j = 0; j < num; j++)
            {
                if (boardIndex < BOARD_SIZE)
                {
                    board[boardIndex] = "";
                    boardIndex++;
                }
            }
        }
        else
        {
            if (boardIndex < BOARD_SIZE)
            {
                board[boardIndex] = pieces[i];
                boardIndex++;
            }
        }
    }

    // Fill any remaining positions with empty strings
    for (; boardIndex < BOARD_SIZE; boardIndex++)
    {
        board[boardIndex] = "";
    }
}
std::string getPieceName(std::string piece)
{
    if (piece.empty())
    {
        return "Invalid";
    }

    std::string prefix = (isupper(piece[0])) ? "Black " : "White ";
    std::string name = "Invalid";

    switch (toupper(piece[0]))
    {
    case 'R':
        name = "Rook";
        break;
    case 'P':
        name = "Pawn";
        break;
    case 'B':
        name = "Bishop";
        break;
    case 'N':
        name = "Knight";
        break;
    case 'K':
        name = "King";
        break;
    case 'Q':
        name = "Queen";
        break;
    }

    return prefix + name;
}
bool isSpotEmpty(std::string board[], int pos)
{
    return board[pos][0] == '\0';
}
bool validateMove(std::string board[], int from, int to)
{
    bool valid = true;
    if (isSpotEmpty(board, from))
    {
        valid = false;
    }
    return valid; // TODO: Implement logic :D (Not fun?)
}
bool eatsPiece(std::string board[], int from, int to)
{
    char movedPiece = board[from][0];
    char placedPos = board[to][0];
    return (!isSpotEmpty(board, to));
}
int getPossibleMoves[](std::string board[], int from)
{
    // TODO: make logic
    return 0;
}