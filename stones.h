#ifndef STONES_H
#define STONES_H

#include "setup.h"

// a stone has the information of what colour it is, what group it's a part of, 
// where it is on the board and if it is the head for a stone group which stones are in that group
class Stones
{
private:
	StoneColour m_colour{};
	position_t m_pointToGroup{};
	position_t m_position{};
	group_t m_groupMembers{};
	//Liberties are the spaces around a group that need to be filled for a group to be taken
	group_t m_groupLiberties{};

public:
	Stones()
	{
		//these will all be set once I initialise the board
		m_colour = StoneColour::empty;
		m_pointToGroup = noPosition;
		m_position = noPosition;
		m_groupMembers = emptyGroup;
		m_groupLiberties = emptyGroup;
	}

	StoneColour getColour() { return m_colour; }
	position_t getWhichGroup() { return m_pointToGroup; }
	position_t getPosition() { return m_position; }
	group_t getGroup() { return m_groupMembers; }
	group_t getLiberties() { return m_groupLiberties; }
	void setPosition(position_t position) { m_position = position; }
	void setColour(StoneColour colour) { m_colour = colour; }
	void setWhichGroup(position_t position) { m_pointToGroup = position; }
	void setGroup(group_t group) { m_groupMembers = group; }
	void setLiberties(group_t group) { m_groupLiberties = group; }
	void setEmptyStone();
	void placeStone(position_t position, StoneColour colour);
};


#endif // !STONES_H