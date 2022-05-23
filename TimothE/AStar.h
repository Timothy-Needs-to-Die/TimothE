
#pragma once
#include "List"
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm.hpp>
#include "TileMap.h"

#define ERROR_PATH_POSITION -1

/// <summary>
/// The Node struct is used to represent the information of a cell in the maze
/// </summary>
struct Node {
	//Is this node an obstacle i.e a wall
	bool _mIsObstacle = false;
	//Has this node already been visited 
	bool _mIsVisited = false;

	//Distance to the end node
	float _mGlobalGoal = FLT_MAX;

	//Distance to the end node from here
	float _mLocalGoal = FLT_MAX;

	//X and Y position of the node in the map
	/*int xPos = 0;
	int yPos = 0;*/

	glm::vec2 _mPos;

	//A vector containing all of the nodes in the maze level
	std::vector<Node*> _mNeighborNodes;
	//A pointer to the neighbor node that is closest to the start node
	glm::vec2 _mParentNode = { ERROR_PATH_POSITION, ERROR_PATH_POSITION };
};

class AStar
{
public:
	//The default constructor for the class
	AStar() = default;

	//Overriding the default destructor to delete the memory associated with the direction and path lists
	~AStar();

	/// <summary>
	/// This function will calculate the shortest path for the maze. Using the A* Pathfinding Algorithm
	/// </summary>
	/// <returns>This function returns true if a path is found and false if a path is not found</returns>
	std::vector<glm::vec2> FindPath(glm::vec2 start, glm::vec2 end);

	void SetMap(TileMap* map);
	std::vector<glm::vec2> processedPath;
private:

	Node* _mEndNode = nullptr;

	//This list contains the directions the player needs to take in the form of Nodes. 
	std::vector<Node> _mPathOfNodes;

	std::vector<Node> _mMapNodes;
	float _mWidth;
	float _mHeight;
	float _mTilesPerUnit;
};


