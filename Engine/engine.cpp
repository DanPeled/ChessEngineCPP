#include "engine.h"
#include "../Game/game.h"
using namespace Chess;
const std::string Engine::Pieces::BISHOP = "Bishop";
const std::string Engine::Pieces::ROOK = "Rook";
const std::string Engine::Pieces::PAWN = "Pawn";
const std::string Engine::Pieces::QUEEN = "Queen";
const std::string Engine::Pieces::KING = "King";
const std::string Engine::Pieces::KNIGHT = "Knight";
const std::string Engine::DEFAULT_BOARD = "rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR";
std::vector<int> generateRookMovements(int from);
std::vector<int> generateBishopMovements(int from);
void copyStringArray(const std::string source[], std::string destination[], int size);

void Engine::printBoard(bool whitesTurn, std::vector<int> highlighted)
{
    // SetConsoleOutputCP(CP_UTF8);
    std::cout << "  | A | B | C | D | E | F | G | H |" << std::endl;
    std::cout << "  |___|___|___|___|___|___|___|___|" << std::endl;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (i % 8 == 0)
        {
            std::cout << " " << (i / 8) + 1 << "|";
        }

        if (Game::board[i] == "")
        {
            if (std::find(highlighted.begin(), highlighted.end(), i) != highlighted.end())
            {
                std::cout << BG_GREEN << "   " << RESET << "|";
            }
            else
            {
                std::cout << "   |"; // Print a blank space for an empty cell
            }
        }
        else
        {
            if (std::find(highlighted.begin(), highlighted.end(), i) != highlighted.end())
            {
                std::cout << BG_GREEN << " " << (isupper(Chess::Game::board[i][0]) ? BOLDBLACK : BOLDWHITE) << Chess::Game::board[i]
                          << " " << RESET << "|";
            }
            else
            {
                std::cout << " " << (isupper(Chess::Game::board[i][0]) ? BOLDBLACK : BOLDWHITE) << Chess::Game::board[i] << RESET
                          << " |";
            }
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
void Engine::printBoard(std::vector<int> highlighted)
{
    Engine::printBoard(Game::whitesTurn, highlighted);
}
void Engine::printBoard()
{
    Engine::printBoard(Game::whitesTurn, {});
}
void Engine::initBoard(std::string pieces)
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
                    Chess::Game::board[boardIndex] = "";
                    boardIndex++;
                }
            }
        }
        else
        {
            if (boardIndex < BOARD_SIZE)
            {
                Chess::Game::board[boardIndex] = pieces[i];
                boardIndex++;
            }
        }
    }

    // Fill any remaining positions with empty strings
    for (; boardIndex < BOARD_SIZE; boardIndex++)
    {
        Chess::Game::board[boardIndex] = "";
    }
}
std::string Engine::getPieceType(std::string piece)
{
    std::string name = "Invalid";
    switch (toupper(piece[0]))
    {
    case 'R':
        name = Engine::Pieces::ROOK;
        break;
    case 'P':
        name = Engine::Pieces::PAWN;
        break;
    case 'B':
        name = Engine::Pieces::BISHOP;
        break;
    case 'N':
        name = Engine::Pieces::KNIGHT;
        break;
    case 'K':
        name = Engine::Pieces::KING;
        break;
    case 'Q':
        name = Engine::Pieces::QUEEN;
        break;
    }
    return name;
}
std::string Engine::getPieceName(std::string piece)
{
    if (piece.empty())
    {
        return "Invalid";
    }

    std::string prefix = (isupper(piece[0])) ? "Black " : "White ";
    std::string name = getPieceType(piece);

    return prefix + name;
}
bool Engine::isSpotEmpty(int pos)
{
    return Chess::Game::board[pos].empty();
}

bool Engine::validateMove(int from, int to)
{
    std::vector<int> possibleMoves = getPossibleMoves(from, Chess::Game::turnNum);
    bool valid = true;
    bool toExistsInPossibleMoves = false;
    if (isupper(Chess::Game::board[from][0]) && Chess::Game::turnNum % 2 == 0)
    {
        return false;
    }
    if (!isupper(Chess::Game::board[from][0]) && Chess::Game::turnNum % 2 != 0)
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

    if (isSpotEmpty(from) || !toExistsInPossibleMoves || from == to)
    {
        valid = false;
    }

    return valid;
}

bool Engine::eatsPiece(int from, int to)
{
    char movedPiece = Chess::Game::board[from][0];
    char placedPos = Chess::Game::board[to][0];
    return (!isSpotEmpty(to));
}
std::vector<int> Engine::getPossibleMoves(int from, int turnNum)
{
    std::vector<int> possibleMoves;
    std::string piece = getPieceType(Chess::Game::board[from]);
    if (piece == Engine::Pieces::KING)
    {
        if (from + 8 < BOARD_SIZE && (Engine::isSpotEmpty(from + 8) || Engine::isSpotSelfColor(from, from + 8)))
        {
            possibleMoves.push_back(from + 8);
        }
        if (from - 8 >= 0 && (Engine::isSpotEmpty(from - 8) || Engine::isSpotSelfColor(from, from - 8)))
        {
            possibleMoves.push_back(from - 8);
        }
        if (from % 8 != 7 && (Engine::isSpotEmpty(from + 1) || Engine::isSpotSelfColor(from, from + 1)))
        {
            possibleMoves.push_back(from + 1);
        }
        if (from % 8 != 0 && (Engine::isSpotEmpty(from - 1) || Engine::isSpotSelfColor(from, from - 1)))
        {
            possibleMoves.push_back(from - 1);
        }
        if (from + 7 < BOARD_SIZE && from % 8 != 0 && (Engine::isSpotEmpty(from + 7) || Engine::isSpotSelfColor(from, from + 7)))
        {
            possibleMoves.push_back(from + 7);
        }
        if (from - 7 >= 0 && from % 8 != 7 && (Engine::isSpotEmpty(from - 7) || Engine::isSpotSelfColor(from, from - 7)))
        {
            possibleMoves.push_back(from - 7);
        }
        if (from + 9 < BOARD_SIZE && from % 8 != 7 && (Engine::isSpotEmpty(from + 9) || Engine::isSpotSelfColor(from, from + 9)))
        {
            possibleMoves.push_back(from + 9);
        }
        if (from - 9 >= 0 && from % 8 != 0 && (Engine::isSpotEmpty(from - 9) || Engine::isSpotSelfColor(from, from - 9)))
        {
            possibleMoves.push_back(from - 9);
        }
    }
    else if (piece == Engine::Pieces::PAWN)
    {
        int y = from / 8;
        if (!isupper(Chess::Game::board[from][0]))
        {
            if (from + 8 < BOARD_SIZE && isSpotEmpty(from + 8))
            {
                possibleMoves.push_back(from + 8);
            }
            if (y == 1 && from + 16 < BOARD_SIZE && isSpotEmpty(from + 16))
            {
                possibleMoves.push_back(from + 16);
            }
            if (from + 9 < BOARD_SIZE && Engine::isSpotEnemy(from, from + 9))
            {
                possibleMoves.push_back(from + 9);
            }
            if (from + 7 < BOARD_SIZE && Engine::isSpotEnemy(from, from + 7))
            {
                possibleMoves.push_back(from + 7);
            }
        }
        else
        {
            if (from - 8 < BOARD_SIZE && Engine::isSpotEmpty(from - 8))
            {
                possibleMoves.push_back(from - 8);
            }
            if (from - 9 < BOARD_SIZE && Engine::isSpotEnemy(from, from - 9))
            {
                possibleMoves.push_back(from - 9);
            }
            if (from - 7 < BOARD_SIZE && Engine::isSpotEnemy(from, from - 7))
            {
                possibleMoves.push_back(from - 7);
            }
            if (y == 6 && from - 16 < BOARD_SIZE && isSpotEmpty(from - 16))
            {
                possibleMoves.push_back(from - 16);
            }
        }
    }
    else if (piece == Engine::Pieces::ROOK)
    {
        std::vector<int> positions = generateRookMovements(from);
        possibleMoves = positions;
    }
    else if (piece == Engine::Pieces::BISHOP)
    {
        possibleMoves = generateBishopMovements(from);
    }
    else if (piece == Engine::Pieces::KNIGHT)
    {
        int x = from % 8;
        int y = from / 8;

        int knightMoves[8][2] = {
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

        for (int i = 0; i < 8; i++)
        {
            int dx = knightMoves[i][0];
            int dy = knightMoves[i][1];
            int toX = x + dx;
            int toY = y + dy;
            int to = toY * 8 + toX;

            if (toX >= 0 && toX < 8 && toY >= 0 && toY < 8)
            {
                if (Engine::isSpotEmpty(to) || Engine::isSpotEnemy(from, to))
                {
                    possibleMoves.push_back(to);
                }
            }
        }
    }
    else if (piece == Engine::Pieces::QUEEN)
    {
        std::vector<int> bishopMovements = generateBishopMovements(from);
        std::vector<int> rookMovements = generateRookMovements(from);
        std::vector<int> movements;
        movements.insert(movements.end(), rookMovements.begin(), rookMovements.end());
        movements.insert(movements.end(), bishopMovements.begin(), bishopMovements.end());
        possibleMoves = movements;
    }
    return possibleMoves;
}

std::vector<int> Engine::generateRookMovements(int from)
{
    std::vector<int> possibleMoves;
    int x = from % 8;
    int y = from / 8;

    // Check moves to the right
    for (int i = x + 1; i < 8; i++)
    {
        int to = y * 8 + i;
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    // Check moves to the left
    for (int i = x - 1; i >= 0; i--)
    {
        int to = y * 8 + i;
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    // Check moves upward
    for (int i = y + 1; i < 8; i++)
    {
        int to = i * 8 + x;
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    // Check moves downward
    for (int i = y - 1; i >= 0; i--)
    {
        int to = i * 8 + x;
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    return possibleMoves;
}

std::vector<int> Engine::generateBishopMovements(int from)
{
    std::vector<int> possibleMoves;

    // Bishop moves diagonally
    int x = from % 8;
    int y = from / 8;

    // Diagonal (top-left to bottom-right)
    for (int i = 1; x + i < 8 && y + i < 8; i++)
    {
        int to = (y + i) * 8 + (x + i);
        if (!Engine::isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }
    for (int i = 1; x - i >= 0 && y - i >= 0; i++)
    {
        int to = (y - i) * 8 + (x - i);
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    // Diagonal (top-right to bottom-left)
    for (int i = 1; x + i < 8 && y - i >= 0; i++)
    {
        int to = (y - i) * 8 + (x + i);
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }
    for (int i = 1; x - i >= 0 && y + i < 8; i++)
    {
        int to = (y + i) * 8 + (x - i);
        if (!isSpotEmpty(to))
        {
            if (Engine::isSpotSelfColor(from, to))
            {
                break; // Stop when we encounter our own piece
            }
            else if (Engine::isSpotEnemy(from, to))
            {
                possibleMoves.push_back(to);
            }
            break; // Stop when we encounter an enemy piece
        }
        possibleMoves.push_back(to);
    }

    return possibleMoves;
}

template <typename T>
std::vector<T> Engine::combineVectors(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<T> temp = v1;
    temp.insert(temp.end(), v2.begin(), v2.end());
    return temp;
}

bool Engine::isSpotEnemy(int from, int to)
{
    bool fromPieceColor = isupper(Chess::Game::board[from][0]);
    bool toPieceColor = isupper(Chess::Game::board[to][0]);
    // Check if the colors are different, indicating an enemy piece, and if the destination is not empty
    return (fromPieceColor != toPieceColor) && !isSpotEmpty(to);
}
bool Engine::isSpotSelfColor(int from, int to)
{
    char fromPieceColor = Chess::Game::board[from][0];
    char toPieceColor = Chess::Game::board[to][0];

    // Check if the colors are the same, indicating the same player's piece, and if the destination is not empty
    return (fromPieceColor == toPieceColor) && !isSpotEmpty(to);
}

bool Engine::isWhiteChecked()
{
    return isWhiteChecked(Chess::Game::board);
}

bool Engine::isBlackChecked()
{
    return isBlackChecked(Chess::Game::board);
}

bool Engine::isWhiteChecked(std::string board[])
{
    int whiteKingPos = -1;

    // Find the position of the white king
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i] == "k")
        {
            whiteKingPos = i;
            break;
        }
    }

    // If the white king position is not found, something is wrong
    if (whiteKingPos == -1)
    {
        std::cerr << "Error: White king not found on the board." << std::endl;
        return false;
    }

    // Iterate through the board to check if any black piece can attack the white king
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (isupper(board[i][0])) // Check if the piece is black
        {
            std::vector<int> blackPieceMoves = getPossibleMoves(i, 1); // Assuming it's black's turn (turnNum % 2 == 1)

            // Check if any move of the black piece is equal to the white king's position
            if (std::find(blackPieceMoves.begin(), blackPieceMoves.end(), whiteKingPos) != blackPieceMoves.end())
            {
                // The white king is in check
                return true;
            }
        }
    }

    // The white king is not in check
    return false;
}

bool Engine::isBlackChecked(std::string board[])
{
    int blackKingPos = -1;

    // Find the position of the black king
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i] == "K")
        {
            blackKingPos = i;
            break;
        }
    }

    // If the black king position is not found, something is wrong
    if (blackKingPos == -1)
    {
        std::cerr << "Error: Black king not found on the board." << std::endl;
        return false;
    }

    // Iterate through the board to check if any white piece can attack the black king
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (islower(board[i][0])) // Check if the piece is white
        {
            std::vector<int> whitePieceMoves = getPossibleMoves(i, 0); // Assuming it's white's turn (turnNum % 2 == 0)

            // Check if any move of the white piece is equal to the black king's position
            if (std::find(whitePieceMoves.begin(), whitePieceMoves.end(), blackKingPos) != whitePieceMoves.end())
            {
                // The black king is in check
                return true;
            }
        }
    }

    // The black king is not in check
    return false;
}

void copyStringArray(const std::string source[], std::string destination[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        destination[i] = source[i];
    }
}

bool Engine::isMoveLegal(int from, int to)
{
    // Check basic move validity
    if (!validateMove(from, to))
    {
        return false;
    }

    // Make a temporary copy of the board
    std::string tempBoard[BOARD_SIZE];
    copyStringArray(Game::board, tempBoard, BOARD_SIZE);

    // Simulate the move on the temporary board
    tempBoard[to] = tempBoard[from];
    tempBoard[from] = "";

    // Check if the move puts the player's own king in check
    if (isupper(Game::board[from][0]) && isWhiteChecked(tempBoard))
    {
        return false;
    }
    else if (islower(Game::board[from][0]) && isBlackChecked(tempBoard))
    {
        return false;
    }

    return true;
}

bool Engine::isCheckmate(bool isWhite)
{
    // Check if the king is in check
    if (isWhite && isWhiteChecked())
    {
        // Check if there are no legal moves for the white king
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (isupper(Game::board[i][0]))
            {
                std::vector<int> moves = getPossibleMoves(i, 0);
                for (int move : moves)
                {
                    if (isMoveLegal(i, move))
                    {
                        return false; // The king has a legal move
                    }
                }
            }
        }
        return true; // No legal moves for the white king
    }
    else if (!isWhite == 1 && isBlackChecked())
    {
        // Check if there are no legal moves for the black king
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (islower(Game::board[i][0]))
            {
                std::vector<int> moves = getPossibleMoves(i, 1);
                for (int move : moves)
                {
                    if (isMoveLegal(i, move))
                    {
                        return false; // The king has a legal move
                    }
                }
            }
        }
        return true; // No legal moves for the black king
    }

    return false; // The king is not in check or there are legal moves
}