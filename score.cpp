#include "score.h"

score_t blackScore{ 0 };
score_t whiteScore{ 0 };

const double komi{ 6.5 };



score_t getScore(StoneColour turnColour)
{
	if (turnColour == StoneColour::black)
	{
		return blackScore;
	}
	else if (turnColour == StoneColour::white)
	{
		return whiteScore;
	}
	else
		return ERROR;
}

void changeScore(StoneColour turnColour, int change)
{

	if (turnColour == StoneColour::black)
	{
		blackScore += change;
	}
	else if (turnColour == StoneColour::white)
	{
		whiteScore += change;
	}
}

void score()
{
	std::cout << "Stones captured are " << getScore(StoneColour::black) << " for Black, " << getScore(StoneColour::white) << " for White\n\n";
	std::cout << "White has komi of " << komi << "\n\n";
	std::cout << "Score: " << getScore(StoneColour::black) << " Black, " << (static_cast<double>(getScore(StoneColour::white)) + komi) << " White\n\n";
}

void finalScore(board_t &board, lettersArray_t letters)
{
	std::cout << "\n\n\n\n\n\n\nEnd of the game\n";
	std::cout << "\nPlease input black's points from territory\n\n";
	std::string scoreChange{};
	std::getline(std::cin, scoreChange);
	//changeScore(StoneColour::black, numberCharactersToInteger(scoreChange));
	changeScore(StoneColour::black, stoi(scoreChange));
	std::cout << "\nPlease input white's points from territory\n\n";
	std::getline(std::cin, scoreChange);
	//changeScore(StoneColour::white, numberCharactersToInteger(scoreChange));
	changeScore(StoneColour::white, stoi(scoreChange));


	std::cout << "\n\n\t\t\tFINAL SCORE\t\t\t\n\n";
	score();

	displayBoard(board, letters);
}