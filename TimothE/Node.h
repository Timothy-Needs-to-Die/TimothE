#include "pch.h"

#define ERROR_PATH_POSITION -1

/// <summary>
/// The Node struct is used to represent the information of a cell in the maze
/// </summary>
struct Node {
	//Is this node an obstacle i.e a wall
	bool _isObstacle = false;
	//Has this node already been visited 
	bool _isVisited = false;

	//Distance to the end node
	float _globalGoal = FLT_MAX;

	//Distance to the end node from here
	float _localGoal = FLT_MAX;

	//X and Y position of the node in the map
	glm::vec2 _pos;

	//A vector containing all of the nodes in the maze level
	std::vector<Node*> _neighborNodes;
	//A pointer to the neighbor node that is closest to the start node
	glm::vec2 _parentNodePosition = { ERROR_PATH_POSITION, ERROR_PATH_POSITION };
};