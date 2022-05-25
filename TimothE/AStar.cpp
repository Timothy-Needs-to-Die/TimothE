#include "AStar.h"



AStar::~AStar()
{
	//clears the nodes list
	_mPathOfNodes.clear();
}

struct node_greater_than {
	bool operator()(Node const* a, Node const* b) const {
		return a->_mGlobalGoal > b->_mGlobalGoal;
	}
};

std::vector<glm::vec2> AStar::FindPath(glm::vec2 start, glm::vec2 end)
{
	_mPathOfNodes.clear();

	//This list will contain the untested nodes that will be used to cycle through each node in the map 
	std::vector<Node*> untestedNodes;

	//Reset all nodes on map.
	for (int i = 0; i < _mMapNodes.size(); ++i) {
		_mMapNodes[i]._mIsVisited = false;
		_mMapNodes[i]._mParentNode = glm::vec2(-1);
		_mMapNodes[i]._mGlobalGoal = FLT_MAX;
		_mMapNodes[i]._mLocalGoal = FLT_MAX;
	}

	Node* currentNode = new Node();
	currentNode->_mPos = start;
	currentNode->_mLocalGoal = 0.0f;
	currentNode->_mGlobalGoal = glm::distance(currentNode->_mPos, end);
	currentNode->_mNeighborNodes = _mMapNodes.at((start.y * _mTilesPerUnit) * _mWidth + (start.x * _mTilesPerUnit))._mNeighborNodes;

	untestedNodes.push_back(currentNode);

	bool pathFound = false;

	while (!untestedNodes.empty())
	{
		//Converts the untested nodes into a binary heap
		std::make_heap(untestedNodes.begin(), untestedNodes.end(), node_greater_than());

		//The elements at the start of the list may have already been visited, meaning that testing them would use unnecessary resources.
		while (!untestedNodes.empty() && untestedNodes.front()->_mIsVisited)
		{
			//remove the front node if it has been visited
			untestedNodes.erase(untestedNodes.begin());
		}

		//if there are no nodes available then break out of the loop
		if (untestedNodes.empty()) break;

		//sets the current node to the front of the list
		currentNode = untestedNodes.front();
		currentNode->_mIsVisited = true; //Nodes only need to be calculated once

		//Explore this node's neighbors
		for (auto& nodeNeighbor : currentNode->_mNeighborNodes) {
			//if the neighbor node is not visited and is not an obstacle then add it to the untestedNode list
			if (!nodeNeighbor->_mIsVisited && !nodeNeighbor->_mIsObstacle) {
				//Adds the neighboring node to the list
				untestedNodes.push_back(nodeNeighbor);
			}


			//Calculates the neighbors 'potentially' lower distance 
			float potentiallyLowerGoal = currentNode->_mLocalGoal + glm::length(currentNode->_mPos + nodeNeighbor->_mPos);

			//If the distance between this node and the neighbors is lower than the local score of the neighbor is then this should be the new parent node of the neighbor 
			if (potentiallyLowerGoal < nodeNeighbor->_mLocalGoal) {
				//Sets the parent node to the new closest node
				nodeNeighbor->_mParentNode = currentNode->_mPos;

				//sets the local goal to the new lowest goal
				nodeNeighbor->_mLocalGoal = potentiallyLowerGoal;

				//Calculate the heuristic value of the neighbor based on there local goal and the distance to the end point
				nodeNeighbor->_mGlobalGoal = nodeNeighbor->_mLocalGoal + glm::length(nodeNeighbor->_mPos + end);
			}

			/*if the distance between the neighbor node and the end node is 0 then it means a path has been found.
			However it may not be the shortest path*/
			float dist = glm::distance(nodeNeighbor->_mPos, end);

			if (dist <= 0.25f)
			{
				_mEndNode = nodeNeighbor;
				pathFound = true;
			}
		}
	}

	if (pathFound) {
		//if (mEnd != nullptr) {
			//Sets the previousNode to the endPoint as the A* algorithm works backwards
		Node& previousNode = *_mEndNode;
		
		int size = _mPathOfNodes.size();
		//keep looping until the previousNode no longer has a parent this can only be the starting node
		while (previousNode._mParentNode != start)
		{
			//Check the parent node is valid
			if (previousNode._mParentNode.y == ERROR_PATH_POSITION) break;

			//adds the node to the path of nodes
			for (int i = 0; i < size; ++i) {
				if (_mPathOfNodes[i]._mPos == previousNode._mPos) {
					int index = (start.y * _mTilesPerUnit) * _mWidth + (start.x * _mTilesPerUnit);
					if (index < 0) index = 0;
					previousNode = _mMapNodes.at(index);
					_mPathOfNodes.emplace_back(previousNode);
					break;
				}
			}

			_mPathOfNodes.push_back(previousNode);
			size++;

			//Sets the previous node to the parent of this node
			int index = (previousNode._mParentNode.y * _mTilesPerUnit) * _mWidth + (previousNode._mParentNode.x * _mTilesPerUnit);
			if (index < 0) index = 0;
			previousNode = _mMapNodes.at(index);
		}
	}

	//for (int i = 0; i < _mPathOfNodes.size(); ++i) {
	//	processedPath.emplace_back(_mPathOfNodes[i]->_mPos);
	//}

	for (std::vector<Node>::iterator it = _mPathOfNodes.begin(); it != _mPathOfNodes.end(); ++it) {
		processedPath.push_back(it->_mPos);
	}

	return processedPath;
}

void AStar::SetMap(TileMap* map)
{
	for (int i = 0; i < _mMapNodes.size(); ++i) {
		_mMapNodes[i]._mNeighborNodes.clear();
	}

	_mMapNodes.clear();
	_mTilesPerUnit = map->GetTilesPerUnit();
	_mWidth = map->GetMapSize().x * _mTilesPerUnit;
	_mHeight = map->GetMapSize().y * _mTilesPerUnit;

	std::vector<TileData> tiles = map->GetAllTilesInLayer(0);
	for (int i = 0; i < tiles.size(); i++)
	{
		Node tile;
		tile._mIsObstacle = map->CollidableAtPosition(i);
		tile._mPos = tiles.at(i).pos;

		_mMapNodes.push_back(tile);
	}

	for (int i = 0; i < _mMapNodes.size(); i++)
	{
		_mMapNodes[i]._mNeighborNodes.clear();

		int yIndex = i / _mWidth;
		int xIndex = i - (yIndex * _mWidth);

		glm::vec2 pos = _mMapNodes[i]._mPos;

		//Left
		if (xIndex > 0) {
			_mMapNodes[i]._mNeighborNodes.emplace_back(&_mMapNodes[i - 1]);
		}

		//Right
		if (xIndex < _mWidth) {
			_mMapNodes[i]._mNeighborNodes.emplace_back(&_mMapNodes[i + 1]);
		}

		//Top 
		if (yIndex < _mHeight) {
			_mMapNodes[i]._mNeighborNodes.emplace_back(&_mMapNodes[i + _mWidth]);
		}

		//Bottom
		if (yIndex > 0) {
			_mMapNodes[i]._mNeighborNodes.emplace_back(&_mMapNodes[i - _mWidth]);
		}

		//TopLeft
		if (xIndex > 0 && yIndex < _mHeight) {
			_mMapNodes[i]._mNeighborNodes.push_back(&_mMapNodes[i - 1 + _mWidth]);
		}

		//TopRight
		if (xIndex < _mWidth && yIndex < _mHeight) {
			_mMapNodes[i]._mNeighborNodes.push_back(&_mMapNodes[i + 1 + _mWidth]);
		}
		//BottomLeft
		if (xIndex > 0 && yIndex > _mHeight) {
			_mMapNodes[i]._mNeighborNodes.push_back(&_mMapNodes[i - 1 - _mWidth]);
		}

		//BottomRight
		if (xIndex < _mWidth && yIndex > _mHeight) {
			_mMapNodes[i]._mNeighborNodes.push_back(&_mMapNodes[i + 1 - _mWidth]);
		}
	}
}
