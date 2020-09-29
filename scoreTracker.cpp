#include "scoreTracker.h"



score_t ScoreTracker::getScore(Stones::StoneColour turnColour)
{
	if (turnColour == Stones::StoneColour::black)
	{
		return m_blackScore;
	}
	else if (turnColour == Stones::StoneColour::white)
	{
		return m_whiteScore;
	}
	else
		return constants::ERROR;
}

void ScoreTracker::changeScore(Stones::StoneColour turnColour, int change)
{

	if (turnColour == Stones::StoneColour::black)
	{
		m_blackScore += change;
	}
	else if (turnColour == Stones::StoneColour::white)
	{
		m_whiteScore += change;
	}
}

void ScoreTracker::currentScore()
{
	std::cout << "Stones captured are " << getScore(Stones::StoneColour::black) << " for Black, " << getScore(Stones::StoneColour::white) << " for White\n\n";
	std::cout << "White has komi of " << m_komi << "\n\n";
	std::cout << "Score: " << getScore(Stones::StoneColour::black) << " Black, " << (static_cast<double>(getScore(Stones::StoneColour::white)) + m_komi) << " White\n\n";
}

void ScoreTracker::finalScore()
{
	std::cout << "\n\n\n\n\n\n\nEnd of the game\n";
	std::cout << "\nPlease input black's points from territory\n\n";
	std::string scoreChange{};
	std::getline(std::cin, scoreChange);
	changeScore(Stones::StoneColour::black, stoi(scoreChange));
	std::cout << "\nPlease input white's points from territory\n\n";
	std::getline(std::cin, scoreChange);
	changeScore(Stones::StoneColour::white, stoi(scoreChange));


	std::cout << "\n\n\t\t\tFINAL SCORE\t\t\t\n\n";
	currentScore();
}