#include "PresetMapIds.h"

PresetMapIds::PresetMapIds()
{
	// FIRST MAP
	std::vector<std::vector<Tile>>map1 = {
		{ Tile{Tile::EXIT}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile {Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}},
		{ Tile{Tile::HOLE}, Tile{Tile::LAND}, Tile {Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND} },
		{ Tile{Tile::TREE}, Tile{Tile::TREE}, Tile {Tile::TREE}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND} },
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile {Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::HOLE} },
		{ Tile{Tile::TREASURE}, Tile{Tile::WATER}, Tile {Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE} },
		{ Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::LAND} }
	};
	map1[0][0].setExitId(MAP2);
	maps.insert({ MAP1, map1 });

	// SECOND MAP
	std::vector<std::vector<Tile>> map2 = {
		{ Tile{Tile::LAND}, Tile{Tile::TREASURE}, Tile{Tile::TREE}, Tile{Tile::EXIT}},
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::LAND}},
		{ Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::TREE}, Tile{Tile::LAND}},
		{ Tile{Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::HOLE}},
		{ Tile{Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND}},
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}},
		{ Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::TREE}, Tile{Tile::LAND}},
		{ Tile{Tile::HOLE}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::EXIT}}
	};
	map2[0][3].setExitId(MAP3);
	map2[7][3].setExitId(MAP1);
	maps.insert({ MAP2, map2 });

	// THIRD MAP
	std::vector<std::vector<Tile>> map3 = {
		{ Tile{Tile::TREE}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}},
		{ Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::WATER}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::WATER}},
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREASURE}, Tile{Tile::LAND}, Tile{Tile::WATER}},
		{ Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::WATER}},
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::HOLE}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}},
		{ Tile{Tile::EXIT}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}}
		
	};
	map3[5][0].setExitId(MAP2);
	maps.insert({ MAP3, map3 });
	

	// START POSITIONS
	startPositions.insert({ { NO_MAP, MAP1 }, { 5, 5 } }); // () -> MAP1
	startPositions.insert({ {MAP2, MAP1}, {0, 0} }); // MAP2 -> MAP1
	startPositions.insert({ {MAP1, MAP2} , {7, 3} }); // MAP1 -> MAP2
	startPositions.insert({ {MAP3, MAP2}, {0, 3} }); // MAP3 -> MAP2
	startPositions.insert({ {MAP2, MAP3}, {5, 0} }); // MAP2 -> MAP3
}

bool PresetMapIds::idExists(int id)
{
	if (id == NO_MAP)
	{
		return false;
	}
	return (maps.count(id) == 1) ? true : false;
}

std::vector<std::vector<Tile>>& PresetMapIds::getMapById(int id) // ***
{
	if (maps.count(id) == 1)
	{
		return maps.at(id);
	}
	else
	{
		std::cout << "ERROR: error getting map\n";
		exit(1);
	}
}
// Start position determined by <prevMapId, nextMapId> key.
std::pair<int, int> PresetMapIds::getStartPos(int prevMapId, int nextMapId)
{
	std::pair<int, int> key = { prevMapId, nextMapId };
	if (startPositions.count(key) == 1)
	{
		return startPositions.at(key);
	}
	else
	{
		std::cout << "ERROR: player position error\n";
		std::cout << "<p, n> = " << prevMapId << ", " << nextMapId << std::endl;
		exit(1);
	}
}
// Should be called before getMapById whenever changing maps.
void PresetMapIds::updateMapById(int id, std::vector<std::vector<Tile>> currentMap) // ***
{
	if (id == NO_MAP)
	{
		return; // initial state, nothing to save
	}
	else if (idExists(id))
	{
		maps[id] = currentMap;
	}
	else
	{
		std::cout << "ERROR: could not update map, id does not exist\n";
		exit(1);
	}
}