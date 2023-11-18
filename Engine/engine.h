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
namespace Chess
{
    class Engine
    {
    public:
        /// @brief Uppercase - BLACK Lowercase - WHITE
        static const std::string DEFAULT_BOARD;
        static void printBoard(bool whitesTurn);
        static void initBoard(std::string pieces);
        static std::string getPieceName(std::string piece);
        static bool isSpotEmpty(int pos);
        static bool validateMove(int from, int to);
        static bool eatsPiece(int from, int to);
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
        static std::vector<int> getPossibleMoves(int from, int turnNum);
        static bool isSpotSelfColor(int from, int to);
        static bool isSpotEnemy(int from, int to);
        static void printBoard(bool whitesTurn, std::vector<int> highlighted);
        static bool isWhiteChecked();
        static bool isBlackChecked();
        static std::string getPieceSymbol(char piece);
        static int convertMove(std::string pos);
        static void makeMove(int from, int to);
        static void makeMove(std::string prevBoard[], int from, int to, int turnNum, bool ignoreRules, bool *whitesTurn);
        template <typename T>
        static std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2);
    };
};
#endif