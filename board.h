#ifndef BOARD_H
#define BOARD_H

#include "setup.h"
#include "stones.h"
#include "output.h"
#include "scoreTracker.h"
#include "inputValidator.h"



class Board
{
public:
	//using board_t = std::array<const Stones, constants::pointNumber>;

private:

	board_t m_board;
	//std::array<std::reference_wrapper<Stones>, constants::pointNumber> m_board;
	lettersArray_t m_letters;
	ScoreTracker m_score;
	InputValidator m_inputValidator;
	Output m_output;
	



public:
	Board()
	{
		m_letters = initialiseLetterArray();
	}

	//Stones getStone(position_t position) { return (m_board.at(position)); }
	//Stones& getStone(position_t position) { return (*this).m_board.at(position)); }

	void displayBoard();

	position_t getMove();

	void hasBeenTaken(position_t position, Stones::StoneColour stoneColour);

	void placeMove(Stones::StoneColour turnColour, position_t stonePosition);

	void addToGroup(position_t stoneToAddPosition, position_t groupMember);

	group_t mergeGroups(group_t group1, group_t group2);

	group_t mergeLiberties(group_t lib1, group_t lib2, group_t stoneGroup);

	position_t askForAnotherMove();

	bool hasEmptyLiberties(Stones& nodeStone, Stones::StoneColour stoneColour);

	std::array<Stones, 2> biggerGroup(Stones stoneWithGroupToAdd, Stones nodeStone);

	position_t moveInputToPosition(std::string move);

	lettersArray_t initialiseLetterArray();

	lettersArray_t getLetters() { return m_letters; }

	ScoreTracker& getScoreTracker()  { return m_score; }

	void removePointFromGroup(position_t stonePosition);

	void setPointToEmptyStone(position_t stonePosition);
};






#endif // !BOARD_H