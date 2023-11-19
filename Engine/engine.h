#ifndef ENGINE_H
#define ENGINE_H

#include <cstddef>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include "../Util/colors.h"

namespace Chess
{
    class Engine
    {
    public:
        // Constants
        static const std::string DEFAULT_BOARD;

        // Board functions
        static void printBoard(std::vector<int> highlighted);
        static void initBoard(std::string pieces);
        static std::string getPieceName(std::string piece);
        static bool isSpotEmpty(int pos);
        static bool validateMove(int from, int to);
        static bool eatsPiece(int from, int to);
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
        static bool isBlackChecked(std::string board[]);
        static bool isWhiteChecked(std::string board[]);
        template <typename T>
        static std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2);
        static bool isMoveLegal(int from, int to);
        static std::string getPieceType(std::string piece);

        // Piece types
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

        // Movement generation functions
        static std::vector<int> generateRookMovements(int from);
        static std::vector<int> generateBishopMovements(int from);

        // Additional board printing function
        static void printBoard();
        static bool isCheckmate(bool isWhite);
    };
}

#endif
