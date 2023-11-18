#include "../Util/util.h"
#include "../Engine/engine.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

class Game
{
public:
	static int turnNum;
	static bool whitesTurn;
	static bool showMode;
	static bool ignoreRules;
	static std::string board[BOARD_SIZE];
	static std::string prevBoard[BOARD_SIZE];
	static int convertMove(std::string pos);
	static void makeMove(int from, int to);
	static void init();
	static void gameLoop();
};
