#ifndef OUTPUT_H
#define OUTPUT_H


#include "setup.h"
#include "stones.h"



class Output
{
private:


public:

	//StoneColour symbolToColour(char symbol);



	static char stoneColourToSymbol(StoneColour stone);



	static std::string printColour(StoneColour stone);

	static std::string printColourCaps(StoneColour stone);

};



#endif // !OUTPUT_H