#include "Tile.h"
#include <string>
#include <iostream>

Tile::Tile(int type)
{
	this->type = type;
	this->searched = false;
	this->exitable = false;
	this->exitId = NO_EXIT_ID;
	switch (type)
	{
	case EXIT:
		description = "exit";
		icon = iEXIT;
		passable = true;
		searchable = false;
		exitable = true;
		break;
	case WATER:
		description = "water";
		icon = iWATER;
		passable = false;
		searchable = false;
		break;
	case TREE:
		description = "tree";
		icon = iTREE;
		passable = false;
		searchable = true;
		break;
	case HOLE:
		description = "hole";
		icon = iHOLE;
		passable = true;
		searchable = true;
		break;
	case TREASURE:
		description = "x-marked spot";
		icon = iTREASURE;
		passable = true;
		searchable = true;
		break;
	default:
		type = LAND;
		this->type = LAND;
	case LAND:
		description = "land";
		icon = iLAND;
		passable = true;
		searchable = false;
		break;
	}
}
int Tile::getType() const { return type; }
std::string Tile::getDesc() const { return description; }
char Tile::getIcon() const { return icon; }
bool Tile::isPassable() const { return passable; }
bool Tile::isSearchable() const { return searchable; }
bool Tile::wasSearched() const { return searched; }
bool Tile::isExitable() const { return exitable; }
int Tile::getExitId() const
{
	if (exitable && exitId == NO_EXIT_ID)
	{
		std::cout << "ERROR: exit tile is missing an exitId\n";
		exit(1);
	}
	return exitId;
}
void Tile::setExitId(int exitId)
{
	if (exitable)
	{
		this->exitId = exitId;
	}
}
void Tile::setAsSearched()
{
	if (searchable)
	{
		searched = true;
	}
}
