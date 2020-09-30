//Go Board Game in C++

#include "setup.h"
#include "stones.h"
#include "output.h"
#include "scoreTracker.h"
#include "board.h"
#include "game.h"



/* Still to do:
 * use const references if the function doesn't need to modify the input
 * implement depth search scoring
 * variable board size
 * indexing by points -> indexing by rows & columns (9 row arrays of 9)
 * evaluate the board when you place a stone rather than keeping track of all the groups stuff - do this last
 *
 * playerTurn should return an enum of valid move, invalid move and pass
 * pass should be a bool of did last person pass, in game object
 * 
 *
 * make the score object part of game maybe? Probably fine
 * 
 * invalid move: print invalid move and just don't switch turn - can't do this until I just evaluate the board state, as suicide stones currently get dealt with after I deal with the passes
 *
 */





//Initialise the position generator to 0 for the board to iterate through it when it calls the stones constructor
position_t Stones::s_positionGenerator = 0;


int main()
{
	Game game{};
	game.initialiseGame();
	game.gameplay();

	game.getBoard().getScoreTracker().finalScore();
	//Display board end state
	game.getBoard().displayBoard();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
