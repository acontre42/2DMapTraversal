#include "GameController.h"

GameController::GameController()
{
	this->mapId = PresetMapIds::NO_MAP;
	gameMap = nullptr;

	int defaultId = PresetMapIds::MAP1;
	if (presetMaps.idExists(defaultId))
	{
		setMapInfo(defaultId);
	}
	else
	{
		std::cout << "ERROR: Invalid id.\n";
		exit(1);
	}
}

GameController::GameController(int mapId)
{
	this->mapId = PresetMapIds::NO_MAP;
	gameMap = nullptr;
	if (presetMaps.idExists(mapId))
	{
		setMapInfo(mapId);
	}
	else
	{
		std::cout << "ERROR: Invalid id.\n";
		exit(1);
	}
}

void GameController::setMapInfo(int newMapId)
{
	presetMaps.updateMapById(mapId, tilesMap); // save current map progress before changing map

	this->gameMap = &presetMaps.getGameMapById(newMapId);
	this->tilesMap = gameMap->getTilesMap();
	this->playerPos = presetMaps.getStartPos(mapId, newMapId);
	if (gameMap->getId() != newMapId)
	{
		std::cout << "ERROR: newMapId != gameMap's id\n";
		exit(1);
	}
	this->mapId = gameMap->getId();
	this->rows = tilesMap.size();
	this->cols = tilesMap[0].size();
}

std::string GameController::checkDestination(std::pair<int, int> destination, int movement)
{
	std::string destinationString = "", moveString = "";
	switch (movement)
	{
	case FORWARD:
		destinationString = " ahead";
		moveString = "You moved forward.\n";
		break;
	case BACKWARD:
		destinationString = " behind you";
		moveString = "You moved backward.\n";
		break;
	case LEFT:
		destinationString = " to your left";
		moveString = "You made a left.\n";
		break;
	case RIGHT:
		destinationString = " to your right";
		moveString = "You made a right.\n";
		break;
	}

	if (destination == playerPos)
	{
		std::cout << "Error: positioning error\n";
		exit(1);
	}
	else if (destination.first < 0 || destination.first >= rows || destination.second < 0 || destination.second >= cols)
	{
		return "Cannot move out of bounds.\n";
	}
	else if (!tilesMap[destination.first][destination.second].isPassable())
	{
		Tile* desTile = &tilesMap[destination.first][destination.second]; // destination tile
		std::string blockedString = "Cannot pass " + desTile->getDesc() + destinationString;
		if (desTile->isSearchable())
		{
			blockedString = blockedString + ", but " + desTile->getDesc() + " is searchable. ";
			std::cout << blockedString;
			promptSearch(destination);
			updatePlayerPos(playerPos, movement); // playerPos stays same, changes facing direction
			return "\n";
		}
		else
		{
			blockedString = blockedString + ".\n";
			return blockedString;
		}
	}
	else
	{
		updatePlayerPos(destination, movement);
		return moveString;
	}
}

void GameController::updatePlayerPos(std::pair<int, int> destination, int movement)
{
	if (destination != playerPos)
	{
		playerPos = destination;
	}
	// change direction player's icon faces
	switch (movement)
	{
	case LEFT:
		player.facing = player.facing - 1;
		if (player.facing < WEST)
		{
			player.facing = SOUTH;
		}
		break;
	case BACKWARD:
		player.facing = player.facing - 2;
		if (player.facing < WEST)
		{
			player.facing = player.facing + numDirections;
		}
		break;
	case RIGHT:
		player.facing = player.facing + 1;
		if (player.facing > SOUTH)
		{
			player.facing = WEST;
		}
		break;
	}
}

void GameController::promptExit()
{
	char choice = ' ';
	do
	{
		std::cout << "Would you like to move to next area? Enter 'Y' for yes or 'N' for no. \n";
		std::cin >> choice;
		choice = toupper(choice);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!isValidChoice(choice)); // ***

	if (choice == 'Y')
	{
		int nextMapId = tilesMap[playerPos.first][playerPos.second].getExitId();
		if (!presetMaps.idExists(nextMapId))
		{
			std::cout << "ERROR: nextMapId: " << nextMapId << std::endl;
			exit(1);
		}
		
		setMapInfo(nextMapId);
	}
}

void GameController::promptUnlock(GameMap nextAreaGameMap) 
{
	int unlockPrice = nextAreaGameMap.getUnlockPrice();
	std::cout << "The next area costs " << unlockPrice << " coins to unlock. ";

	char choice = ' ';
	do
	{
		std::cout << "Would you like to use your coins to unlock this area? Enter 'Y' for yes or 'N' for no.\n";
		std::cin >> choice;
		choice = toupper(choice);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!isValidChoice(choice)); // ***

	if (choice == 'Y')
	{
		bool successfulUnlock = nextAreaGameMap.unlock(player.coins);
		if (successfulUnlock)
		{
			presetMaps.updatePriceById(nextAreaGameMap.getId(), nextAreaGameMap.getUnlockPrice());
			promptExit();
		}
	}
}

void GameController::promptSearch(std::pair<int, int> searchCoords)
{
	Tile* targetTile = &tilesMap[searchCoords.first][searchCoords.second];
	std::string tileDesc = targetTile->getDesc();
	if (targetTile->wasSearched())
	{
		std::cout << "This " << tileDesc << " has been searched already.\n";
	}
	else
	{
		char choice = ' ';
		do
		{
			std::cout << "Would you like to search " << tileDesc << "? Enter 'Y' for yes or 'N' for no. \n";
			std::cin >> choice;
			choice = toupper(choice);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (!isValidChoice(choice)); // ***

		if (choice == 'Y')
		{
			searchArea(searchCoords);
		}
	}
}

void GameController::searchArea(std::pair<int, int> coords)
{
	Tile* tile = &tilesMap[coords.first][coords.second];
	if (tile->wasSearched())
	{
		std::cout << "Error: search should not be possible\n";
		exit(1);
	}

	int numCoins = rng.getNumber(MIN_SEARCH_COINS, MAX_SEARCH_COINS);
	if (tile->getType() == Tile::TREASURE)
	{
		numCoins = numCoins + TREASURE_BONUS;
	}
	if (numCoins == 0)
	{
		std::cout << "You did not manage to find anything.\n";
	}
	else
	{
		std::cout << "You found " << numCoins << (numCoins == 1 ? " coin" : " coins") << "!\n";
	}
	tile->setAsSearched();
	player.coins = player.coins + numCoins;
}

void GameController::display()
{
	// info
	char playerIcon = ' ';
	switch (player.facing)
	{
	case WEST:
		playerIcon = FWEST;
		break;
	case NORTH:
		playerIcon = FNORTH;
		break;
	case EAST:
		playerIcon = FEAST;
		break;
	case SOUTH:
		playerIcon = FSOUTH;
		break;
	}
	std::cout << "LOCATION: " << gameMap->getMapName() << "\n";
	std::cout << "PLAYER: " << playerIcon;
	std::cout << "\tCOINS: " << player.coins << std::endl;

	// upper border
	for (int i = 0; i < cols + 2; i++)
	{
		std::cout << "- ";
	}
	std::cout << "\n";

	// side borders and contents
	for (int i = 0; i < rows; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < cols; j++)
		{
			if (i == playerPos.first && j == playerPos.second)
			{
				std::cout << playerIcon;
			}
			else
			{
				std::cout << tilesMap[i][j].getIcon();
			}
			std::cout << " ";
		}
		std::cout << "|\n";
	}

	// lower border
	for (int i = 0; i < cols + 2; i++)
	{
		std::cout << "- ";
	}
	std::cout << "\n";
}

void GameController::displayLegend()
{
	std::vector<std::pair<std::string, char>> legend = Tile::getLegendAsPairs();
	for (int i = 0; i < 20; i++)
	{
		std::cout << "- ";
	}
	std::cout << "\n\tMap Legend:\n";
	for (auto& pair : legend)
	{
		std::cout << "\t" <<  pair.second << "\t" << pair.first << "\n";
	}
	for (int i = 0; i < 20; i++)
	{
		std::cout << "- ";
	}
	std::cout << "\n";
}

std::string GameController::goForward()
{
	int facing = player.facing;
	std::pair<int, int> destination = playerPos;
	switch (facing)
	{
	case WEST:
		destination.second = destination.second - 1;
		break;
	case NORTH:
		destination.first = destination.first - 1;
		break;
	case EAST:
		destination.second = destination.second + 1;
		break;
	case SOUTH:
		destination.first = destination.first + 1;
		break;
	}
	
	return checkDestination(destination, FORWARD);
}

std::string GameController::goBackward()
{
	int facing = player.facing;
	std::pair<int, int> destination = playerPos;
	switch (facing)
	{
	case WEST:
		destination.second = destination.second + 1;
		break;
	case NORTH:
		destination.first = destination.first + 1;
		break;
	case EAST:
		destination.second = destination.second - 1;
		break;
	case SOUTH:
		destination.first = destination.first - 1;
		break;
	}

	return checkDestination(destination, BACKWARD);
}

std::string GameController::goLeft()
{
	int facing = player.facing;
	std::pair<int, int> destination = playerPos;
	switch (facing)
	{
	case WEST:
		destination.first = destination.first + 1;
		break;
	case NORTH:
		destination.second = destination.second - 1;
		break;
	case EAST:
		destination.first = destination.first - 1;
		break;
	case SOUTH:
		destination.second = destination.second + 1;
		break;
	}

	return checkDestination(destination, LEFT);
}

std::string GameController::goRight()
{
	int facing = player.facing;
	std::pair<int, int> destination = playerPos;
	switch (facing)
	{
	case WEST:
		destination.first = destination.first - 1;
		break;
	case NORTH:
		destination.second = destination.second + 1;
		break;
	case EAST:
		destination.first = destination.first + 1;
		break;
	case SOUTH:
		destination.second = destination.second - 1;
		break;
	}

	return checkDestination(destination, RIGHT);
}

void GameController::traverse() // TO DO: separate into functions?
{
	while (true)
	{
		display();

		std::vector<char> options = { 'F', 'B', 'L', 'R', 'M', 'Q', '$' }; // ***
		char choice = ' ';
		do
		{
			std::cout << "Enter 'F' to move FORWARD, 'B' to move BACKWARD, 'L' to go LEFT, or 'R' to go RIGHT.\n";
			std::cout << "To display MAP LEGEND, enter 'M'. To QUIT program, enter 'Q'.\n";
			std::cout << "What would you like to do? ";
			std::cin >> choice;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			choice = toupper(choice);
		} while (!isValidChoice(choice, options));

		std::string result = "";
		switch (choice)
		{
		case 'F':
			result = goForward();
			break;
		case 'B':
			result = goBackward();
			break;
		case 'L':
			result = goLeft();
			break;
		case 'R':
			result = goRight();
			break;
		case 'M':
			displayLegend();
			break;
		case 'Q':
			std::cout << "Goodbye!\n";
			exit(0);
		case '$': // ***
			player.coins = player.coins + 500;
			break;
		default:
			std::cout << "ERROR: choice error\n";
			exit(1);
		}

		std::cout << result;

		// check current tile conditions
		Tile* currentTile = &tilesMap[playerPos.first][playerPos.second];
		if (currentTile->isSearchable())
		{
			promptSearch(playerPos);
		}
		if (currentTile->isExitable())
		{
			int nextId = currentTile->getExitId();
			GameMap nextGM = presetMaps.getGameMapById(nextId);
			if (nextGM.isLocked()) 
			{
				promptUnlock(nextGM);
			}
			else
			{
				promptExit();
			}
		}

		std::cout << "\n";
	}
}
// Checks if user input is valid choice. By default, options are Y/N.
bool GameController::isValidChoice(char choice, std::vector<char> options) // ***
{
	std::vector<char>::iterator it;
	for (it = options.begin(); it != options.end(); it++)
	{
		if (choice == *it)
		{
			return true;
		}
	}
	return false;
}