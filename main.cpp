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
bool validateMove(int from, int to);
// Constants

// Function prototypes
string board[BOARD_SIZE]; // Declare the board array

int main()
{
	string pieces = DEFAULT_BOARD;
	initBoard(board, pieces); // Initialize the board with empty strings
	printBoard(board, BOARD_SIZE);
	std::string from, to;
	while (true)
	{
		cout << "  Enter Board Positions: ";
		cin >> from;
		if (from == "exit")
		{
			break; // Exit the loop when "exit" is entered
		}

		cin >> to;

		int fromPosIndex = -1;
		int toPosIndex = -1;

		fromPosIndex = convertMove(from);
		toPosIndex = convertMove(to);

		if (fromPosIndex != -1)
		{
			if (inRange(fromPosIndex, 0, 64) && inRange(toPosIndex, 0, 64) && from.length() == 2 && to.length() == 2)
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
	if (validateMove(board, from, to))
	{
		if (eatsPiece(board,from, to))
		{
			cout << endl
				 << "  "
				 << getPieceName(board[from])
				 << " Ate " << getPieceName(board[to]) << endl
				 << endl;
			board[to] = "\0 ";
		}
		switchArrayItems(board, from, to);
		printBoard(board, BOARD_SIZE);
	}
	else
	{
		cout << "Invalid move." << endl;
	}
}
