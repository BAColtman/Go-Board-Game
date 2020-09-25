#ifndef SCORE_H
#define SCORE_H

#include "setup.h"
#include "labels.h"


using score_t = int;

score_t getScore(StoneColour turnColour);

void changeScore(StoneColour turnColour, int change);

void score();

void finalScore(board_t &board, lettersArray_t letters);

void displayBoard(board_t& board, lettersArray_t& letters);

#endif // !SCORE_H