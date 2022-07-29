#include "pch.h"
#include "AStar.h"

std::vector<glm::vec2> AStar::FindPath(glm::vec2 start, glm::vec2 end)
{
	auto distance = [](Node* a, Node* b)
	{
		//Returns the distance between the two nodes
		return sqrtf((a->_pos.x - b->_pos.x) * (a->_pos.x - b->_pos.x) + (a->_pos.y - b->_pos.y) * (a->_pos.y - b->_pos.y));
	};

	auto heuristic = [distance](Node* a, Node* b) {
		return distance(a, b);
	};

	std::vector<Node> pathOfNodes;

	//This list will contain the untested nodes that will be used to cycle through each node in the map 
	std::list<Node*> untestedNodes;

	//Reset all nodes on map.
	for (int i = 0; i < _mapNodes.size(); ++i) {
		_mapNodes[i]._isVisited = false;
		_mapNodes[i]._parentNodePosition = glm::vec2(-1);
		_mapNodes[i]._globalGoal = FLT_MAX;
		_mapNodes[i]._localGoal = FLT_MAX;
	}

	Node* currentNode = new Node();
	currentNode->_pos = start;
	currentNode->_localGoal = 0.0f;
	currentNode->_globalGoal = glm::distance(currentNode->_pos, end);
	currentNode->_neighborNodes = _mapNodes.at((start.y * _tilesPerUnit) * _width + (start.x * _tilesPerUnit))._neighborNodes;


	_pEndNode = &_mapNodes.at((end.y * _tilesPerUnit) * _width + (end.x * _tilesPerUnit));

	untestedNodes.emplace_back(currentNode);

	bool pathFound = false;

	while (!untestedNodes.empty())
	{
		untestedNodes.sort(
			[](const Node* nodeA, const Node* nodeB) {
				return nodeA->_globalGoal < nodeB->_globalGoal;
			});


		//The elements at the start of the list may have already been visited, meaning that testing them would use unnecessary resources.
		while (!untestedNodes.empty() && untestedNodes.front()->_isVisited)
		{
			//remove the front node if it has been visited
			untestedNodes.erase(untestedNodes.begin());
		}

		//if there are no nodes available then break out of the loop
		if (untestedNodes.empty()) break;

		//sets the current node to the front of the list
		currentNode = untestedNodes.front();
		currentNode->_isVisited = true; //Nodes only need to be calculated once

		//Explore this node's neighbors
		for (auto& nodeNeighbor : currentNode->_neighborNodes) {
			if (nodeNeighbor == nullptr) continue;

			//if the neighbor node is not visited and is not an obstacle then add it to the untestedNode list
			if (!nodeNeighbor->_isVisited && !nodeNeighbor->_isObstacle) {
				//Adds the neighboring node to the list
				untestedNodes.emplace_back(nodeNeighbor);
			}


			//Calculates the neighbors 'potentially' lower distance 
			float potentiallyLowerGoal = currentNode->_localGoal + distance(currentNode, nodeNeighbor);

			//If the distance between this node and the neighbors is lower than the local score of the neighbor is then this should be the new parent node of the neighbor 
			if (potentiallyLowerGoal < nodeNeighbor->_localGoal) {
				//Sets the parent node to the new closest node
				nodeNeighbor->_parentNodePosition = currentNode->_pos;

				//sets the local goal to the new lowest goal
				nodeNeighbor->_localGoal = potentiallyLowerGoal;

				//Calculate the heuristic value of the neighbor based on there local goal and the distance to the end point
				nodeNeighbor->_globalGoal = nodeNeighbor->_localGoal + heuristic(nodeNeighbor, _pEndNode);
			}

			if (distance(nodeNeighbor, _pEndNode) == 0.0f)
			{
				pathFound = true;
				untestedNodes.clear();
				break;
			}
		}
	}

	if (pathFound) {
		Node& previousNode = *_pEndNode;
		
		size_t size = pathOfNodes.size();
		//keep looping until the previousNode no longer has a parent this can only be the starting node
		while (previousNode._parentNodePosition != start)
		{
			//Check the parent node is valid
			if (previousNode._parentNodePosition.y == ERROR_PATH_POSITION) break;

			//adds the node to the path of nodes
			for (int i = 0; i < size; ++i) {
				if (pathOfNodes[i]._pos == previousNode._pos) {
					int index = (start.y * _tilesPerUnit) * _width + (start.x * _tilesPerUnit);
					if (index < 0) index = 0;
					previousNode = _mapNodes.at(index);
					previousNode._parentNodePosition = start;
					return ProcessPath(pathOfNodes);
				}
			}

			pathOfNodes.emplace_back(previousNode);
			size++;

			//Sets the previous node to the parent of this node
			int index = (previousNode._parentNodePosition.y * _tilesPerUnit) * _width + (previousNode._parentNodePosition.x * _tilesPerUnit);
			if (index < 0) index = 0;
			previousNode = _mapNodes.at(index);
		}
	}
	return ProcessPath(pathOfNodes);
}

void AStar::SetMap(TileMap* map)
{
	for (int i = 0; i < _mapNodes.size(); ++i) {
		_mapNodes[i]._neighborNodes.clear();
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
			tile._isObstacle = collidableMap[y][x];
			tile._pos = td->pos;
			tile._neighborNodes.clear();
			_mapNodes.emplace_back(tile);

		}
	}

	for (int i = 0; i < _mapNodes.size(); i++)
	{
		int yIndex = i / _width;
		int xIndex = i - (yIndex * _width);

		glm::vec2 pos = _mapNodes[i]._pos;

		//Left and Right
		if (xIndex > 0) _mapNodes[i]._neighborNodes.emplace_back(&_mapNodes[i - 1]); 
		if (xIndex < _width) _mapNodes[i]._neighborNodes.emplace_back(&_mapNodes[i + 1]);

		//Top and Bottom		
		if (yIndex < _height) _mapNodes[i]._neighborNodes.emplace_back(&_mapNodes[i + _width]);
		if (yIndex > 0) _mapNodes[i]._neighborNodes.emplace_back(&_mapNodes[i - _width]); 

		//Top Left and Top Right
		if (xIndex > 0 && yIndex < _height) _mapNodes[i]._neighborNodes.push_back(&_mapNodes[i - 1 + _width]); //TopLeft
		if (xIndex < _width && yIndex < _height) _mapNodes[i]._neighborNodes.push_back(&_mapNodes[i + 1 + _width]); //TopRight

		//Bottom Left and Bottom Right
		if (xIndex > 0 && yIndex > _height) _mapNodes[i]._neighborNodes.push_back(&_mapNodes[i - 1 - _width]);
		if (xIndex < _width && yIndex > _height) _mapNodes[i]._neighborNodes.push_back(&_mapNodes[i + 1 - _width]);
	}
}

void AStar::UpdateNodeObstacleStatus(glm::vec2 worldPos, bool val)
{
	//TODO: Remove this

	int index = (worldPos.y * _tilesPerUnit) * _width + (worldPos.x * _tilesPerUnit);

	if (index < 0) index = 0;
	if (index > _mapNodes.size() - 1) index = _mapNodes.size() - 1;

	_mapNodes[index]._isObstacle = val;
}

std::vector<glm::vec2> AStar::ProcessPath(std::vector<Node>& nodePath)
{
	std::vector<glm::vec2> processedPath;

	TIM_LOG_LOG("Original Path Size: " << nodePath.size());

	glm::vec2 directionOld = glm::vec2{ 0.0f };

	for (int i = 1; i < nodePath.size(); i++) {
		glm::vec2 newDirection = glm::vec2{ nodePath[i - 1]._pos.x - nodePath[i]._pos.x, nodePath[i - 1]._pos.y - nodePath[i]._pos.y };

		if (newDirection != directionOld) 
		{
			processedPath.emplace_back(nodePath[i]._pos);
		}
		directionOld = newDirection;
	}

	TIM_LOG_LOG("Processed Path Size: " << processedPath.size());

	return processedPath;
}
