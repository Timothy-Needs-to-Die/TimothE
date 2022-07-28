
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

	~AStar();

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

	std::vector<Node> _mapNodes;
	float _width;
	float _height;
	float _tilesPerUnit;
};

/*
	auto distance = [](Node* a, Node* b)
	{
		//Returns the distance between the two nodes
		return sqrtf((a->xPos - b->xPos) * (a->xPos - b->xPos) + (a->yPos - b->yPos) * (a->yPos - b->yPos));
	};

	auto heuristic = [distance](Node* a, Node* b) {
		return distance(a, b);
	};

	Node* currentNode = mStartNode;

	mStartNode->localGoal = 0.0f;
	mStartNode->globalGoal = heuristic(currentNode, mEndNode);

	std::list<Node*> untestedNodes;
	untestedNodes.push_back(mStartNode);

	bool pathFound = false;

	while (!untestedNodes.empty())
	{
		untestedNodes.sort(
			[](const Node* nodeA, const Node* nodeB) {
				return nodeA->globalGoal < nodeB->globalGoal;
			});

		while (!untestedNodes.empty() && untestedNodes.front()->isVisited)
		{
			untestedNodes.pop_front();
		}

		if (untestedNodes.empty())
			break;

		currentNode = untestedNodes.front();
		currentNode->isVisited = true; //Nodes only need to be calculated once

		for (auto nodeNeighbor : currentNode->neighborNodes) {
			if (!nodeNeighbor->isVisited && !nodeNeighbor->isObstacle) {
				untestedNodes.push_back(nodeNeighbor);
			}


			float potentiallyLowerGoal = currentNode->localGoal + distance(currentNode, nodeNeighbor);

			if (potentiallyLowerGoal < nodeNeighbor->localGoal) {
				nodeNeighbor->parentNode = currentNode;

				nodeNeighbor->localGoal = potentiallyLowerGoal;

				nodeNeighbor->globalGoal = nodeNeighbor->localGoal + heuristic(nodeNeighbor, mEndNode);
			}

			if (distance(nodeNeighbor, mEndNode) == 0) pathFound = true;
		}
	}

	return pathFound;
*/


