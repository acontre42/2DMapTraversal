#include "GameMap.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>

GameMap::GameMap(std::vector<std::vector<Tile>> tilesMap, std::string mapName = "", int priceToUnlock = 0)
{
	if (tilesMap.size() <= 0)
	{
		std::cout << "ERROR: tilesMap is empty\n";
		exit(1);
	}

	this->tilesMap = tilesMap;
	this->mapName = mapName;
	this->priceToUnlock = priceToUnlock;
	locked = (priceToUnlock == UNLOCKED_PRICE ? false : true);
}
std::vector<std::vector<Tile>>& GameMap::getTilesMap() { return tilesMap; }
std::string GameMap::getMapName() const { return mapName; }
int GameMap::getUnlockPrice() const{ return priceToUnlock; }
bool GameMap::isLocked() const { return locked; }
void GameMap::setMapName(std::string newName)
{
	mapName = newName;
}
std::string GameMap::unlock(int& playerCoins)
{
	if (!locked)
	{
		return "This area has already been unlocked.\n";
	}
	else if (playerCoins < priceToUnlock)
	{

		std::string result = "Insufficient funds. Price to unlock next area is " + priceToUnlock;
		result += " coins. You currently have " + playerCoins;
		result += ".\n";
		return result;
	}
	else
	{
		playerCoins = playerCoins - priceToUnlock;
		locked = false;
		std::string result = "You've unlocked a new area! " + priceToUnlock;
		result += " coins have been subtracted from your inventory.\n";
		priceToUnlock = UNLOCKED_PRICE;
		return result;
	}
}