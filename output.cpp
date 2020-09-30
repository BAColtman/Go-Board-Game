#include "output.h"


//Turns empty, black or white into the corresponding symbol for display on the board
char Output::stoneColourToSymbol(Stones::StoneColour stone)
{
	return constants::stoneColourSymbol[static_cast<int>(stone)];
}



/*
Stones::StoneColour symbolToColour(char symbol)
{
	Stones::StoneColour colour{};
	if (symbol == '-')
	{
		colour = Stones::StoneColour::empty;
	}
	else if (symbol == 'X')
	{
		colour = Stones::StoneColour::black;
	}
	else if (symbol == 'O')
	{
		colour = Stones::StoneColour::white;
	}
	else
		std::cout << "error\n";

	return colour;
}
*/

std::string Output::printColour(Stones::StoneColour stone)
{
	if (stone == Stones::StoneColour::black)
	{
		return "black";
	}
	else if (stone == Stones::StoneColour::white)
	{
		return "white";
	}
	else if (stone == Stones::StoneColour::empty)
	{
		return "empty";
	}
	else
		return "error";
}

std::string Output::printColour(Stones::StoneColourCaps stone)
{
	if (stone == Stones::StoneColourCaps::Black)
	{
		return "Black";
	}
	else if (stone == Stones::StoneColourCaps::White)
	{
		return "White";
	}
	else if (stone == Stones::StoneColourCaps::Empty)
	{
		return "Empty";
	}
	else
		return "error";
}