#ifndef BOARD_H
#define BOARD_H

#include "setup.h"
#include "stones.h"
#include "labels.h"
#include "score.h"




class Board
{
public:
	//using board_t = std::array<const Stones, constants::pointNumber>;
	std::array<Stones, constants::pointNumber> m_board;

private:
	friend class Stones;
	//board_t m_board;
	//std::array<const Stones, constants::pointNumber> m_board;
	//std::array<Stones, constants::pointNumber> m_board;
	//std::array<std::reference_wrapper<Stones>, constants::pointNumber> m_board;
	lettersArray_t m_letters;



public:
	Board()
	{
		m_letters = initialiseLetterArray();
	}

	//Stones getStone(position_t position) { return (m_board.at(position)); }
	//Stones& getStone(position_t position) { return (*this).m_board.at(position)); }

	void displayBoard();

	position_t getMove();

	void hasBeenTaken(position_t position, StoneColour stoneColour);

	void placeMove(StoneColour turnColour, position_t stonePosition);

	void addToGroup(position_t stoneToAddPosition, position_t groupMember);

	group_t mergeGroups(group_t group1, group_t group2);

	group_t mergeLiberties(group_t lib1, group_t lib2, group_t stoneGroup);

	position_t askForAnotherMove();

	bool hasEmptyLiberties(Stones& nodeStone, StoneColour stoneColour);

	std::array<Stones, 2> biggerGroup(Stones stoneWithGroupToAdd, Stones nodeStone);

	position_t moveInputToPosition(std::string move);

};






#endif // !BOARD_H