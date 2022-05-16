#include "AStar.h"

//Using a initializer list to initialize the mStartNode and mEndNode variables
AStar::AStar(Node* startNode, Node* endNode) : mStartNode(startNode), mEndNode(endNode) {}

AStar::~AStar()
{
	//clears the nodes list
	mPathOfNodes.clear();
}

bool AStar::FindPath()
{
	/// <summary>
	/// Lambda expression to get the distance between two nodes on the map. 
	/// </summary>
	/// <returns>The distance between two nodes</returns>
	auto distance = [](Node* a, Node* b)
	{
		//Returns the distance between the two nodes

		float ySeparation = b->pos.y - a->pos.y;
		float xSeparation = b->pos.x - a->pos.x;

		return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
	};

	/// <summary>
	/// Lambda expression used to calculate the heuristic value between two nodes.
	/// </summary>
	/// <returns>The heuristic value between nodes on the map</returns>
	auto heuristic = [distance](Node* a, Node* b) {
		/*Currently the heuristic value is based upon the overall distance between two nodes,
		however this could be changed to take further variables into mind such as the players speed
		on a particular type of tile. e.g. the player would move slower through water than on solid stone*/
		return distance(a, b);
	};

	//This list will contain the untested nodes that will be used to cycle through each node in the map 
	std::list<Node*> untestedNodes;

	Node* currentNode = new Node();
	currentNode->pos = mStartNode->pos;
	currentNode->localGoal = 0.0f;
	currentNode->globalGoal = heuristic(currentNode, mEndNode);
	currentNode->isObstacle = mStartNode->isObstacle;
	currentNode->isVisited = mStartNode->isVisited;
	currentNode->neighborNodes = _mMapNodes.at(0).neighborNodes;

	currentNode->parentNode = { 0, 0 };


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

		if (currentNode->neighborNodes.size() > 6) {
			untestedNodes.pop_front();
			continue;

		}

		//Explore this node's neighbors
		for (auto nodeNeighbor : currentNode->neighborNodes) {
			//if the neighbor node is not visited and is not an obstacle then add it to the untestedNode list
			if (!nodeNeighbor->isVisited && !nodeNeighbor->isObstacle) {
				//Adds the neighboring node to the list
				untestedNodes.push_back(nodeNeighbor);
			}


			//Calculates the neighbors 'potentially' lower distance 
			float potentiallyLowerGoal = currentNode->localGoal + distance(currentNode, nodeNeighbor);

			//If the distance between this node and the neighbors is lower than the local score of the neighbor is then this should be the new parent node of the neighbor 
			if (potentiallyLowerGoal < nodeNeighbor->localGoal) {
				//Sets the parent node to the new closest node
				nodeNeighbor->parentNode = currentNode->pos;

				//sets the local goal to the new lowest goal
				nodeNeighbor->localGoal = potentiallyLowerGoal;

				//Calculate the heuristic value of the neighbor based on there local goal and the distance to the end point
				nodeNeighbor->globalGoal = nodeNeighbor->localGoal + heuristic(nodeNeighbor, mEndNode);
			}

			/*if the distance between the neighbor node and the end node is 0 then it means a path has been found.
			However it may not be the shortest path*/
			float dist = distance(nodeNeighbor, mEndNode);
			if (dist < 5) {
				int i = 4;
			}
			if (dist == 0)
			{
				pathFound = true;

			}
		}
	}

	//returns if the path has been found
	return pathFound;
}

void AStar::ProcessDirections()
{
	mPathOfNodes.clear();

	if (mEndNode != nullptr) {
		//Sets the previousNode to the endPoint as the A* algorithm works backwards
		Node* previousNode = mEndNode;

		if (previousNode != nullptr) {
			//keep looping until the previousNode no longer has a parent this can only be the starting node
			while (previousNode != nullptr && previousNode->parentNode != mStartNode->pos)
			{

				//parent node check here
				if (previousNode->parentNode.y == 10000 || previousNode->parentNode.x == 10000)
				{
					//break;
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
}


#pragma region Getters
std::list<Node*> AStar::GetPathOfNodes()
{
	return mPathOfNodes;
}
void AStar::SetMap(TileMap* map)
{
	tilesPerUnit = map->GetTilesPerUnit();
	width = map->GetMapSize().x * tilesPerUnit;
	height = map->GetMapSize().y * tilesPerUnit;
	std::vector<TileData>* tiles = map->GetAllTiles();
	for (int i = 0; i < tiles->size(); i++)
	{
		Node tile;
		tile.isObstacle = tiles->at(i).collidable;
		tile.pos = { tiles->at(i).colXPos, tiles->at(i).colYPos };
		
		_mMapNodes.push_back(tile);

	}

	for (int i = 0; i < _mMapNodes.size(); i++)
	{
		_mMapNodes[i].neighborNodes.clear();

		if (_mMapNodes[i].pos == glm::vec2{6.0f, 6.0f}) {
			int i = 3;
		}

		glm::vec2 pos = _mMapNodes[i].pos;

		//Left
		if (i > 0) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i - 1]);
		}

		//Right
		if (i < width) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i + 1]);
		}

		//Top
		if (i < i + width) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i + width]);
		}

		//Bottom
		if (i > i - width) {
			_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[i - width]);
		}

		//
		//if (pos.x > 0) {
		//	_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[pos.y * width + (pos.x - 1)]);
		//}
		////if the node is not on the right most side then add the right hand node to the nodes neighbors
		//if (pos.x < width - 1) {
		//	_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[pos.y * width + (pos.x + 1)]);
		//}
		////if the node is not on top of the map then add the node above to the nodes neighbors
		//if (pos.y > 0) {
		//	_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[(pos.y - 1) * width + pos.x]);
		//}
		////if the node is not at the bottom of the map then add the node below it to the nodes neighbors
		//if (pos.y < height - 1) {
		//	_mMapNodes[i].neighborNodes.push_back(&_mMapNodes[(pos.y + 1) * width + pos.x]);
		//}
	}

}
#pragma endregion 