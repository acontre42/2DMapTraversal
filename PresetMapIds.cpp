#include "PresetMapIds.h"
#include "GameMap.h"
#include <string>

PresetMapIds::PresetMapIds()
{
	// FIRST MAP
	std::vector<std::vector<Tile>> map1 = {
		{ Tile{Tile::EXIT}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile {Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}},
		{ Tile{Tile::HOLE}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND} },
		{ Tile{Tile::TREE}, Tile{Tile::TREE}, Tile{Tile::TREE}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::LAND} },
		{ Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::HOLE} },
		{ Tile{Tile::TREASURE}, Tile{Tile::WATER}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::LAND}, Tile{Tile::TREE} },
		{ Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::WATER}, Tile{Tile::TREE}, Tile{Tile::LAND}, Tile{Tile::LAND} }
	};
	map1[0][0].setExitId(MAP2);
	GameMap gm1{ MAP1, map1, "Map 1"};
	gameMaps.insert({ MAP1, gm1 });

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
	GameMap gm2{ MAP2, map2, "Map 2", 100 };
	gameMaps.insert({ MAP2, gm2 });

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
	GameMap gm3{ MAP3, map3, "Map 3", 175 };
	gameMaps.insert({ MAP3, gm3 });
	

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
	return (gameMaps.count(id) == 1) ? true : false;
}

GameMap& PresetMapIds::getGameMapById(int id) // ***
{
	if (gameMaps.count(id) == 1)
	{
		return gameMaps.at(id);
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
		gameMaps.at(id).setTilesMap(currentMap);
	}
	else
	{
		std::cout << "ERROR: could not update map, id does not exist\n";
		exit(1);
	}
}
// Should be called every time new area unlocked.
void PresetMapIds::updatePriceById(int id, int price)
{
	if (idExists(id))
	{
		gameMaps.at(id).setPrice(price);
	}
	else
	{
		std::cout << "ERROR: could not update map price, id does not exist\n";
		exit(1);
	}
}