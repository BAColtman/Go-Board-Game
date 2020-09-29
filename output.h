#ifndef OUTPUT_H
#define OUTPUT_H


#include "setup.h"
#include "stones.h"



class Output
{
private:


public:

	//Stones::StoneColour symbolToColour(char symbol);



	char stoneColourToSymbol(Stones::StoneColour stone);



	std::string printColour(Stones::StoneColour stone);

	std::string printColour(Stones::StoneColourCaps stone);

};



#endif // !OUTPUT_H