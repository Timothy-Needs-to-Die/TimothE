#include "pch.h"
#include "AStar.h"



AStar::~AStar()
{
	//clears the nodes list
	_pathOfNodes.clear();
}

struct node_greater_than {
	bool operator()(Node const* a, Node const* b) const {
		return a->_mGlobalGoal > b->_mGlobalGoal;
	}
};

std::vector<glm::vec2> AStar::FindPath(glm::vec2 start, glm::vec2 end)
{
	_pathOfNodes.clear();

	//This list will contain the untested nodes that will be used to cycle through each node in the map 
	std::vector<Node*> untestedNodes;

	//Reset all nodes on map.
	for (int i = 0; i < _mapNodes.size(); ++i) {
		_mapNodes[i]._mIsVisited = false;
		_mapNodes[i]._mParentNode = glm::vec2(-1);
		_mapNodes[i]._mGlobalGoal = FLT_MAX;
		_mapNodes[i]._mLocalGoal = FLT_MAX;
	}

	Node* currentNode = new Node();
	currentNode->_mPos = start;
	currentNode->_mLocalGoal = 0.0f;
	currentNode->_mGlobalGoal = glm::distance(currentNode->_mPos, end);
	currentNode->_mNeighborNodes = _mapNodes.at((start.y * _tilesPerUnit) * _width + (start.x * _tilesPerUnit))._mNeighborNodes;

	untestedNodes.emplace_back(currentNode);

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
			if (nodeNeighbor == nullptr) continue;

			//if the neighbor node is not visited and is not an obstacle then add it to the untestedNode list
			if (!nodeNeighbor->_mIsVisited && !nodeNeighbor->_mIsObstacle) {
				//Adds the neighboring node to the list
				untestedNodes.emplace_back(nodeNeighbor);
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

			if (dist <= 1.25f)
			{
				_pEndNode = nodeNeighbor;
				pathFound = true;
			}
		}
	}

	if (pathFound) {
		//if (mEnd != nullptr) {
			//Sets the previousNode to the endPoint as the A* algorithm works backwards
		Node& previousNode = *_pEndNode;
		
		size_t size = _pathOfNodes.size();
		//keep looping until the previousNode no longer has a parent this can only be the starting node
		while (previousNode._mParentNode != start)
		{
			//Check the parent node is valid
			if (previousNode._mParentNode.y == ERROR_PATH_POSITION) break;

			//adds the node to the path of nodes
			for (int i = 0; i < size; ++i) {
				if (_pathOfNodes[i]._mPos == previousNode._mPos) {
					int index = (start.y * _tilesPerUnit) * _width + (start.x * _tilesPerUnit);
					if (index < 0) index = 0;
					previousNode = _mapNodes.at(index);
					previousNode._mParentNode = start;
					return ProcessPath();
				}
			}

			_pathOfNodes.emplace_back(previousNode);
			size++;

			//Sets the previous node to the parent of this node
			int index = (previousNode._mParentNode.y * _tilesPerUnit) * _width + (previousNode._mParentNode.x * _tilesPerUnit);
			if (index < 0) index = 0;
			previousNode = _mapNodes.at(index);
		}
	}
	return ProcessPath();
}

void AStar::SetMap(TileMap* map)
{
	for (int i = 0; i < _mapNodes.size(); ++i) {
		_mapNodes[i]._mNeighborNodes.clear();
	}

	_mapNodes.clear();
	_tilesPerUnit = map->GetTilesPerUnit();
	_width = map->GetMapSize().x * _tilesPerUnit;
	_height = map->GetMapSize().y * _tilesPerUnit;

	glm::vec2 mapDimensions = map->GetTileMapDimensions();

	bool** collidableMap = map->GetCollidableTileMap();

	//Loop through map Y and X
	for (int y = 0; y < mapDimensions.y; y++) {
		for (int x = 0; x < mapDimensions.x; x++) {
			//Gets the desired tile
			TileData* td = map->GetTileFromXYIndex(x, y);

			//Sets the basic attributes.
			Node tile;
			tile._mIsObstacle = collidableMap[y][x];
			tile._mPos = td->pos;
			tile._mNeighborNodes.clear();
			_mapNodes.emplace_back(tile);

		}
	}

	for (int i = 0; i < _mapNodes.size(); i++)
	{
		int yIndex = i / _width;
		int xIndex = i - (yIndex * _width);

		glm::vec2 pos = _mapNodes[i]._mPos;

		//Left and Right
		if (xIndex > 0) _mapNodes[i]._mNeighborNodes.emplace_back(&_mapNodes[i - 1]); 
		else if (xIndex < _width) _mapNodes[i]._mNeighborNodes.emplace_back(&_mapNodes[i + 1]);

		//Top and Bottom		
		if (yIndex < _height) _mapNodes[i]._mNeighborNodes.emplace_back(&_mapNodes[i + _width]);
		else if (yIndex > 0) _mapNodes[i]._mNeighborNodes.emplace_back(&_mapNodes[i - _width]); 

		//Top Left and Top Right
		if (xIndex > 0 && yIndex < _height) _mapNodes[i]._mNeighborNodes.push_back(&_mapNodes[i - 1 + _width]); //TopLeft
		else if (xIndex < _width && yIndex < _height) _mapNodes[i]._mNeighborNodes.push_back(&_mapNodes[i + 1 + _width]); //TopRight

		//Bottom Left and Bottom Right
		if (xIndex > 0 && yIndex > _height) _mapNodes[i]._mNeighborNodes.push_back(&_mapNodes[i - 1 - _width]);
		else  if (xIndex < _width && yIndex > _height) _mapNodes[i]._mNeighborNodes.push_back(&_mapNodes[i + 1 - _width]);
	}
}

void AStar::UpdateNodeObstacleStatus(glm::vec2 worldPos, bool val)
{
	//TODO: Remove this

	int index = (worldPos.y * _tilesPerUnit) * _width + (worldPos.x * _tilesPerUnit);

	if (index < 0) index = 0;
	if (index > _mapNodes.size() - 1) index = _mapNodes.size() - 1;

	_mapNodes[index]._mIsObstacle = val;
}

std::vector<glm::vec2> AStar::ProcessPath()
{
	for (std::vector<Node>::iterator it = _pathOfNodes.begin(); it != _pathOfNodes.end(); ++it) {
		_processedPath.emplace_back(it->_mPos);
	}
	return _processedPath;
}
