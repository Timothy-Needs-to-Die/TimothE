#pragma once
#include <vector>
#include <vec3.hpp>
#include <stdlib.h>
#include <vector>
#include <algorithm>
class MapNode {
public:
	glm::vec3 position;
	int fCost;
	int gCost;
	int hCost;
	int id;
	MapNode* previousNodePAth = NULL;
};



class AStar
{
public:

	glm::vec3 PathFinding(glm::vec3 startPos);
	std::vector<glm::vec3> GetPathPoints();
	void SetPathPoints(std::vector<glm::vec3> _points);
	void SetMapCoords(std::vector<glm::vec3> mapTiles, int sizeX, int sizeY);

private:
	std::vector<glm::vec3> _mPoints;
	std::vector<MapNode> _mMapNodes;
	std::vector<MapNode> _mPath;
	int _mMapTilesX;
	int _mMapTilesY;

	int CalculateDistance(MapNode nodeA, MapNode nodeB);
};