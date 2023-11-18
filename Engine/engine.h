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
void printBoard(bool whitesTurn);
void initBoard(std::string pieces);
std::string getPieceName(std::string piece);
bool isSpotEmpty(int pos);
bool validateMove(int from, int to, int turnNum);
bool eatsPiece(int from, int to);
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
std::vector<int> getPossibleMoves(int from, int turnNum);
template <typename T>
std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2);
bool isSpotSelfColor(int from, int to);
bool isSpotEnemy(int from, int to);
void printBoard(bool whitesTurn, std::vector<int> highlighted);
bool isWhiteChecked(int turnNum);
bool isBlackChecked(int turnNum);
std::string getPieceSymbol(char piece);
int convertMove(std::string pos);
void makeMove(int from, int to);
void makeMove(std::string prevBoard[], int from, int to, int turnNum, bool ignoreRules, bool *whitesTurn);
#endif