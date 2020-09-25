#include "board.h"

//Function to show the current status of the gaming board
void displayBoard(board_t &board, lettersArray_t& letters)
{
	//Render game board
	std::cout << "\nPLAYER 1 is Black [X]\t PLAYER 2 is White [O]\n\n";
	std::cout << "   ";
	for (auto letter : letters)
	{
		std::cout << letter << " ";
	}
	std::cout << "\n";
	//more formatting to get the board to line up
	if (boardSize < 10)
		std::cout << " ";
	std::cout << boardLabelReverse(0) << " ";
	for (int i{ 1 }; i <= pointNumber; i++)
	{
		//prints the current contents of each point
		std::cout << stoneColourToSymbol(board[i - zeroOffset].getColour()) << ' ';
		//makes a newline at the end of each row, and then prints the next label (apart from the last row)
		if ((i % boardSize == 0) && (i != pointNumber))
		{
			std::cout << "\n";
			//need an extra space for <10 to make the formatting nice
			if (boardLabelReverse(i / boardSize) < 10)
				std::cout << " ";
			std::cout << boardLabelReverse(i / boardSize) << " ";
		}
	}
	std::cout << "\n\n";
}

neighbour_t neighbourPositions(position_t position)
{
	//I shall use -1 to mean invalid neighbour e.g. the left-most stones do not have left neighbours
	neighbour_t neighbours{ noPosition,noPosition,noPosition,noPosition };
	//neighbours are listed in order of: up right down left

	//check it's not on the top side of the board
	if (position > (boardSize - zeroOffset))
	{
		neighbours.at(0) = position - boardSize;
	}

	//check it's not on the right side of the board
	if ((position + zeroOffset) % boardSize)
	{
		neighbours.at(1) = position + 1;
	}

	//check it's not on the bottom side of the board
	if (position < ((pointNumber - boardSize) - zeroOffset))
	{
		neighbours.at(2) = position + boardSize;
	}

	//check it's not on the left side of the board
	if (position % boardSize)
	{
		neighbours.at(3) = position - 1;
	}


	removeInvalidPositions(neighbours);

	//std::cout << "\n";
	//for(auto i : neighbours)
	//std::cout << i << " ";
	//std::cout << "\n";

	return neighbours;
}

//tells us that the input is invalid and asks for another move
position_t invalidMove(board_t& board)
{
	std::cout << "Invalid move, pick another\n\n";
	return getMove(board);
}

position_t moveInputToPosition(board_t& board, std::string move)
{
		int columnIndex{ letterToColumnNumber(move.at(0)) - zeroOffset };//this needs error checking
		int rowIndex{ boardLabelReverse(numberCharactersToInteger(move)) };


		//returns the coordinates of where the stone should be placed, with the row entry reversed appropriately
		position_t position{ boardIndex(rowIndex, columnIndex) };

		//check if input is within bounds, before trying to access it
		if ((position >= pointNumber) || (!isValidLetter(columnIndex)) || (!isValidLetter(rowIndex)) || (rowIndex == ERROR))
		{
			return invalidMove(board);
		}
		//check whether there's a stone already there
		else if (board[position].getColour() != StoneColour::empty)
		{
			return invalidMove(board);
		}
		else
			return position;
}

position_t getMove(board_t& board)
{
	std::cout << "Enter a move (letter first), or type \"pass\" to pass\n\n";
	std::string move;
	static int hasPass{ 0 };

	//this bit of code is when we want to specify several inputs at once for debugging purposes
	static int debugModeCountInput{ (!isDebug)*50 };// zero for isDebug = 1, 50 for isDebug = 0
	if (debugModeCountInput < static_cast<int>(defaultInput.size()))
	{
		move = defaultInput[debugModeCountInput];
		debugModeCountInput++;
	}
	else
		std::getline(std::cin, move);//This is what gets called if not in debug mode

	std::cout << "\n";


	if ((move == "pass") && (hasPass == 0))
	{
		hasPass = 1;
		return flag;
	}
	else if ((move == "pass") && (hasPass == 1))
	{
		return endGameFlag;
	}
	else
	{
		hasPass = 0;
		return moveInputToPosition(board, move);
	}
}


// merges group to return a sorted group with no duplicates
group_t mergeGroups(group_t group1, group_t group2)
{
	std::vector<groupElement_t> mergedGroup;
	mergedGroup.reserve(group1.size() + group2.size()); // preallocate memory
	mergedGroup.insert(mergedGroup.end(), group1.begin(), group1.end());
	mergedGroup.insert(mergedGroup.end(), group2.begin(), group2.end());

	sortVectorDescending(mergedGroup);
	//remove duplicates
	groupElement_t lastElement{ noPosition };
	for (auto &currentElement : mergedGroup)
	{
		if (currentElement == lastElement)
		{
			currentElement = noPosition;
		}
		else
		{
			lastElement = currentElement;
		}
	}
	removeInvalidPositions(mergedGroup);

	return mergedGroup;
}

group_t mergeLiberties(group_t lib1, group_t lib2, group_t stoneGroup)
{
	group_t libertyGroup{ mergeGroups(lib1, lib2) };

	for (auto position : stoneGroup)
	{
		for (auto &liberty : libertyGroup)
		{
			if (liberty == position)
			{
				liberty = noPosition;
			}
			//std::cerr << liberty << " " << position << "\n";
		}
	}

	removeInvalidPositions(libertyGroup);

	return libertyGroup;
}

//compare size of groups and return them with the biggest one first
std::array<Stones,2> biggerGroup(board_t board, Stones stoneWithGroupToAdd, Stones nodeStone)
{
	Stones newNode{ board[stoneWithGroupToAdd.getWhichGroup()] };
	Stones oldNode{ board[nodeStone.getWhichGroup()] };//This should be just nodeStone, but I've made it reversable just in case
	if (newNode.getGroup().size() > oldNode.getGroup().size())
	{
		return { newNode, oldNode };
	}
	else
		return { oldNode, newNode };
}

void addToGroup(board_t& board, position_t stoneToAddPosition, position_t groupMember)
{

	position_t groupNode{ board[groupMember].getWhichGroup() };
	//Stones nodeStone{ board[groupNode] };

	//if it is a single stone, point it to the group node and add it to the group
	if (board[stoneToAddPosition].getWhichGroup() == board[stoneToAddPosition].getPosition())
	{
		//Stones stoneToAdd = board[stoneToAddPosition];

		//set the group indicator of the new stone to the group indicator of the group it's joining
		board[stoneToAddPosition].setWhichGroup(groupNode);
		//add the stone to the group vector
		board[groupNode].setGroup(mergeGroups(board[stoneToAddPosition].getGroup(), board[groupNode].getGroup()));
		//calculate the new liberties of the group
		board[groupNode].setLiberties(mergeLiberties(board[stoneToAddPosition].getLiberties(), board[groupNode].getLiberties(), board[groupNode].getGroup()));
	}
	//if it has already been added to a group, but it's the same group as we are testing now, then we don't need to do anything
	//
	//if it has already been added to a group, and the two groups are distinct, we need to merge the two groups
	else if ((board[stoneToAddPosition].getWhichGroup() != board[stoneToAddPosition].getPosition()) && (board[stoneToAddPosition].getWhichGroup() != groupNode))
	{
		/*
		Stones stoneWithGroupToAdd = board[stoneToAddPosition];
		//find which is the larger group, and make the bigger one the node of the new group
		//this might be unnecessary, as I don't think it affects how long it takes to do this, but we'll keep it in for now
		Stones newNodeStone{ biggerGroup(board, board[stoneToAddPosition], board[groupNode])[0] };
		Stones oldNodeStone{ biggerGroup(board, board[stoneToAddPosition], board[groupNode])[1] };

		//point all the stones that used to point to the old node to the new node
		for (auto positionsOfGroupStones : oldNodeStone.getGroup())
			board[positionsOfGroupStones].setWhichGroup(newNodeStone.getPosition());

		//set the new group of the new node to the merged group
		newNodeStone.setGroup(mergeGroups(newNodeStone.getGroup(), oldNodeStone.getGroup()));
		//empty the group of the old node
		oldNodeStone.setGroup(emptyGroup);

		//set the new liberties of the new node to the merged liberties
		newNodeStone.setLiberties(mergeLiberties(newNodeStone.getLiberties(), oldNodeStone.getLiberties(), newNodeStone.getGroup()));
		//empty the liberties of the old node
		oldNodeStone.setLiberties(emptyGroup);
		*/



		position_t newNodeStonePosition{ (biggerGroup(board, board[stoneToAddPosition], board[groupNode])[0]).getPosition() };
		position_t oldNodeStonePosition{ (biggerGroup(board, board[stoneToAddPosition], board[groupNode])[1]).getPosition() };

		//point all the stones that used to point to the old node to the new node
		for (auto positionsOfGroupStones : board[oldNodeStonePosition].getGroup())
			board[positionsOfGroupStones].setWhichGroup(board[newNodeStonePosition].getPosition());

		//set the new group of the new node to the merged group
		board[newNodeStonePosition].setGroup(mergeGroups(board[newNodeStonePosition].getGroup(), board[oldNodeStonePosition].getGroup()));
		//empty the group of the old node
		board[oldNodeStonePosition].setGroup(emptyGroup);

		//set the new liberties of the new node to the merged liberties
		board[newNodeStonePosition].setLiberties(mergeLiberties(board[newNodeStonePosition].getLiberties(), board[oldNodeStonePosition].getLiberties(), board[newNodeStonePosition].getGroup()));
		//empty the liberties of the old node
		board[oldNodeStonePosition].setLiberties(emptyGroup);
	}
}

void hasBeenTaken(board_t& board, position_t position, StoneColour stoneColour)
{
	//check whether board[position] is surrounded by the opposite colour
	bool emptyLiberty{ false };
	Stones stoneAtRisk{ board[position] };

	//for a single stone - single stones now point to themselves, so this doesn't do what I want
	if (stoneAtRisk.getWhichGroup() == noPosition)
	{
		neighbour_t neighbours{ neighbourPositions(position) };
		for (auto neighbour : neighbours)
		{
			if (neighbour != noPosition)
			{
				if (board[neighbour].getColour() != switchColour(stoneColour))
				{
					emptyLiberty = true;
				}
			}
		}

		//if the stone is surrounded, remove it and give the other colour a point
		if (!emptyLiberty)
		{
			board[position].setEmptyStone();
			changeScore(switchColour(stoneColour), 1);
		}

	}
	else
	{
		Stones nodeStone = board[stoneAtRisk.getWhichGroup()];
		group_t groupPositions = nodeStone.getGroup();

		//std::cerr << "pass\n\n";

		for (auto libertyPosition : nodeStone.getLiberties())
		{
			//std::cerr << nodeStone.getLiberties() << "\n";
			//std::cerr << stoneColourToSymbol(board[libertyPosition].getColour()) << "\n";
			//std::cerr << stoneColourToSymbol(switchColour(stoneColour)) << "\n";
			if (board[libertyPosition].getColour() != switchColour(stoneColour))
			{
				emptyLiberty = true;
			}
		}

		//if the stones is surrounded, remove them and give the other colour a point for each stone removed
		if (!emptyLiberty)
		{
			changeScore(switchColour(stoneColour), groupPositions.size());
			for (auto stonePosition : groupPositions)
			{
				board[stonePosition].setEmptyStone();
			}
			
		}
	}
}

void placeMove(board_t& board, StoneColour turnColour, position_t position)
{
	//places the stone
	board[position].placeStone(position, turnColour);

	//finds stone neighbours
	neighbour_t neighbours{ neighbourPositions(position) };

	//checks if any of the neighbours have been taken, or if they're the same colour it adds it to the stone group
	for (int neighbour : neighbours)
	{
		if (neighbour != noPosition)//this is no longer necessary, as I remove the -1s in neighbourPositions
		{
			if (board[neighbour].getColour() == turnColour)
			{
				addToGroup(board, position, neighbour);
			}
			else if (board[neighbour].getColour() == switchColour(turnColour))
			{
				hasBeenTaken(board, neighbour, switchColour(turnColour));
			}
		}
	}

	//if the move is suicidal we can reset the position to empty and ask for another move
}