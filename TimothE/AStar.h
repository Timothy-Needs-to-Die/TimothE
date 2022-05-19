
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
	bool isObstacle = false;
	//Has this node already been visited 
	bool isVisited = false;

	//Distance to the end node
	float globalGoal = FLT_MAX;

	//Distance to the end node from here
	float localGoal = FLT_MAX;

	//X and Y position of the node in the map
	/*int xPos = 0;
	int yPos = 0;*/

	glm::vec2 pos;

	//A vector containing all of the nodes in the maze level
	std::vector<Node*> neighborNodes;
	//A pointer to the neighbor node that is closest to the start node
	glm::vec2 parentNode = { ERROR_PATH_POSITION, ERROR_PATH_POSITION };
};

class AStar
{
public:
	//The default constructor for the class
	AStar() = default;

	/// <summary>
	/// The constructor for the class which initializes the start and end nodes 
	/// </summary>
	/// <param name="startNode">The node that the player starts on</param>
	/// <param name="endNode">The node that the player ends on</param>
	AStar(Node* startNode, Node* endNode);

	//Overriding the default destructor to delete the memory associated with the direction and path lists
	~AStar();

	/// <summary>
	/// This function will calculate the shortest path for the maze. Using the A* Pathfinding Algorithm
	/// </summary>
	/// <returns>This function returns true if a path is found and false if a path is not found</returns>
	bool FindPath();

	/// <summary>
	/// This function will process the node list to find the directions the player needs to go in to get to the end
	/// </summary>
	void ProcessDirections();

	/// <summary>
	/// This function returns the node path list to the user
	/// </summary>
	std::list<Node*> GetPathOfNodes();
	void SetMap(TileMap* map);

private:
	//The starting node
	Node* mStartNode = nullptr;

	//The ending node
	Node* mEndNode = nullptr;

	//This list contains the directions the player needs to take in the form of Nodes. 
	std::list<Node*> mPathOfNodes;

	std::vector<Node> _mMapNodes;
	float width;
	float height;
	float tilesPerUnit;
};


