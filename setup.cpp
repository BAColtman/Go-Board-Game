#include "setup.h"
#include "board.h"

//Initialises the empty starting board
void initialiseGame(board_t &board)
{
	std::cout << "\t\tGO BOARD GAME\t\t\n\n";
	//std::cout << "\t     Black goes first\t\t\n\n";

	initialiseBoard(board);
}

std::array<char, constants::boardSize> initialiseLetterArray()
{
	std::array<char, constants::boardSize> letterArray;
	int offset{ constants::asciiOffset + constants::zeroOffset };
	for (int i{ 0 }; i < constants::boardSize; i++)
	{
		letterArray.at(i) = static_cast<char>(i + offset);
		//skips I, as on a traditional Go board
		if (i == 7)
			offset++;
	}
	//extern const std::array<char, constants::boardSize> letters{ letterArray };
	return letterArray;//find a way to make this external, and perhaps global?
}