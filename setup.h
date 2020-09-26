#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <array>
#include <vector>
#include <string>


//put all constants into a constant:: namespace

namespace constants
{

	//defines how big the board is and how many spaces there are, eventually could make this optional to the user
	constexpr int boardSize{ 9 };
	constexpr int pointNumber{ constants::boardSize * constants::boardSize };
	//used when needing to start an array from 1, or similar circumstances
	constexpr int zeroOffset{ 1 };
	//offset to turn ascii code from letter input into corresponding number on the board, e.g. A->1
	constexpr int asciiOffset{ 64 };
	//a similar concept for numbers
	constexpr int asciiOffsetNum{ 48 };
	constexpr int ERROR{ -2 };

	//use for anything where I need to flag up a certain thing has happened
	constexpr int flag{ -3 };
	//use for flagging that a player (but not both) have passed
	constexpr int passFlag{ -3 };

	//use to flag that both players have passed and the game has ended
	constexpr int endGameFlag{ -4 };



	//tools for debugging, 0 for no debug, 1 for debug mode
	constexpr int isDebug{ 0 };

	//std::vector<std::string> defaultInput{ {"A9", "A8", "B9", "B8", "F2", "C9"} };
	const std::array<std::string, 8> defaultInput{ {"F7", "A8", "F8", "A6", "G7", "C9", "G8", "G6"} };

}



// so that I can easily see which variables refer to position indices on the board
using position_t = int;


// this is so that I can easily change whether I store positions or objects for each group, if I decide the other one is better
using groupElement_t = position_t;
// group_t is shorthand for a vector of groupElement_t's
using group_t = std::vector<groupElement_t>;

using neighbour_t = group_t;

//type for array of letters on the top of the board
using lettersArray_t = std::array<char, constants::boardSize>;

// use an alias for the board type, can replace with a class later if I want
class Stones;
using board_t = std::array<Stones, constants::pointNumber>;

namespace constants
{

	// setting up empty positions and empty groups
	const position_t noPosition{ -1 };
	const group_t emptyGroup{ {noPosition} };

	// - represents an empty space, X represents a Black stone and O represents a White stone
	const std::array<char, 3> stoneColourSymbol{ { '-','X','O' } };

}

//enumerator to decide what, if anything, is on a particular space on the board
enum class StoneColour
{
	empty,
	black,
	white
};


enum class StoneColourCaps
{
	Empty,
	Black,
	White
};



void initialiseGame(board_t& board);

std::array<char, constants::boardSize> initialiseLetterArray();




#endif // !SETUP_H