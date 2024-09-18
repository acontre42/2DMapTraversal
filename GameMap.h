#pragma once
#include "Tile.h"
#include <vector>
#include <string>

const int UNLOCKED_PRICE = 0;

class GameMap
{
private:
	std::vector<std::vector<Tile>> tilesMap;
	std::string mapName;
	int priceToUnlock;
	bool locked;
public:
	GameMap(std::vector<std::vector<Tile>> tilesMap, std::string name, int princeToUnlock);
	std::vector<std::vector<Tile>>& getTilesMap();
	std::string getMapName() const;
	int getUnlockPrice() const;
	bool isLocked() const;
	void setMapName(std::string newName);
	std::string unlock(int& playerCoins);
};
