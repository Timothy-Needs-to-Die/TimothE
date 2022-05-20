#include "AStar.h"


AStar::~AStar()
{
	//clears the nodes list
	mPathOfNodes.clear();
}

std::vector<glm::vec2> AStar::FindPath(glm::vec2 start, glm::vec2 end)
{
	//This list will contain the untested nodes that will be used to cycle through each node in the map 
	std::list<Node*> untestedNodes;

	Node* currentNode = new Node();
	currentNode->pos = start;
	currentNode->localGoal = 0.0f;
	currentNode->globalGoal = glm::distance(currentNode->pos, end);
	//currentNode->isObstacle = mStartNode->isObstacle;
	//currentNode->isVisited = mStartNode->isVisited;
	currentNode->neighborNodes = _mMapNodes.at(0).neighborNodes;

	//currentNode->parentNode = { 0, 0 };


	untestedNodes.push_back(currentNode);


	bool pathFound = false;

	while (!untestedNodes.empty())
	{
		/*Sorts the list by order of distance in ascending order.
		This is done as lists do not have iterative access meaning it is harder to grab an
		element at a specified index.
		*/
		untestedNodes.sort(
			[](const Node* nodeA, const Node* nodeB) {
				return nodeA->globalGoal < nodeB->globalGoal;
			});

		//The elements at the start of the list may have already been visited, meaning that testing them would use unnecessary resources.
		while (!untestedNodes.empty() && untestedNodes.front()->isVisited)
		{
			//remove the front node if it has been visited
			untestedNodes.pop_front();
		}

		//if there are no nodes available then break out of the loop
		if (untestedNodes.empty())
			break;

		//sets the current node to the front of the list
		currentNode = untestedNodes.front();
		currentNode->isVisited = true; //Nodes only need to be calculated once

		//Explore this node's neighbors
		for (auto nodeNeighbor : currentNode->neighborNodes) {
			//if the neighbor node is not visited and is not an obstacle then add it to the untestedNode list
			if (!nodeNeighbor->isVisited && !nodeNeighbor->isObstacle) {
				//Adds the neighboring node to the list
				untestedNodes.push_back(nodeNeighbor);
			}


			//Calculates the neighbors 'potentially' lower distance 
			float potentiallyLowerGoal = currentNode->localGoal + glm::distance(currentNode->pos, nodeNeighbor->pos);

			//If the distance between this node and the neighbors is lower than the local score of the neighbor is then this should be the new parent node of the neighbor 
			if (potentiallyLowerGoal < nodeNeighbor->localGoal) {
				//Sets the parent node to the new closest node
				nodeNeighbor->parentNode = currentNode->pos;

				//sets the local goal to the new lowest goal
				nodeNeighbor->localGoal = potentiallyLowerGoal;

				//Calculate the heuristic value of the neighbor based on there local goal and the distance to the end point
				nodeNeighbor->globalGoal = nodeNeighbor->localGoal + glm::distance(nodeNeighbor->pos, end);
			}

			/*if the distance between the neighbor node and the end node is 0 then it means a path has been found.
			However it may not be the shortest path*/
			float dist = glm::distance(nodeNeighbor->pos, end);

			if (dist == 0)
			{
				mEndNode = nodeNeighbor;
				pathFound = true;
			}
		}
	}

	if (pathFound) {
		mPathOfNodes.clear();

		//if (mEnd != nullptr) {
			//Sets the previousNode to the endPoint as the A* algorithm works backwards
		Node* previousNode = mEndNode;

		if (previousNode != nullptr) {
			//keep looping until the previousNode no longer has a parent this can only be the starting node
			while (previousNode != nullptr && previousNode->parentNode != start)
			{

				//parent node check here
				if (previousNode->parentNode.y == ERROR_PATH_POSITION || previousNode->parentNode.x == ERROR_PATH_POSITION)
				{
					break;
				}

				//adds the node to the path of nodes
				auto it = std::find(mPathOfNodes.begin(), mPathOfNodes.end(), previousNode);
				if (it == mPathOfNodes.end()) {
					mPathOfNodes.push_back(previousNode);
				}

				//Sets the previous node to the parent of this node
				previousNode = &_mMapNodes.at((previousNode->parentNode.y * tilesPerUnit) * width + (previousNode->parentNode.x * tilesPerUnit));

			}
		}
	}

	std::vector<glm::vec2> processedPath;
	for (int i = 0; i < mPathOfNodes.size(); i++) {
		processedPath.push_back(mPathOfNodes[i]->pos);
	}
	mPathOfNodes.clear();

	return processedPath;

}

void AStar::SetMap(TileMap* map)
{
	tilesPerUnit = map->GetTilesPerUnit();
	width = map->GetMapSize().x * tilesPerUnit;
	height = map->GetMapSize().y * tilesPerUnit;
	std::vector<TileData> tiles = map->GetAllTilesInLayer(0);
	for (int i = 0; i < tiles.size(); i++)
	{
		Node tile;
		tile.isObstacle = tiles.at(i).collidable;
		tile.pos = { tiles.at(i).colXPos, tiles.at(i).colYPos };

		_mMapNodes.push_back(tile);

	}

	for (int i = 0; i < _mMapNodes.size(); i++)
	{
		_mMapNodes[i].neighborNodes.clear();

		int yIndex = i / width;
		int xIndex = i - (yIndex * width);


		glm::vec2 pos = _mMapNodes[i].pos;

		//Left
		if (xIndex > 0) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i - 1]);
		}

		//Right
		if (xIndex < width) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i + 1]);
		}

		//Top 
		if (yIndex < height) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i + width]);
		}

		//Bottom
		if (yIndex > height) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i - width]);
		}
	}

}
