#include <cstddef>
#include <string>
const int BOARD_SIZE = 64;
const std::string DEFAULT_BOARD = "rnbqkbnrppppppppddddPPPPPPPPRNBQKBNR";
void printBoard(std::string board[], int size);
void initBoard(std::string board[], std::string pieces);
std::string getPieceName(std::string piece);
bool isSpotEmpty(std::string board[], int pos);
bool validateMove(std::string board[], int from, int to);
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