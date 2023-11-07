#include "engine.h"
#include <iostream>
#include <string>

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
            std::cout << " " << board[i] << " |";
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
        if (isdigit(pieces[i]))
        {
            int num = pieces[i] - '0';
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
