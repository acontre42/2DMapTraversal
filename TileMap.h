#pragma once
#include "Tile.h"
#include "PresetMapIds.h"
#include <vector>
#include <string>
#include "RNG.h" 

const int numDirections = 4;
enum DIRECTIONS { WEST = 1, NORTH = 2, EAST = 3, SOUTH = 4 };
enum MOVEMENTS { FORWARD, BACKWARD, LEFT, RIGHT };
const char FWEST = '<', FNORTH = '^', FEAST = '>', FSOUTH = 'v'; // Represents player
const int MIN_SEARCH_COINS = 0, MAX_SEARCH_COINS = 10, TREASURE_BONUS = 100; // For searching

struct Player
{
	int facing;
	int coins;
	Player()
	{
		this->facing = NORTH;
		this->coins = 0;
	}
};

class TileMap
{
private:
	PresetMapIds presetMaps; // Object with Map of vector<vector<Tile>> maps.
	int mapId;
	std::vector< std::vector<Tile> > tilesMap;
	std::pair<int, int> playerPos;
	int rows;
	int cols;
	Player player;
	RNG rng;
	void setMapInfo(int newMapId);
	std::string checkDestination(std::pair<int, int> destination, int direction);
	void updatePlayerPos(std::pair<int, int> destination, int movement);
	void promptExit();
	void promptSearch(std::pair<int, int> searchCoords);
	void searchArea(std::pair<int, int> coords);
public:
	static const int MAP1 = PresetMapIds::MAP1, MAP2 = PresetMapIds::MAP2;
	TileMap(int mapId);
	void display();
	void displayLegend();
	std::string goForward();
	std::string goBackward();
	std::string goLeft();
	std::string goRight();
	void traverse();
};

