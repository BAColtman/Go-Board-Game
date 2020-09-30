#include "game.h"

//Initialises the empty starting board
void Game::initialiseGame()
{
	std::cout << "\t\tGO BOARD GAME\t\t\n\n";
	printTurnSetup();
}


void Game::printTurnSetup()
{
	m_board.displayBoard();
	std::cout << Output::printColourCaps(getTurnColour());
	std::cout << "'s turn\n";
}

void Game::gameplay()
{
	bool isValidMove{true};

	while (!m_isEndGame)
	{

		

		position_t position{ m_board.getMove() };
		if (position == constants::passFlag)
		{
			if (m_hasPassed)
			{
				//if there's a pass and the previous player passed, trigger the end game
				m_isEndGame = true;
			}
			else
			{
				m_hasPassed = true;
			}
		}
		else
		{
			//places the move and checks whether it's a suicide move or not, outputs into isValidMove
			isValidMove = m_board.placeMove(getTurnColour(), position);
			if (isValidMove)
				m_hasPassed = false;
		}

		//if the last move was valid, print the corresponding text and switch turn, otherwise go round the loop again
		if (isValidMove)
		{
			//switch turn
			m_whichTurn = !m_whichTurn;

			m_board.getScoreTracker().currentScore();
			printTurnSetup();
		}
	}
}

StoneColour Game::getTurnColour()
{
	//m_whichTurn == true means it's white's turn
	if (m_whichTurn)
	{
		return StoneColour::white;
	}
	//m_whichTurn == false means it's black's turn
	else
	{
		return StoneColour::black;
	}
}