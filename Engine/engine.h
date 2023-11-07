#include <cstddef>
#include <string>
const int BOARD_SIZE = 64;
const std::string DEFAULT_BOARD = "rnbqkbnrpppppppp8888pppppppprnbqkbnr";
void printBoard(std::string board[], int size);
void initBoard(std::string board[], std::string pieces);