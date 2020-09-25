#include "setup.h"
#include "board.h"

//Initialises the empty starting board
board_t initialiseGame()
{
	std::cout << "\t\tGO BOARD GAME\t\t\n\n";
	//std::cout << "\t     Black goes first\t\t\n\n";

	board_t board;

	for (position_t i{ 0 }; i < pointNumber; i++)
	{
		board[i].setPosition(i);
		board[i].setLiberties(neighbourPositions(i));
	}

	return board;
}

std::array<char, boardSize> initialiseLetterArray()
{
	std::array<char, boardSize> letterArray;
	int offset{ asciiOffset + zeroOffset };
	for (int i{ 0 }; i < boardSize; i++)
	{
		letterArray.at(i) = static_cast<char>(i + offset);
		//skips I, as on a traditional Go board
		if (i == 7)
			offset++;
	}
	//extern const std::array<char, boardSize> letters{ letterArray };
	return letterArray;//find a way to make this external, and perhaps global
}