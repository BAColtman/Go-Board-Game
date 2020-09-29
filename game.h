#ifndef GAME_H
#define GAME_H

#include "setup.h"
#include "stones.h"
#include "output.h"
#include "scoreTracker.h"
#include "board.h"
#include "inputValidator.h"

class Game
{
private:
	Board m_board{};
	Stones::StoneColour m_whichTurn;
	bool m_isEndGame;

public:
	Game()
	{
		m_whichTurn = Stones::StoneColour::black;
		m_isEndGame = false;
	};

	void initialiseGame();
	void playerTurn(Stones::StoneColour& turnColour);
	void gameplay();
	//currently makes a copy of the board, the speed could be improved, possibly at the cost of some encapsulation
	Board getBoard() { return m_board; }


};




#endif // !GAME_H