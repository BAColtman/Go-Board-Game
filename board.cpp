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
	std::cout << Input::boardLabelReverse(0) << " ";
	for (int i{ 1 }; i <= constants::pointNumber; i++)
	{
		//prints the current contents of each point
		std::cout << Output::stoneColourToSymbol(m_board.at(i - constants::zeroOffset).getColour()) << ' ';
		//makes a newline at the end of each row, and then prints the next label (apart from the last row)
		if ((i % constants::boardSize == 0) && (i != constants::pointNumber))
		{
			std::cout << "\n";
			//need an extra space for <10 to make the formatting nice
			if (Input::boardLabelReverse(i / constants::boardSize) < 10)
				std::cout << " ";
			std::cout << Input::boardLabelReverse(i / constants::boardSize) << " ";
		}
	}
	std::cout << "\n\n";
}

//sets the entry of a stone on the board to reflect that a stone is not there
void Board::setPointToEmptyStone(position_t stonePosition)
{
	Stones &stone = m_board.at(stonePosition);
	stone.setColour(StoneColour::empty);
	stone.setWhichGroup(constants::noPosition);
	stone.setGroup(constants::emptyGroup);
	stone.resetLiberties();
}



position_t Board::inputToPosition(std::string move)
{

	try
	{
		int columnIndex{ Input::letterToColumnNumber(move.at(0))};
		int rowIndex{ Input::boardLabelReverse(Input::inputToRowNumber(move)) };


		//returns the coordinates of where the stone should be placed, with the row entry reversed appropriately
		position_t position{ Input::boardIndex(rowIndex, columnIndex) };

		//check whether there's a stone already there
		//if position is invalid at() will throw an exception when we try to access it
		if (m_board.at(position).getColour() != StoneColour::empty)
		{
			throw "Can't place a stone on a filled space";
		}
		else
			return position;
	}
	//All the different exceptions put out their own error code
	catch (const char* exception)
	{
		std::cerr << exception << "\n";
	}
	catch (std::invalid_argument)
	{
		std::cout << "Invalid input\n";
	}
	catch (std::out_of_range)
	{
		std::cout << "Invalid board space\n";
	}
	catch (error_t)
	{
		std::cout << "Invalid move\n";
	}
	//regardless of what sort of exception is thrown, it will ask for another move afterwards
	std::cout << "Please pick another move\n\n";
	return getMove();
	
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


	if (move == "pass")
	{
		return constants::passFlag;
	}
	else
	{
		return inputToPosition(move);
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

	Input::sortVectorDescending(mergedGroup);
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
	Input::removeInvalidPositions(mergedGroup);

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

	Input::removeInvalidPositions(libertyGroup);

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

//Removes a stone from the group it's currently in - we use this if we need to reverse a suicide move
void Board::removePointFromGroup(position_t stonePosition)
{
	//need to find which group it's in and remove it from the group, reset it to be in its own group
	Stones &nodeStone = m_board.at(m_board.at(stonePosition).getWhichGroup());
	group_t group{ nodeStone.getGroup() };
	for (int i{ 0 }; i < static_cast<int>(group.size()); i++)
	{
		position_t& position{ group.at(i) };
		if (position == stonePosition)
		{
			position = constants::noPosition;
			//break;
		}
	}

	Input::removeInvalidPositions(group);
	nodeStone.setGroup(group);
}

//check whether stones at risk are surrounded by the opposite colour
bool Board::hasEmptyLiberties(Stones& nodeStone, StoneColour stoneColour)
{
	for (auto libertyPosition : nodeStone.getLiberties())
	{
		//if there's a liberty which is not filled with the opposite colour, return true
		if (m_board.at(libertyPosition).getColour() != Input::switchColour(stoneColour))
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
		m_score.changeScore(Input::switchColour(stoneColour), nodeStone.getGroup().size());
		for (auto stonePosition : nodeStone.getGroup())
		{
			setPointToEmptyStone(stonePosition);
		}

	}
}


bool Board::placeMove(StoneColour turnColour, position_t stonePosition)
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
		else if (m_board.at(neighbour).getColour() == Input::switchColour(turnColour))
		{
			hasBeenTaken(neighbour, Input::switchColour(turnColour));
		}
	}

	//if the move is suicidal we can reset the position to empty and ask for another move to place
	if (!hasEmptyLiberties(m_board.at(stone.getWhichGroup()), turnColour))
	{
		removePointFromGroup(stonePosition);
		setPointToEmptyStone(stonePosition);
		std::cout << "Suicide moves are not valid\n";
		return false;
	}
	else
		return true;

}

lettersArray_t Board::initialiseLetterArray()
{
	lettersArray_t letterArray;
	int offset{ constants::asciiOffset + constants::zeroOffset };
	for (int i{ 0 }; i < constants::boardSize; i++)
	{
		letterArray.at(i) = static_cast<char>(i + offset);
		//skips I, as on a traditional Go board
		if (i == 7)
			offset++;
	}
	return letterArray;
}