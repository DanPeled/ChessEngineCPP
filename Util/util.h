// util.h
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstddef>

bool inRange(double value, double minVal, double maxVal);

int twoDIndexTo1D(int x, int y, int rowLength);

template <typename T, size_t N>
int getArraySize(T (&array)[N]);

template <typename T, size_t N>
void switchArrayItems(T (&array)[N], int pos1, int pos2);

void switchArrayItems(std::string array[], int pos1, int pos2);

#endif
