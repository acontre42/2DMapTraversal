#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Tile.h"

class PresetMapIds
{
private:
	std::map<int, std::vector<std::vector<Tile>>> maps;
	std::map<std::pair<int, int>, std::pair<int, int>> startPositions; // Key is <prevMapId, nextMapId> which returns correct start position.
public:
	enum MAP_IDS {NO_MAP, MAP1, MAP2, MAP3};
	PresetMapIds();
	bool idExists(int id);
	std::vector<std::vector<Tile>>& getMapById(int id); // ***
	std::pair<int, int> getStartPos(int prevMapId, int nextMapId);
	void updateMapById(int id, std::vector<std::vector<Tile>> currentMap); // ***
};

