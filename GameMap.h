#pragma once
#include "Tile.h"
#include <vector>
#include <string>

const int UNLOCKED_PRICE = 0;

class GameMap
{
private:
	int id;
	std::vector<std::vector<Tile>> tilesMap;
	std::string mapName;
	int priceToUnlock;
	bool locked;
public:
	GameMap(int id, std::vector<std::vector<Tile>> tilesMap, std::string name = "", int princeToUnlock = 0);
	int getId();
	std::vector<std::vector<Tile>>& getTilesMap();
	std::string getMapName() const;
	int getUnlockPrice() const;
	bool isLocked() const;
	void setTilesMap(std::vector<std::vector<Tile>> tilesMap);
	void setMapName(std::string newName);
	void setPrice(int price);
	bool unlock(int& playerCoins);
};
