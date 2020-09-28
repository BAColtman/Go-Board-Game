// a stone has the information of what colour it is, what group it's a part of, 
// where it is on the board and if it is the head for a stone group which stones are in that group

#include "stones.h"
#include "board.h"

//sets the entry of a stone on the board to reflect that a stone is not there
void Stones::setEmptyStone(board_t& m_board, position_t position)
{
	setColour(StoneColour::empty);
	setWhichGroup(constants::noPosition);
	setGroup(constants::emptyGroup);
	//resetLiberties(board, position);
	m_board.at(position).setLiberties(findNeighbourPositions());
}

//changes the entry of a stone on the board to reflect that it has been placed
void Stones::placeStone(position_t position, StoneColour colour)
{
	setColour(colour);
	setWhichGroup(position);
	setGroup({ position });
}


void Stones::resetLiberties(board_t &m_board, position_t position)
{
	m_board.at(position).setLiberties(findNeighbourPositions());
}

neighbour_t Stones::findNeighbourPositions()
{
	position_t position = m_position;
	//I shall use -1 to mean invalid neighbour e.g. the left-most stones do not have left neighbours
	neighbour_t neighbours{ constants::noPosition, constants::noPosition, constants::noPosition, constants::noPosition };
	//neighbours are listed in order of: up right down left

	//check it's not on the top side of the board
	if (position > (constants::boardSize - constants::zeroOffset))
	{
		neighbours.at(0) = position - constants::boardSize;
	}

	//check it's not on the right side of the board
	if ((position + constants::zeroOffset) % constants::boardSize)
	{
		neighbours.at(1) = position + 1;
	}

	//check it's not on the bottom side of the board
	if (position < ((constants::pointNumber - constants::boardSize) - constants::zeroOffset))
	{
		neighbours.at(2) = position + constants::boardSize;
	}

	//check it's not on the left side of the board
	if (position % constants::boardSize)
	{
		neighbours.at(3) = position - 1;
	}

	removeInvalidPositions(neighbours);

	return neighbours;
}
