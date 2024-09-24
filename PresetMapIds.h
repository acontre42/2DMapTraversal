#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Tile.h"
#include "GameMap.h"

class PresetMapIds
{
private:
	std::map<int, GameMap> gameMaps;
	std::map<std::pair<int, int>, std::pair<int, int>> startPositions; // Key is <prevMapId, nextMapId> which returns correct start position.
public:
	enum MAP_IDS {NO_MAP, MAP1, MAP2, MAP3};
	PresetMapIds();
	bool idExists(int id);
	GameMap& getGameMapById(int id);
	std::pair<int, int> getStartPos(int prevMapId, int nextMapId);
	void updateMapById(int id, std::vector<std::vector<Tile>> currentMap);
	void updatePriceById(int id, int price);
};

