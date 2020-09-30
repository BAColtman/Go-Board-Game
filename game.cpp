#include "game.h"

//Initialises the empty starting board
void Game::initialiseGame()
{
	std::cout << "\t\tGO BOARD GAME\t\t\n\n";
}

//handles everything to do with each player's turn
void Game::playerTurn(Stones::StoneColour& turnColour)
{

	if ((turnColour == Stones::StoneColour::black) || (turnColour == Stones::StoneColour::white))
	{
		Output output;
		std::cout << output.printColour(static_cast<Stones::StoneColourCaps>(turnColour));
		std::cout << "'s turn\n";
		position_t position{ m_board.getMove() };
		if (position == constants::endGameFlag)
			m_isEndGame = true;
		else if (position == constants::passFlag)
			;
		else
			m_board.placeMove(turnColour, position);

		InputValidator  inputValidator;
		turnColour = inputValidator.switchColour(turnColour);
	}
	else
	{
		std::cout << "Error, unexpected turn";
	}

}

void Game::gameplay()
{
	Stones::StoneColour turn{ Stones::StoneColour::black };
	while (!m_isEndGame)
	{
		m_board.displayBoard();
		playerTurn(turn);
		m_board.getScoreTracker().currentScore();
	}
}