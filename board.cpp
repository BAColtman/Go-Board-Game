#include "board.h"


//Function to show the current status of the gaming board
void Board::displayBoard()
{
	//Render game board
	std::cout << "\nPLAYER 1 is Black [X]\t PLAYER 2 is White [O]\n\n";
	std::cout << "   ";
	for (auto letter : m_letters)
	{
		std::cout << letter << " ";
	}
	std::cout << "\n";
	//more formatting to get the board to line up
	if (constants::boardSize < 10)
		std::cout << " ";
	std::cout << boardLabelReverse(0) << " ";
	for (int i{ 1 }; i <= constants::pointNumber; i++)
	{
		//prints the current contents of each point
		std::cout << stoneColourToSymbol(m_board.at(i - constants::zeroOffset).getColour()) << ' ';
		//makes a newline at the end of each row, and then prints the next label (apart from the last row)
		if ((i % constants::boardSize == 0) && (i != constants::pointNumber))
		{
			std::cout << "\n";
			//need an extra space for <10 to make the formatting nice
			if (boardLabelReverse(i / constants::boardSize) < 10)
				std::cout << " ";
			std::cout << boardLabelReverse(i / constants::boardSize) << " ";
		}
	}
	std::cout << "\n\n";
}

//tells us that the input is invalid and asks for another move
position_t Board::askForAnotherMove()
{
	std::cout << "Invalid move, pick another\n\n";
	return getMove();
}

position_t Board::moveInputToPosition(std::string move)
{
		int columnIndex{ letterToColumnNumber(move.at(0)) - constants::zeroOffset };
		int rowIndex{ boardLabelReverse(numberCharactersToInteger(move)) };


		//returns the coordinates of where the stone should be placed, with the row entry reversed appropriately
		position_t position{ boardIndex(rowIndex, columnIndex) };

		//check if input is within bounds, before trying to access it
		if ((position >= constants::pointNumber) || (!isValidLetter(columnIndex)) || (!isValidLetter(rowIndex)) || (rowIndex == constants::ERROR))
		{
			return askForAnotherMove();
		}
		//check whether there's a stone already there
		else if (m_board.at(position).getColour() != StoneColour::empty)
		{
			return askForAnotherMove();
		}
		else
			return position;
}

position_t Board::getMove()
{
	std::cout << "Enter a move (letter first), or type \"pass\" to pass\n\n";
	static int hasPass{ 0 };
	std::string move;

	//this bit of code is when we want to specify several inputs at once for debugging purposes
	static int debugModeCountInput{ (!constants::isDebug)*50 };// zero for isDebug = 1, 50 for isDebug = 0
	if (debugModeCountInput < static_cast<int>(constants::defaultInput.size()))
	{
		move = constants::defaultInput[debugModeCountInput];
		debugModeCountInput++;
	}
	else
		//This is what gets called if not in debug mode
		std::getline(std::cin, move);

	std::cout << "\n";


	if ((move == "pass") && (hasPass == 0))
	{
		hasPass = 1;
		return constants::flag;
	}
	else if ((move == "pass") && (hasPass == 1))
	{
		return constants::endGameFlag;
	}
	else
	{
		hasPass = 0;
		return moveInputToPosition(move);
	}
}


// merges group to return a sorted group with no duplicates
group_t Board::mergeGroups(group_t group1, group_t group2)
{
	std::vector<groupElement_t> mergedGroup;
	//preallocate memory
	mergedGroup.reserve(group1.size() + group2.size());
	mergedGroup.insert(mergedGroup.end(), group1.begin(), group1.end());
	mergedGroup.insert(mergedGroup.end(), group2.begin(), group2.end());

	sortVectorDescending(mergedGroup);
	//remove duplicates
	groupElement_t lastElement{ constants::noPosition };
	for (auto &currentElement : mergedGroup)
	{
		if (currentElement == lastElement)
		{
			currentElement = constants::noPosition;
		}
		else
		{
			lastElement = currentElement;
		}
	}
	removeInvalidPositions(mergedGroup);

	return mergedGroup;
}

group_t Board::mergeLiberties(group_t lib1, group_t lib2, group_t stoneGroup)
{
	group_t libertyGroup{ mergeGroups(lib1, lib2) };

	for (auto position : stoneGroup)
	{
		for (auto &liberty : libertyGroup)
		{
			if (liberty == position)
			{
				liberty = constants::noPosition;
			}
		}
	}

	removeInvalidPositions(libertyGroup);

	return libertyGroup;
}

//compare size of groups and return them with the biggest one first
std::array<Stones,2> Board::biggerGroup(Stones stoneWithGroupToAdd, Stones nodeStone)
{
	Stones newNode{ m_board.at(stoneWithGroupToAdd.getWhichGroup()) };
	//This should be just nodeStone, but I've made it reversable just in case
	Stones oldNode{ m_board.at(nodeStone.getWhichGroup()) };
	if (newNode.getGroup().size() > oldNode.getGroup().size())
	{
		return { newNode, oldNode };
	}
	else
		return { oldNode, newNode };
}

void Board::addToGroup(position_t stoneToAddPosition, position_t groupMember)
{

	position_t nodeStonePosition{ m_board.at(groupMember).getWhichGroup() };
	Stones& nodeStone{ m_board.at(nodeStonePosition) };
	Stones& stoneToAdd{ m_board.at(stoneToAddPosition) };

	//if it is a single stone, point it to the group node and add it to the group
	if (stoneToAdd.getWhichGroup() == stoneToAddPosition)
	{
		//set the group indicator of the new stone to the group indicator of the group it's joining
		stoneToAdd.setWhichGroup(nodeStonePosition);
		//add the stone to the group vector
		nodeStone.setGroup(mergeGroups(stoneToAdd.getGroup(), nodeStone.getGroup()));
		//calculate the new liberties of the group
		nodeStone.setLiberties(mergeLiberties(stoneToAdd.getLiberties(), nodeStone.getLiberties(), nodeStone.getGroup()));
	}
	//if it has already been added to a group, but it's the same group as we are testing now, then we don't need to do anything
	//
	//if it has already been added to a group, and the two groups are distinct, we need to merge the two groups
	else if ((stoneToAdd.getWhichGroup() != stoneToAddPosition) && (stoneToAdd.getWhichGroup() != nodeStonePosition))
	{
		
		Stones &stoneWithGroupToAdd{ stoneToAdd };
		//find which is the larger group, and make the bigger one the node of the new group
		//this might be unnecessary, as I don't think it affects how long it takes to do this, but we'll keep it in for now
		Stones &newNodeStone{ biggerGroup(stoneWithGroupToAdd, nodeStone)[0] };
		Stones &oldNodeStone{ biggerGroup(stoneWithGroupToAdd, nodeStone)[1] };

		//point all the stones that used to point to the old node to the new node
		for (auto positionsOfGroupStones : oldNodeStone.getGroup())
			m_board.at(positionsOfGroupStones).setWhichGroup(newNodeStone.getPosition());

		//set the new group of the new node to the merged group
		newNodeStone.setGroup(mergeGroups(newNodeStone.getGroup(), oldNodeStone.getGroup()));
		//empty the group of the old node
		oldNodeStone.setGroup(constants::emptyGroup);

		//set the new liberties of the new node to the merged liberties
		newNodeStone.setLiberties(mergeLiberties(newNodeStone.getLiberties(), oldNodeStone.getLiberties(), newNodeStone.getGroup()));
		//empty the liberties of the old node
		oldNodeStone.setLiberties(constants::emptyGroup);
	}
}

//check whether stone at risk is surrounded by the opposite colour
bool Board::hasEmptyLiberties(Stones& nodeStone, StoneColour stoneColour)
{
	for (auto libertyPosition : nodeStone.getLiberties())
	{
		//if there's a liberty which is not filled with the opposite colour, return true
		if (m_board.at(libertyPosition).getColour() != switchColour(stoneColour))
		{
			return true;
		}
	}

	//if all of a stone or group's liberties are full of the opposite colour, return that it does not have empty liberties
	return false;
}

//checks whether stones have been taken, based on whether their liberties are full
void Board::hasBeenTaken(position_t stoneAtRiskPosition, StoneColour stoneColour)
{
	Stones stoneAtRisk{ m_board.at(stoneAtRiskPosition) };
	
	//for a single stone nodeStone is stoneAtRisk
	Stones nodeStone{ m_board.at(stoneAtRisk.getWhichGroup()) };
	//const group_t &nodeGroup{ nodeStone.getGroup() };

	//if the stones are surrounded, remove them and give the other colour a point for each stone removed
	if (!hasEmptyLiberties(nodeStone, stoneColour))
	{
		//change score of the opposite colour by the size of the group taken
		changeScore(switchColour(stoneColour), nodeStone.getGroup().size());
		for (auto stonePosition : nodeStone.getGroup())
		{
			m_board.at(stonePosition).setEmptyStone(m_board, stonePosition);
		}

	}
}

void Board::placeMove(StoneColour turnColour, position_t stonePosition)
{
	//places the stone
	Stones& stone{ m_board.at(stonePosition) };
	stone.placeStone(stonePosition, turnColour);

	//finds stone neighbours
	neighbour_t neighbours{ stone.findNeighbourPositions() };

	//checks if any of the neighbours have been taken, or if they're the same colour it adds it to the stone group
	for (int neighbour : neighbours)
	{
		if (m_board.at(neighbour).getColour() == turnColour)
		{
			addToGroup(stonePosition, neighbour);
		}
		else if (m_board.at(neighbour).getColour() == switchColour(turnColour))
		{
			hasBeenTaken(neighbour, switchColour(turnColour));
		}
	}

	//if the move is suicidal we can reset the position to empty and ask for another move to place - wrong
	if (!hasEmptyLiberties(stone, turnColour))
	{

		stone.setEmptyStone(m_board, stonePosition);
		placeMove(turnColour, askForAnotherMove());
	}

}