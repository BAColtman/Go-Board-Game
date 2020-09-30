#include "input.h"

//takes a row and column value and picks out the correct element of the 1D array
int Input::boardIndex(int row, int column)
{
	return (row * constants::boardSize) + column;
}

//Converts a letter input from a move to a number on the grid
int Input::letterToColumnNumber(char letter)
{
	//A (or a) should convert to 0 and so on, toupper implicitly converts to int
	int letterCast{ toupper(letter) - constants::asciiOffset - constants::zeroOffset };
	
	//checks if it's a valid column index (including if it's I, which doesn't exist on the board)
	if ((letterCast < 0)||(letterCast > 24)||(letterCast == 8))
	{
		throw "Invalid column index";
	}

	//checks if letter was between 'H' and 'Z', as traditional Go Boards do not have a letter 'I' on them
	//8 is the corresponding value for 'I'
	if (letterCast > 8)
	{
		//because we've missed 'I' we need to decrement by 1
		letterCast--;
	}
	
	//If it's a valid letter but the board is too small for that column to exist:
	if (letterCast >= constants::boardSize)
	{
	throw "That column is not on the board";
	}

	return letterCast;
}

int Input::inputToRowNumber(std::string numberString)
{
	//removes the first character (which should standardly be a letter)
	if (!isValidDigit(numberString.at(0)))
		numberString.erase(0, 1);

	int rowCandidate{ std::stoi(numberString) };
	if (isValidIndex(rowCandidate))
		return rowCandidate;
	else
		throw "That row is not on the board";
}








void Input::sortVectorDescending(neighbour_t& neighbours)
{
	sort(neighbours.begin(), neighbours.end(), std::greater{});
}

//removes noPositions from a sorted vector
void Input::removeInvalidPositionsSorted(neighbour_t& neighbours)
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
}

//sorts unsorted vector and removes noPositions
void Input::removeInvalidPositions(neighbour_t& neighbours)
{
	sortVectorDescending(neighbours);
	removeInvalidPositionsSorted(neighbours);

}

//traditional Go boards index upwards
int Input::boardLabelReverse(int i)
{
	return constants::boardSize - i;
}





//Switches white to black and vice versa
StoneColour Input::switchColour(StoneColour turnColour)
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



int Input::numberCharacterToInteger(char numberCharacter)
{
	return (static_cast<int>(numberCharacter) - constants::asciiOffsetNum);
}

bool Input::isValidDigit(char numberCharacter)
{
	int digit{ (numberCharacterToInteger(numberCharacter)) };
	//if function argument is not a digit, return false
	if ((digit < 0) || (digit > 9))
		return false;
	else
		return true;
}

bool Input::isValidIndex(int index)
{
	//current implementation converts letters to between 0 and 24, hence the limit on indices
	if ((index < 0) || (index > std::min(24, constants::boardSize)))
		return false;
	else
		return true;
}

bool Input::isValidLetter(char letter)
{
	int letterInteger{ letterToColumnNumber(letter) };
	//if letterInteger is not a valid value, return false (A to Z without I converts to 0 to 24), but we don't want it bigger than the board
	if ((letterInteger < 0) || (letterInteger > std::min(24, constants::boardSize)))
		return false;
	else
		return true;
}