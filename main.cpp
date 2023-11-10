#include "Util/util.h"
#include "Engine/engine.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

template <typename T, size_t N>
int getArraySize(T (&array)[N]);
template <typename T, size_t N>
void switchArrayItems(T (&array)[N], int pos1, int pos2);
int convertMove(std::string pos);
void makeMove(int from, int to);
int turnNum = 0;
bool whitesTurn = true;
bool showMode = false;
// Constants

// Function prototypes
string board[BOARD_SIZE]; // Declare the board array
string prevBoard[BOARD_SIZE];
int main()
{
	string pieces = DEFAULT_BOARD;
	initBoard(board, pieces); // Initialize the board with empty strings
	printBoard(board, whitesTurn);
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
			std::vector<int> highlight = getPossibleMoves(board, toPosIndex, turnNum);
			printBoard(board, whitesTurn, highlight);
			continue;
		}
		cin >> to;

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

	return 0;
}

template <typename T, size_t N>
int getArraySize(T (&array)[N])
{
	return N;
}

template <typename T, size_t N>
void switchArrayItems(T (&array)[N], int pos1, int pos2)
{
	T temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}
int convertMove(string pos)
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
void makeMove(int from, int to)
{
	// validate move
	if (validateMove(board, from, to, turnNum))
	{
		if (eatsPiece(board, from, to))
		{
			cout << endl
				 << "  "
				 << getPieceName(board[from])
				 << " Ate " << getPieceName(board[to]) << endl
				 << endl;
			board[to] = "\0 ";
		}
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			prevBoard[i] = board[i];
		}

		switchArrayItems(board, from, to);
		whitesTurn = !whitesTurn;
		turnNum++;
		printBoard(board, whitesTurn);
	}
	else
	{
		cout << endl
			 << "	Invalid move." << endl
			 << endl;
	}
}
