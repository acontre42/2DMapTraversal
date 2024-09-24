#include "GameMap.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>

GameMap::GameMap(int id, std::vector<std::vector<Tile>> tilesMap, std::string mapName, int priceToUnlock)
{
	if (tilesMap.size() <= 0)
	{
		std::cout << "ERROR: tilesMap is empty\n";
		exit(1);
	}
	this->id = id;
	this->tilesMap = tilesMap;
	this->mapName = mapName;
	this->priceToUnlock = priceToUnlock;
	locked = (priceToUnlock == UNLOCKED_PRICE ? false : true);
}
int GameMap::getId() { return id; }
std::vector<std::vector<Tile>>& GameMap::getTilesMap() { return tilesMap; }
std::string GameMap::getMapName() const { return mapName; }
int GameMap::getUnlockPrice() const{ return priceToUnlock; }
bool GameMap::isLocked() const { return locked; }
void GameMap::setTilesMap(std::vector<std::vector<Tile>> tilesMap)
{
	this->tilesMap = tilesMap;
}
void GameMap::setMapName(std::string newName)
{
	mapName = newName;
}
void GameMap::setPrice(int price)
{
	priceToUnlock = price;
	locked = (priceToUnlock == UNLOCKED_PRICE ? false : true);
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