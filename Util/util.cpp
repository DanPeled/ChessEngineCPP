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
