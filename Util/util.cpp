#include "util.h"

bool inRange(double value, double minVal, double maxVal)
{
	return value >= minVal && value < maxVal;
}

int twoDIndexTo1D(int x, int y, int rowLength)
{
	int oneDIndex = (y * rowLength) + x;
	return oneDIndex;
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

void switchArrayItems(std::string array[], int pos1, int pos2)
{
	std::string temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}