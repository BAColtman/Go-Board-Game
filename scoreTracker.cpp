#include "scoreTracker.h"



score_t ScoreTracker::getScore(StoneColour turnColour)
{
	if (turnColour == StoneColour::black)
	{
		return m_blackScore;
	}
	else if (turnColour == StoneColour::white)
	{
		return m_whiteScore;
	}
	else
		return constants::ERROR;
}

void ScoreTracker::changeScore(StoneColour turnColour, int change)
{

	if (turnColour == StoneColour::black)
	{
		m_blackScore += change;
	}
	else if (turnColour == StoneColour::white)
	{
		m_whiteScore += change;
	}
}

void ScoreTracker::currentScore()
{
	std::cout << "Stones captured are " << getScore(StoneColour::black) << " for Black, " << getScore(StoneColour::white) << " for White\n\n";
	std::cout << "White has komi of " << m_komi << "\n\n";
	std::cout << "Score: " << getScore(StoneColour::black) << " Black, " << (static_cast<double>(getScore(StoneColour::white)) + m_komi) << " White\n\n";
}

void ScoreTracker::finalScore()
{
	std::cout << "\n\n\n\n\n\n\nEnd of the game\n";
	std::cout << "\nPlease input black's points from territory\n\n";
	std::string scoreChange{};
	std::getline(std::cin, scoreChange);
	changeScore(StoneColour::black, stoi(scoreChange));
	std::cout << "\nPlease input white's points from territory\n\n";
	std::getline(std::cin, scoreChange);
	changeScore(StoneColour::white, stoi(scoreChange));


	std::cout << "\n\n\t\t\tFINAL SCORE\t\t\t\n\n";
	currentScore();
}