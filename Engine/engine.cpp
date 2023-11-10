#include "engine.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
const std::string Pieces::BISHOP = "Bishop";
const std::string Pieces::ROOK = "Rook";
const std::string Pieces::PAWN = "Pawn";
const std::string Pieces::QUEEN = "Queen";
const std::string Pieces::KING = "King";
const std::string Pieces::KNIGHT = "Knight";
std::vector<int> generateRookMovements(std::string board[], int from);
std::vector<int> generateBishopMovements(std::string board[], int from);
void printBoard(std::string board[], int size, bool whitesTurn)
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
            std::cout << "  |___|___|___|___|___|___|___|___|";
            if (i == 31)
            {
                std::cout << (whitesTurn ? "        White's Turn" : "       Black's Turn");
            }
            std::cout << std::endl;
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
std::string getPieceType(std::string piece)
{
    std::string name = "Invalid";
    switch (toupper(piece[0]))
    {
    case 'R':
        name = Pieces::ROOK;
        break;
    case 'P':
        name = Pieces::PAWN;
        break;
    case 'B':
        name = Pieces::BISHOP;
        break;
    case 'N':
        name = Pieces::KNIGHT;
        break;
    case 'K':
        name = Pieces::KING;
        break;
    case 'Q':
        name = Pieces::QUEEN;
        break;
    }
    return name;
}
std::string getPieceName(std::string piece)
{
    if (piece.empty())
    {
        return "Invalid";
    }

    std::string prefix = (isupper(piece[0])) ? "Black " : "White ";
    std::string name = getPieceType(piece);

    return prefix + name;
}
bool isSpotEmpty(std::string board[], int pos)
{
    return board[pos][0] == '\0';
}
bool validateMove(std::string board[], int from, int to, int turnNum)
{
    std::vector<int> possibleMoves = getPossibleMoves(board, from, turnNum);
    bool valid = true;
    bool toExistsInPossibleMoves = false;
    if (isupper(board[from][0]) && turnNum % 2 == 0)
    {
        return false;
    }
    if (!isupper(board[from][0]) && turnNum % 2 != 0)
    {
        return false;
    }
    for (int move : possibleMoves)
    {
        if (to == move)
        {
            toExistsInPossibleMoves = true;
            break;
        }
    }

    if (isSpotEmpty(board, from) || !toExistsInPossibleMoves || from == to)
    {
        valid = false;
    }

    return valid;
}

bool eatsPiece(std::string board[], int from, int to)
{
    char movedPiece = board[from][0];
    char placedPos = board[to][0];
    return (!isSpotEmpty(board, to));
}
std::vector<int> getPossibleMoves(std::string board[], int from, int turnNum)
{
    std::vector<int> possibleMoves;
    std::string piece = getPieceType(board[from]);
    if (piece == Pieces::KING)
    {
        if (from + 8 < BOARD_SIZE && (isSpotEmpty(board, from + 8) || isSpotSelfColor(board, from, from + 8)))
        {
            possibleMoves.push_back(from + 8);
        }
        if (from - 8 >= 0 && (isSpotEmpty(board, from - 8) || isSpotSelfColor(board, from, from - 8)))
        {
            possibleMoves.push_back(from - 8);
        }
        if (from % 8 != 7 && (isSpotEmpty(board, from + 1) || isSpotSelfColor(board, from, from + 1)))
        {
            possibleMoves.push_back(from + 1);
        }
        if (from % 8 != 0 && (isSpotEmpty(board, from - 1) || isSpotSelfColor(board, from, from - 1)))
        {
            possibleMoves.push_back(from - 1);
        }
        if (from + 7 < BOARD_SIZE && from % 8 != 0 && (isSpotEmpty(board, from + 7) || isSpotSelfColor(board, from, from + 7)))
        {
            possibleMoves.push_back(from + 7);
        }
        if (from - 7 >= 0 && from % 8 != 7 && (isSpotEmpty(board, from - 7) || isSpotSelfColor(board, from, from - 7)))
        {
            possibleMoves.push_back(from - 7);
        }
        if (from + 9 < BOARD_SIZE && from % 8 != 7 && (isSpotEmpty(board, from + 9) || isSpotSelfColor(board, from, from + 9)))
        {
            possibleMoves.push_back(from + 9);
        }
        if (from - 9 >= 0 && from % 8 != 0 && (isSpotEmpty(board, from - 9) || isSpotSelfColor(board, from, from - 9)))
        {
            possibleMoves.push_back(from - 9);
        }
    }
    else if (piece == Pieces::PAWN)
    {
        if (!isupper(board[from][0]))
        {
            if (from + 8 < BOARD_SIZE && isSpotEmpty(board, from + 8))
            {
                possibleMoves.push_back(from + 8);
            }
            if (turnNum == 0 && from + 16 < BOARD_SIZE && isSpotEmpty(board, from + 16))
            {
                possibleMoves.push_back(from + 16);
            }
            if (from + 9 < BOARD_SIZE && isSpotSelfColor(board, from, from + 9))
            {
                possibleMoves.push_back(from + 9);
            }
        }
        else
        {
            if (from - 8 < BOARD_SIZE && isSpotEmpty(board, from - 8))
            {
                possibleMoves.push_back(from - 8);
            }
            if (from - 9 < BOARD_SIZE && isSpotSelfColor(board, from, from - 9))
            {
                possibleMoves.push_back(from - 9);
            }
            if (turnNum == 1 && from - 16 < BOARD_SIZE && isSpotEmpty(board, from - 16))
            {
                possibleMoves.push_back(from - 16);
            }
        }
    }
    else if (piece == Pieces::ROOK)
    {
        std::vector<int> positions = generateRookMovements(board, from);
        possibleMoves = positions;
    }
    else if (piece == Pieces::BISHOP)
    {
        possibleMoves = generateBishopMovements(board, from);
    }
    else if (piece == Pieces::KNIGHT)
    {
        int x = from % 8;
        int y = from / 8;

        int knightMoves[8][2] = {
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

        for (int i = 0; i < 8; i++)
        {
            int dx = knightMoves[i][0];
            int dy = knightMoves[i][1];
            int to = (y + dy) * 8 + (x + dx);

            if (to >= 0 && to < BOARD_SIZE)
            {
                if (isSpotEmpty(board, to) || isSpotEnemy(board, from, to))
                {
                    possibleMoves.push_back(to);
                }
            }
        }
    }

    else if (piece == Pieces::QUEEN)
    {
        std::vector<int> bishopMovements = generateBishopMovements(board, from);
        std::vector<int> rookMovements = generateRookMovements(board, from);
        std::vector<int> movements;
        movements.insert(movements.end(), rookMovements.begin(), rookMovements.end());
        movements.insert(movements.end(), bishopMovements.begin(), bishopMovements.end());
        possibleMoves = movements;
    }
    return possibleMoves;
}
std::vector<int> generateRookMovements(std::string board[], int from)
{
    std::vector<int> possibleMoves;
    int x = from % 8;
    int y = from / 8;

    // Check moves to the right
    for (int i = x + 1; i < 8; i++)
    {
        int to = y * 8 + i;
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    // Check moves to the left
    for (int i = x - 1; i >= 0; i--)
    {
        int to = y * 8 + i;
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    // Check moves upward
    for (int i = y + 1; i < 8; i++)
    {
        int to = i * 8 + x;
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    // Check moves downward
    for (int i = y - 1; i >= 0; i--)
    {
        int to = i * 8 + x;
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    return possibleMoves;
}

std::vector<int> generateBishopMovements(std::string board[], int from)
{
    std::vector<int> possibleMoves;

    // Bishop moves diagonally
    int x = from % 8;
    int y = from / 8;

    // Diagonal (top-left to bottom-right)
    for (int i = 1; x + i < 8 && y + i < 8; i++)
    {
        int to = (y + i) * 8 + (x + i);
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }
    for (int i = 1; x - i >= 0 && y - i >= 0; i++)
    {
        int to = (y - i) * 8 + (x - i);
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    // Diagonal (top-right to bottom-left)
    for (int i = 1; x + i < 8 && y - i >= 0; i++)
    {
        int to = (y - i) * 8 + (x + i);
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }
    for (int i = 1; x - i >= 0 && y + i < 8; i++)
    {
        int to = (y + i) * 8 + (x - i);
        if (isSpotSelfColor(board, from, to))
        {
            possibleMoves.push_back(to);
            break; // Stop when we encounter our own piece
        }
        possibleMoves.push_back(to);
        if (isSpotEnemy(board, from, to))
        {
            break; // Stop when we encounter an enemy piece
        }
    }

    return possibleMoves;
}

template <typename T>
std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<T> temp = v1;
    temp.insert(temp.end(), v2.begin(), v2.end());
    return temp;
}
bool isSpotEnemy(std::string board[], int from, int to)
{
    bool isEnemy = false;
    if (isupper(board[from][0]) && !isupper(board[to][0]))
    {
        isEnemy = true;
    }
    else if (!isupper(board[from][0]) && isupper(board[to][0]))
    {
        isEnemy = true;
    }
    return isEnemy;
}
bool isSpotSelfColor(std::string board[], int from, int to)
{
    if (board[to][0] == '\0')
    {
        return false;
    };
    return isSpotEnemy(board, from, to);
}