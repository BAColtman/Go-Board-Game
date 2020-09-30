#ifndef INPUT_H
#define INPUT_H

#include "setup.h"
#include <algorithm>
#include <sstream>
#include "stones.h"


class Input
{
	/*
private:
	std::string m_stringInput;
	int m_intInput;
	char m_charInput;

public:

	Input()
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
	static position_t boardIndex(int row, int column);

	static int letterToColumnNumber(char letter);

	static int numberCharacterToInteger(char numberCharacter);

	//static int numberCharacterToInteger(std::string numberString);

	///*
	static bool isValidDigit(char numberCharacter);

	static bool isValidIndex(int index);

	static bool isValidLetter(char letter);
	//*/


	static int boardLabelReverse(int i);

	static void removeInvalidPositions(neighbour_t& neighbours);

	static void removeInvalidPositionsSorted(neighbour_t& neighbours);

	static void sortVectorDescending(neighbour_t& neighbours);


	static StoneColour switchColour(StoneColour turnColour);

	static int inputToRowNumber(std::string numberString);

};


#endif // !INPUT_H