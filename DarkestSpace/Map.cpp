#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map() {

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {

	char tile;
	std::fstream mapFile;
	mapFile.open(path);



	mapFile.close();
}
