#ifndef LABELS_H
#define LABELS_H


#include "setup.h"
#include "stones.h"
#include <algorithm>
#include <sstream>

StoneColour symbolToColour(char symbol);

StoneColour switchColour(StoneColour turnColour);

char stoneColourToSymbol(StoneColour stone);

int boardLabelReverse(int i);

//takes a row and column value and picks out the correct element of the 1D array
position_t boardIndex(int row, int column);

int letterToColumnNumber(char letter);

std::string printColour(StoneColour stone);

std::string printColour(StoneColourCaps stone);

void sortVectorDescending(neighbour_t& neighbours);

void removeInvalidPositionsSorted(neighbour_t& neighbours);

void removeInvalidPositions(neighbour_t& neighbours);

int numberCharactersToInteger(char numberCharacter);

int numberCharactersToInteger(std::string numString);

bool isValidDigit(char numberCharacter);

bool isValidLetter(char letter);

bool isValidLetter(int letterInteger);

bool isValidDigit(int digit);

void removeInvalidPositions(neighbour_t& neighbours);

void removeInvalidPositionsSorted(neighbour_t& neighbours);

void sortVectorDescending(neighbour_t& neighbours);

#endif // !LABELS_H