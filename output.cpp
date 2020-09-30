#include "output.h"


//Turns empty, black or white into the corresponding symbol for display on the board
char Output::stoneColourToSymbol(StoneColour stone)
{
	return constants::stoneColourSymbol[static_cast<int>(stone)];
}



/*
StoneColour symbolToColour(char symbol)
{
	StoneColour colour{};
	if (symbol == '-')
	{
		colour = StoneColour::empty;
	}
	else if (symbol == 'X')
	{
		colour = StoneColour::black;
	}
	else if (symbol == 'O')
	{
		colour = StoneColour::white;
	}
	else
		std::cout << "error\n";

	return colour;
}
*/

std::string Output::printColour(StoneColour stone)
{
	if (stone == StoneColour::black)
	{
		return "black";
	}
	else if (stone == StoneColour::white)
	{
		return "white";
	}
	else if (stone == StoneColour::empty)
	{
		return "empty";
	}
	else
		return "error";
}

std::string Output::printColourCaps(StoneColour stone)
{
	if (stone == StoneColour::black)
	{
		return "Black";
	}
	else if (stone == StoneColour::white)
	{
		return "White";
	}
	else if (stone == StoneColour::empty)
	{
		return "Empty";
	}
	else
		return "error";
}