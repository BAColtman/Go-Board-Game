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

//std::array<char, boardSize> initialiseLetterArray();

//takes a row and column value and picks out the correct element of the 1D array
position_t boardIndex(int row, int column);

// use an alias for the board type, can replace with a class later if I want
using board_t = std::array<Stones, pointNumber>;
board_t initialiseGame();

int letterToColumnNumber(char letter);

std::string printColour(StoneColour stone);

std::string printColour(StoneColourCaps stone);

std::array<char, boardSize> initialiseLetterArray();

void sortVectorDescending(neighbour_t& neighbours);

void removeInvalidPositionsSorted(neighbour_t& neighbours);

void removeInvalidPositions(neighbour_t& neighbours);

int numberCharactersToInteger(char numberCharacter);

int numberCharactersToInteger(std::string numString);

bool isValidDigit(char numberCharacter);

bool isValidLetter(char letter);

bool isValidLetter(int letterInteger);

bool isValidDigit(int digit);

#endif // !LABELS_H