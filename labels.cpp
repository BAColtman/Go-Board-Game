#include "labels.h"


//Turns empty, black or white into the corresponding symbol for display on the board
char stoneColourToSymbol(StoneColour stone)
{
	return constants::stoneColourSymbol[static_cast<int>(stone)];
}

//traditional Go boards index upwards
int boardLabelReverse(int i)
{
		return constants::boardSize - i;
}

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

//Switches white to black and vice versa
StoneColour switchColour(StoneColour turnColour)
{
	if (turnColour == StoneColour::black)
	{
		turnColour = StoneColour::white;
	}
	else if (turnColour == StoneColour::white)
	{
		turnColour = StoneColour::black;
	}
	else
		std::cout << "Invalid request\n";

	return turnColour;
}

//prints colour
std::string printColour(StoneColour stone)
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

//prints Colour
std::string printColour(StoneColourCaps stone)
{
	if (stone == StoneColourCaps::Black)
	{
		return "Black";
	}
	else if (stone == StoneColourCaps::White)
	{
		return "White";
	}
	else if (stone == StoneColourCaps::Empty)
	{
		return "Empty";
	}
	else
		return "error";
}

void sortVectorDescending(neighbour_t& neighbours)
{
	sort(neighbours.begin(), neighbours.end(), std::greater<int>());//this should become qsort
}


void removeInvalidPositionsSorted(neighbour_t& neighbours)//removes -1s from a sorted vector
{
	position_t isMissingNeighbour{ 0 };
	position_t missingPosition{};
	for (int i{ 0 }; i < static_cast<int>(neighbours.size()); i++)
	{
		if ((neighbours[i] == constants::noPosition) && (!isMissingNeighbour))
		{
			isMissingNeighbour = 1;
			missingPosition = i;

		}
	}

	if (isMissingNeighbour)
	{
		neighbours.resize(static_cast<unsigned int>(missingPosition));
	}


	//return neighbours;
}

void removeInvalidPositions(neighbour_t& neighbours)//sorts unsorted vector and removes -1s
{
	sortVectorDescending(neighbours);
	removeInvalidPositionsSorted(neighbours);

	//return neighbours;
}

//takes a row and column value and picks out the correct element of the 1D array
int boardIndex(int row, int column)
{
	return (row * constants::boardSize) + column;
}

//Converts a letter input from a move to a number on the grid
int letterToColumnNumber(char letter)
{
	//A should convert to 1 and so on
	int letterCast{ static_cast<int>(letter) - constants::asciiOffset };
	//checks if letter was between 'A' and 'H', as traditional Go Boards do not have a letter 'I' on them
	if ((letterCast > constants::boardSize + 1) || (letterCast < 1))
	{
		//std::cout << "Your letter converted to the number " << letterCast << "\n";
		//std::cout << "Your column is out of range\n\n";
		return constants::ERROR;
	}
	//9 is the corresponding value for 'I'
	else if (letterCast < 9)
	{
		return letterCast;
	}
	else
		//because we've missed 'I' we need to decrement by 1
		return (letterCast - 1);
}

int numberCharactersToInteger(char numberCharacter)
{
	return (static_cast<int>(numberCharacter) - constants::asciiOffsetNum);
}

int numberCharactersToInteger(std::string numberString)//my own implementation of stoi(), in case I don't want to use stoi()
{
	std::vector<int> numberArray;
	int numberOfDigits{ static_cast<int>(numberString.length()) };

	numberArray.reserve(numberOfDigits);
	for (auto chars : numberString)
		numberArray.insert(numberArray.end(), numberCharactersToInteger(chars));

	int number{ 0 };
	int i{ 0 };
	//if the first number was not a digit i.e. if it came from a letter, skip it
	if (!isValidDigit(numberArray.at(0)))
		i++;

	for (i; i < numberOfDigits; i++)
	{
		if (!isValidDigit(numberArray.at(i)))
		{
			return constants::ERROR;
		}
		number += numberArray.at(i) * (static_cast<int>(pow(10, (numberOfDigits - i) - constants::zeroOffset)));
	}

	return number;
}

bool isValidDigit(char numberCharacter)
{
	int digit{ (numberCharactersToInteger(numberCharacter)) };
	//if digit is not a digit, throw an error
	if ((digit < 0) || (digit > 9))
		return false;
	else
		return true;
}

bool isValidDigit(int digit)
{
	//if digit is not a digit, throw an error
	if ((digit < 0) || (digit > 9))
		return false;
	else
		return true;
}

bool isValidIndex(int index)
{
	//current implementation converts letters to between 0 and 24, hence the limit on indices
	if ((index < 0) || (index > std::min(24, constants::boardSize)))
		return false;
	else
		return true;
}

bool isValidLetter(char letter)
{
	int letterInteger{ (letterToColumnNumber(letter) - constants::zeroOffset) };
	//if letterInteger is not a valid value, throw an error (A to Z without I converts to 0 to 24), but we don't want it bigger than the board
	if ((letterInteger < 0) || (letterInteger > std::min(24, constants::boardSize)))
		return false;
	else
		return true;
}

bool isValidLetter(int letterInteger)
{
	//if letterInteger is not a valid value, throw an error (A to Z without I converts to 0 to 24), but we don't want it bigger than the board
	return isValidIndex(letterInteger);
}