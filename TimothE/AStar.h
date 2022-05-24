
#pragma once
#include "List"
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm.hpp>
#include "TileMap.h"
#include "Node.h"




class AStar : public Component
{
public:
	AStar(GameObject* gameObject) : Component(gameObject) {
		SetType(Types::Pathfinding);
	}

	~AStar();
	COMPONENT_STATIC_TYPE(Pathfinding);

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

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
};


