#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <array>
#include <vector>
#include <string>


// change [] to .at()

//put all constants into a constant:: namespace



//defines how big the board is and how many spaces there are, eventually could make this optional to the user
constexpr int boardSize{ 5 };
constexpr int pointNumber{ boardSize * boardSize };
//used when needing to start an array from 1, or similar circumstances
constexpr int zeroOffset{ 1 };
//offset to turn ascii code from letter input into corresponding number on the board, e.g. A->1
constexpr int asciiOffset{ 64 };
//a similar concept for numbers
constexpr int asciiOffsetNum{ 48 };
constexpr int ERROR{ -2 };

//use for anything where I need to flag up a certain thing has happened
constexpr int flag{ -3 };

//use to flag that both players have passed and the game has ended
constexpr int endGameFlag{ -4 };



//tools for debugging
constexpr int isDebug{ 0 };

//std::vector<std::string> defaultInput{ {"A9", "A8", "B9", "B8", "F2", "C9"} };
const std::array<std::string, 8> defaultInput{ {"F7", "A8", "F8", "A6", "G7", "C9", "G8", "G6"} };





// so that I can easily see which variables refer to position indices on the board
using position_t = int;
const position_t noPosition{ -1 };

// this is so that I can easily change whether I store positions or objects for each group, if I decide the other one is better
using groupElement_t = position_t;
// group_t is shorthand for a vector of groupElement_t's
using group_t = std::vector<groupElement_t>;
const group_t emptyGroup{ {noPosition} };

using neighbour_t = group_t;

//type for array of letters on the top of the board
using lettersArray_t = std::array<char, boardSize>;

// - represents an empty space, X represents a Black stone and O represents a White stone
const std::array<char, 3> stoneColourSymbol{ { '-','X','O' } };//do I need the extra braces?

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



#endif // !SETUP_H