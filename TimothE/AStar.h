
#pragma once
#include "List"
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm.hpp>
#include "TileMap.h"
#include "Node.h"




class AStar
{
public:
	AStar() : _height(32), _tilesPerUnit(4.0f), _width(32) { }

	/// <summary>
	/// This function will calculate the shortest path for the maze. Using the A* Pathfinding Algorithm
	/// </summary>
	/// <returns>This function returns true if a path is found and false if a path is not found</returns>
	std::vector<glm::vec2> FindPath(glm::vec2 start, glm::vec2 end);

	void SetMap(TileMap* map);

	void UpdateNodeObstacleStatus(glm::vec2 worldPos, bool val);

private:
	std::vector<glm::vec2> ProcessPath(std::vector<Node>& nodePath);


	Node* _pEndNode = nullptr;

	//This list contains the directions the player needs to take in the form of Nodes. 

	std::vector<Node*> _mapNodes;
	float _width;
	float _height;
	float _tilesPerUnit;
};


