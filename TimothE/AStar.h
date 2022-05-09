#pragma once
#include <vector>
#include <vec3.hpp>
#include <stdlib.h>
class AStar
{
public :
	struct Node
	{
		glm::vec3 position;
		int fCost;
	};

	glm::vec3 PathFinding(glm::vec3 startPos);
	std::vector<glm::vec3> GetPathPoints();
	void SetPathPoints(std::vector<glm::vec3> _points);
	void SetMapCoords(std::vector<glm::vec3> mapTiles, int sizeX, int sizeY);

private:
	std::vector<glm::vec3> _mPoints;
	std::vector<glm::vec3> _mMapTiles;
	int _mMapTilesX;
	int _mMapTilesY;

	int CalculateDistance(Node nodeA, Node nodeB);
	std::vector<glm::vec3> GetNeighbours(Node node);
};

