#ifndef ENGINE_H
#define ENGINE_H
#include <cstddef>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
#include "../Util/colors.h"
const int BOARD_SIZE = 64;
/// @brief Uppercase - BLACK Lowercase - WHITE
const std::string DEFAULT_BOARD = "rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR";
void printBoard(std::string board[], bool whitesTurn);
void initBoard(std::string board[], std::string pieces);
std::string getPieceName(std::string piece);
bool isSpotEmpty(std::string board[], int pos);
bool validateMove(std::string board[], int from, int to, int turnNum);
bool eatsPiece(std::string board[], int from, int to);
class Pieces
{
public:
    const static std::string BISHOP;
    const static std::string ROOK;
    const static std::string PAWN;
    const static std::string QUEEN;
    const static std::string KING;
    const static std::string KNIGHT;
};
std::vector<int> getPossibleMoves(std::string board[], int from, int turnNum);
template <typename T>
std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2);
bool isSpotSelfColor(std::string board[], int from, int to);
bool isSpotEnemy(std::string board[], int from, int to);
void printBoard(std::string board[], bool whitesTurn, std::vector<int> highlighted);
bool isWhiteChecked(std::string board[], int turnNum);
bool isBlackChecked(std::string board[], int turnNum);
std::string getPieceSymbol(char piece);
int convertMove(std::string pos);
void makeMove(int from, int to);
void makeMove(std::string board[], std::string prevBoard[], int from, int to, int turnNum, bool ignoreRules, bool *whitesTurn);
#endif