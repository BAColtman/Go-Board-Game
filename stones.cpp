// a stone has the information of what colour it is, what group it's a part of, 
// where it is on the board and if it is the head for a stone group which stones are in that group

#include "stones.h"

//sets the entry of a stone on the board to reflect that a stone is not there
void Stones::setEmptyStone(board_t& board, position_t position)
{
	setColour(StoneColour::empty);
	setWhichGroup(constants::noPosition);
	setGroup(constants::emptyGroup);
	//resetLiberties(board, position);
	board.at(position).setLiberties(neighbourPositions(position));
}

//changes the entry of a stone on the board to reflect that it has been placed
void Stones::placeStone(position_t position, StoneColour colour)
{
	setColour(colour);
	setWhichGroup(position);
	setGroup({ position });
}


void Stones::resetLiberties(board_t &board, position_t position)
{
	board.at(position).setLiberties(neighbourPositions(position));
}
