#include "../Util/util.h"
#include "../Engine/engine.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;
const int BOARD_SIZE = 64;
namespace Chess
{
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
		static void savePrevBoardState();
		static void printCheckedStatus();
		static void handleShowInput(const std::string &to);
		static void handleIgnoreRulesInput();
		static bool isValidMoveInput(int from, int to);
	};
};
