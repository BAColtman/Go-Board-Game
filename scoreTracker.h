#ifndef SCORETRACKER_H
#define SCORETRACKER_H

#include "setup.h"
#include "output.h"
//#include "board.h"


using score_t = int;

class ScoreTracker
{
private:
	score_t m_blackScore{ 0 };//change these to appear only in the constructor
	score_t m_whiteScore{ 0 };

	const double m_komi{ 6.5 };
	//double m_komi{ 6.5 };

public:
	ScoreTracker()
	{
		m_blackScore = 0;
		m_whiteScore = 0;
		//m_komi = 6.5;
	};



	score_t getScore(Stones::StoneColour turnColour);

	void changeScore(Stones::StoneColour turnColour, int change);

	void currentScore();

	void finalScore();

};





#endif // !SCORETRACKER_H