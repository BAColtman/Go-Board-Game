//Go Board Game in C++

#include "setup.h"
#include "stones.h"
#include "labels.h"
#include "board.h"
#include "score.h"

int gameover(int isEndGame);

//handles everything to do with each player's turn
void playerTurn(board_t &board, StoneColour &turnColour)
{

	if ((turnColour == StoneColour::black) || (turnColour == StoneColour::white))
	{
		std::cout << printColour(static_cast<StoneColourCaps>(turnColour));
		std::cout << "'s turn\n";
		position_t position{ getMove(board) };
		if (position == constants::endGameFlag)
			gameover(constants::endGameFlag);
		else if (position == constants::passFlag)
			;
		else
			placeMove(board, turnColour, position);

		turnColour = switchColour(turnColour);
	}
	else
	{
		std::cout << "Error, unexpected turn";
	}
	
}

int gameover(int isEndGame)
{
	//once isEndGame is !0, it will end the game
	static int endGame{ 0 };
	endGame += isEndGame;
	return endGame;
}

void gameplay(board_t &board, std::array<char, constants::boardSize>& letters)
{
	StoneColour turn{ StoneColour::black };
	while (!gameover(0))
	{
		displayBoard(board, letters);
		playerTurn(board, turn);
		score();
	}
}

int main()
{
	board_t board{};
	initialiseGame(board);
	std::array<char, constants::boardSize> letters{ initialiseLetterArray() };
	gameplay(board, letters);

	finalScore(board, letters);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
