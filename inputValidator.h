#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include "setup.h"
#include <algorithm>
#include <sstream>
#include "stones.h"


class InputValidator
{
	/*
private:
	std::string m_stringInput;
	int m_intInput;
	char m_charInput;

public:

	InputValidator()
	{
		m_stringInput = "\0";
		m_intInput = constants::ERROR;
		m_charInput = '\0';
	}

	std::string getStringInput() { return m_stringInput; }
	void setStringInput(std::string stringInput) { m_stringInput = stringInput; }

	int getIntInput() { return m_intInput; }
	void setIntInput(int intInput) { m_intInput = intInput; }

	char getCharInput() { return m_charInput; }
	void setCharInput(char charInput) { m_charInput = charInput; }

	*/


public:

	//takes a row and column value and picks out the correct element of the 1D array
	position_t boardIndex(int row, int column);

	int letterToColumnNumber(char letter);

	int numberCharactersToInteger(char numberCharacter);

	int numberCharactersToInteger(std::string numberString);

	bool isValidDigit(char numberCharacter);

	bool isValidDigit(int digit);

	bool isValidIndex(int index);

	bool isValidLetter(char letter);

	bool isValidLetter(int letterInteger);



	int boardLabelReverse(int i);

	void removeInvalidPositions(neighbour_t& neighbours);

	void removeInvalidPositionsSorted(neighbour_t& neighbours);

	void sortVectorDescending(neighbour_t& neighbours);


	Stones::StoneColour switchColour(Stones::StoneColour turnColour);

};


#endif // !INPUTVALIDATOR_H