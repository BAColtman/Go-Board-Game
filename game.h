#ifndef GAME_H
#define GAME_H

#include "setup.h"
#include "stones.h"
#include "output.h"
#include "scoreTracker.h"
#include "board.h"
#include "input.h"

class Game
{
private:
	Board m_board{};
	bool m_whichTurn;
	bool m_isEndGame;
	bool m_hasPassed;

public:
	Game()
	{
		m_isEndGame = false;
		m_hasPassed = false;
		//turn marker is a boolean, false means it's black's turn, true is white's turn
		m_whichTurn = false;
	};

	void initialiseGame();
	void printTurnSetup();
	void gameplay();
	//currently makes a copy of the board, the speed could be improved, possibly at the cost of some encapsulation
	Board getBoard() { return m_board; }
	StoneColour getTurnColour();


};




#endif // !GAME_H