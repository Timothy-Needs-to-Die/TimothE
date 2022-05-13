#pragma once
#include <vector>
#include <vec2.hpp>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "TileMap.h"
class MapNode {
public:
	glm::vec2 position;
	int fCost;
	int gCost;
	int hCost;
	int id;
	int previousNodePAth = 0;
	bool wall = false;
};


class TileMap;
class AStar
{
public:

	glm::vec2 PathFinding(glm::vec2 startPos);
	std::vector<glm::vec2> GetPathPoints();
	void SetPathPoints(glm::vec2 _points);
	//void SetMapCoords(std::vector<glm::vec2> mapTiles, glm::vec2 size);
	void SetMapCoords(std::vector<TileData> mapTiles, glm::vec2 size);

private:
	std::vector<glm::vec2> _mPoints;
	std::vector<MapNode> _mMapNodes;
	std::vector<int> _mPath;
	int _mMapTilesX;
	int _mMapTilesY;

};