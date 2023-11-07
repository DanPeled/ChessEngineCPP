#include "Util/util.h"
#include "Engine/engine.h"
#include <iostream>
#include <string>

template <typename T, size_t N>
int getArraySize(T (&array)[N]);
template <typename T, size_t N>
void switchArrayItems(T (&array)[N], int pos1, int pos2);
int convertMove(int x, int y);
void makeMove(int from, int to);
using namespace std;

// Constants

// Function prototypes
string board[BOARD_SIZE]; // Declare the board array

int main()
{
	string pieces = DEFAULT_BOARD;
	initBoard(board, pieces); // Initialize the board with empty strings
	printBoard(board, BOARD_SIZE);
	int fromX, fromY;
	int toX, toY;
	while (true)
	{
		cout << "Enter Board Position: ";
		cin >> fromX >> fromY;
		cin >> toX >> toY;
		int boardPosIndex = -1;
		int toPosIndex = -1;
		if (inRange(fromX - 1, 0, 8) && inRange(fromY - 1, 0, 8))
		{
			boardPosIndex = convertMove(fromX, fromY);
			toPosIndex = convertMove(toX, toY);
		}
		else
		{
			cout << "Invalid position entered." << endl;
		}
		if (boardPosIndex != -1)
		{
			makeMove(boardPosIndex, toPosIndex);
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
int convertMove(int x, int y)
{
	return twoDIndexTo1D(x - 1, y - 1, 8);
}
void makeMove(int from, int to)
{
	// TODO : validate move
	switchArrayItems(board, from, to);
	printBoard(board, BOARD_SIZE);
}