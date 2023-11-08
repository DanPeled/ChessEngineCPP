#include <cstddef>
#include <string>
const int BOARD_SIZE = 64;
const std::string DEFAULT_BOARD = "rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR";
void printBoard(std::string board[], int size);
void initBoard(std::string board[], std::string pieces);
std::string getPieceName(std::string piece);