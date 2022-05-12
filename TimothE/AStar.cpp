#include "AStar.h"
#include <algorithm>

//finds path for AI to take
glm::vec2 AStar::PathFinding(glm::vec2 startPos)
{
    std::vector<MapNode> openList;
    std::vector<MapNode> closedList;
    //set start pos in open list
    openList.push_back({ startPos, 0,0,0 });

    //while open list is not empty path isnt found
    while (openList.size() > 0)
    {
        //gets lowest f cost for moving to next tile
        int lowestIndex = 0;
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].fCost < openList[lowestIndex].fCost)
            {
                lowestIndex = i;
            }
        }

        //sets lowest fcost node to current node
        MapNode current = openList[lowestIndex];

        //if start point equals end point path found
        if (openList[lowestIndex].position == _mPoints[0])
        {
            //create path
            MapNode temp = current;
            _mPath.push_back(temp);
            while (temp.previousNodePAth != NULL)
            {
                _mPath.push_back(*temp.previousNodePAth);
                temp = *temp.previousNodePAth;
            }
        }

        //add current to open list and remove from closed list
        closedList.push_back(current);
        openList.erase(openList.begin() + lowestIndex);

        //get neighbours around current
        std::vector<MapNode> neighbours;
        std::vector<int> openIDs;
        std::vector<int> closedIDs;
        int id = current.id;
        neighbours.push_back(_mMapNodes.at(id - 1));//mid left
        neighbours.push_back(_mMapNodes.at(id + 1));//mid right
        neighbours.push_back(_mMapNodes.at(id + _mMapTilesX));//bottom
        neighbours.push_back(_mMapNodes.at(id - _mMapTilesX));//top
        neighbours.push_back(_mMapNodes.at(id - 1 + _mMapTilesX));//top left
        neighbours.push_back(_mMapNodes.at(id + 1 + _mMapTilesX));//top right
        neighbours.push_back(_mMapNodes.at(id - 1 - _mMapTilesX));//bottom left
        neighbours.push_back(_mMapNodes.at(id + 1 - _mMapTilesX));//bottom right

        //gets all nodes in open and closed for comparing ids
        for (int closedID = 0; closedID < closedList.size(); closedID++)
        {
            closedIDs.push_back(closedList.at(closedID).id);
        }
        for (int openID = 0; openID < openList.size(); openID++)
        {
            openIDs.push_back(openList.at(openID).id);
        }

        //for each neighbour of current
        for (int i= 0; i < neighbours.size(); i++)
        {
            //if neighbour id is not in closed
            if (!std::count(closedIDs.begin(), closedIDs.end(), neighbours[i].id))
            {
                //increase gcost if neighbour is in open list and if neighbour has not been evaluated
                int tempG = current.gCost + 1;

                if (std::count(openIDs.begin(), openIDs.end(), neighbours[i].id))
                {
                    if (tempG < neighbours[i].gCost)
                    {
                        neighbours[i].gCost = tempG;
                    }
                }
                //if neighbour was not in closed list
                else
                {
                    neighbours[i].gCost = tempG;
                    openList.push_back(neighbours[i]);
                }
                //sets h cost as distance from end
                /*float dist = sqrt(pow(neighbours[i].position.x - _mPoints.at(0).x, 2) +
                    pow(neighbours[i].position.y - _mPoints.at(0).y, 2));*/
                //neighbours[i].hCost = dist;
                //set f cost with f = g + h then set neighbour's previous node path to current
                neighbours[i].fCost = neighbours[i].gCost + neighbours[i].hCost;
                neighbours[i].previousNodePAth = &current;
            }

               
        }
    }


    return startPos;

}

//gets path points
std::vector<glm::vec2> AStar::GetPathPoints()
{
    return _mPoints;
}

//sets end path
void AStar::SetPathPoints(glm::vec2 _points)
{
    _mPoints.push_back(_points);
}

//set map coords
void AStar::SetMapCoords(std::vector<glm::vec2> mapTiles, glm::vec2 size)
{
    int id;
    //set all map tiles as nodes
    for each (glm::vec2 position in mapTiles)
    {
        MapNode mapTile;
        mapTile.fCost = 0;
        mapTile.hCost = 0;
        mapTile.gCost = 0;
        mapTile.id = id;
        mapTile.wall = false;
        id++;
        mapTile.position = position;
        _mMapNodes.push_back(mapTile);
    }
    _mMapTilesX = size.x;
    _mMapTilesY = size.y;

}

//calculates distance
int AStar::CalculateDistance(MapNode nodeA, MapNode nodeB)
{
    int distX = std::abs(nodeA.position.x - nodeB.position.x);
    int distY = std::abs(nodeA.position.y - nodeB.position.y);
    if (distX > distY)
    {
        return 14 * distY + 10 * (distX - distY);
    }
    return 14 * distX + 10 * (distY - distX);
}





