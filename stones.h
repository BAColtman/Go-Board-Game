#ifndef STONES_H
#define STONES_H

#include "setup.h"

void removeInvalidPositions(neighbour_t& neighbours);

// a stone has the information of what colour it is, what group it's a part of, 
// where it is on the board and if it is the head for a stone group which stones are in that group
class Stones
{
public:

	//enumerator to decide what, if anything, is on a particular space on the board
	enum class StoneColour
	{
		empty,
		black,
		white
	};


	enum class StoneColourCaps
	{
		Empty,
		Black,
		White
	};

private:
	friend class Board;
	Stones::StoneColour m_colour{};
	position_t m_pointToGroup{};
	static position_t s_positionGenerator;
	position_t m_position{};
	group_t m_groupMembers{};
	//Liberties are the spaces around a group that need to be filled for a group to be taken
	group_t m_groupLiberties{};

public:
	Stones();

	Stones::StoneColour getColour() const { return m_colour; }
	position_t getWhichGroup() const { return m_pointToGroup; }
	position_t getPosition() const { return m_position; }
	group_t getGroup() const { return m_groupMembers; }
	group_t getLiberties() const { return m_groupLiberties; }
	void setPosition(position_t position) { m_position = position; }
	void setColour(Stones::StoneColour colour) { m_colour = colour; }
	void setWhichGroup(position_t position) { m_pointToGroup = position; }
	void setGroup(group_t group) { m_groupMembers = group; }
	void setLiberties(group_t group) { m_groupLiberties = group; }
	void placeStone(position_t position, Stones::StoneColour colour);
	void resetLiberties();
	neighbour_t findNeighbourPositions();
};






#endif // !STONES_H