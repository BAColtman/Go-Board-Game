#ifndef SCORE_H
#define SCORE_H

#include "setup.h"
#include "labels.h"
#include "board.h"


using score_t = int;

score_t getScore(StoneColour turnColour);

void changeScore(StoneColour turnColour, int change);

void score();

void finalScore(Board& board);

#endif // !SCORE_H