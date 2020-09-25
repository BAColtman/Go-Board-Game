#ifndef BOARD_H
#define BOARD_H

#include "setup.h"
#include "stones.h"
#include "labels.h"
#include "score.h"
#include <string>


void displayBoard(board_t& board, lettersArray_t& letters);


neighbour_t neighbourPositions(position_t position);

position_t getMove(board_t& board);

void addToGroup();

void hasBeenTaken(board_t& board, position_t position, StoneColour stoneColour);

void placeMove(board_t& board, StoneColour turnColour, position_t position);

void addToGroup(board_t& board, position_t stoneToAddPosition, position_t groupMember);

group_t mergeGroups(group_t group1, group_t group2);

void removeInvalidPositions(neighbour_t &neighbours);

void removeInvalidPositionsSorted(neighbour_t &neighbours);

void sortVectorDescending(neighbour_t& neighbours);

position_t moveInputToPosition(board_t& board, std::string move);


#endif // !BOARD_H