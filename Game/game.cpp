#include "game.h"
int Game::turnNum = 0;
bool Game::whitesTurn = true;
bool Game::showMode = false;
bool Game::ignoreRules = false;
std::string Game::board[BOARD_SIZE];
std::string Game::prevBoard[BOARD_SIZE];
void Game::init()
{
	turnNum = 0;
	whitesTurn = true;
	showMode = false;
	ignoreRules = false;

	std::string pieces = DEFAULT_BOARD;
	initBoard(pieces);
	printBoard(whitesTurn);
}
void Game::makeMove(int from, int to)
{
	// validate move
	if (validateMove(from, to, turnNum) || ignoreRules)
	{
		// Backup the board state
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			prevBoard[i] = board[i];
		}

		// Check if a piece is eaten
		if (eatsPiece(from, to))
		{
			std::cout << "  " << getPieceName(board[from]) << " captures " << getPieceName(board[to]) << std::endl;
			board[to] = "\0 ";
		}
		// Move the piece
		switchArrayItems(board, from, to);
		cout << endl;
		if (isWhiteChecked(turnNum))
		{
			cout << "	White king is checked!";
		}
		if (isBlackChecked(turnNum))
		{
			cout << "	Black king is checked!";
		}
		cout << endl;
		// Switch turns and increment the turn number
		whitesTurn = !whitesTurn;
		turnNum++;

		// Print the updated board
		printBoard(whitesTurn);
	}
	else
	{
		std::cout << "  Invalid move." << std::endl;
	}
}
int Game::convertMove(string pos)
{
	char x = toupper(pos[1]);
	int y = pos[0] - '0';
	int xPos = 1;
	switch (x)
	{
	case 'A':
		xPos = 1;
		break;
	case 'B':
		xPos = 2;
		break;
	case 'C':
		xPos = 3;
		break;
	case 'D':
		xPos = 4;
		break;
	case 'E':
		xPos = 5;
		break;
	case 'F':
		xPos = 6;
		break;
	case 'G':
		xPos = 7;
		break;
	case 'H':
		xPos = 8;
		break;
	}
	return twoDIndexTo1D(xPos - 1, y - 1, 8);
}
void Game::gameLoop()
{
	std::string from, to;
	while (true)
	{
		cout << endl
			 << "   Enter Board Positions: ";
		cin >> from;
		if (from == "exit")
		{
			break; // Exit the loop when "exit" is entered
		}
		if (from == "show")
		{
			cin >> to;
			int toPosIndex = convertMove(to);
			std::vector<int> highlight = getPossibleMoves(toPosIndex, turnNum);
			printBoard(whitesTurn, highlight);
			continue;
		}
		if (from == "ignoreRules")
		{
			ignoreRules = !ignoreRules;
			continue;
		}
		cin >> to;
		cout << endl;
		int fromPosIndex = -1;
		int toPosIndex = -1;

		fromPosIndex = convertMove(from);
		toPosIndex = convertMove(to);

		if (fromPosIndex != -1)
		{
			if (inRange(fromPosIndex, 0, 64) &&
				inRange(toPosIndex, 0, 64) &&
				from.length() == 2 && to.length() == 2)
			{
				makeMove(fromPosIndex, toPosIndex);
			}
			else
			{
				cout << "  Invalid position entered." << endl;
			}
		}
	}
}