#pragma once
#include "Tile.h"
#include <string>

const char iEXIT = 'E', iWATER = '~', iLAND = ' ', iTREE = 'T', iHOLE = 'o', iTREASURE = 'x';
const int NO_EXIT_ID = -1;

class Tile
{
private:
	int type;
	std::string description;
	char icon;
	bool passable;
	bool searchable;
	bool searched;
	bool exitable;
	int exitId;
public:
	enum TYPES { EXIT, WATER, LAND, TREE, HOLE, TREASURE};
	Tile(int type);
	int getType() const;
	std::string getDesc() const;
	char getIcon() const;
	bool isPassable() const;
	bool isSearchable() const;
	bool wasSearched() const;
	bool isExitable() const;
	int getExitId() const;
	void setExitId(int exitId);
	void setAsSearched();
};

