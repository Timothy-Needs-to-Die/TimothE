#include "AStar.h"
#include <algorithm>
glm::vec3 AStar::PathFinding(glm::vec3 startPos)
{
    std::vector<MapNode> openList;
    std::vector<MapNode> closedList;
    openList.push_back({ startPos, 0,0,0 });

    while (openList.size() > 0)
    {
        int lowestIndex = 0;
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].fCost < openList[lowestIndex].fCost)
            {
                lowestIndex = i;
            }
        }

        MapNode current = openList[lowestIndex];

        if (openList[lowestIndex].position == _mPoints[0])
        {
            MapNode temp = current;
            _mPath.push_back(temp);
            while (temp.previousNodePAth != NULL)
            {
                _mPath.push_back(*temp.previousNodePAth);
                temp = *temp.previousNodePAth;
            }
        }

        closedList.push_back(current);
        openList.erase(openList.begin() + lowestIndex);

        //for each neighbour
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


        for (int closedID = 0; closedID < closedList.size(); closedID++)
        {
            closedIDs.push_back(closedList.at(closedID).id);
        }
        for (int openID = 0; openID < openList.size(); openID++)
        {
            openIDs.push_back(openList.at(openID).id);
        }

        for (int i= 0; i < neighbours.size(); i++)
        {
            if (!std::count(closedIDs.begin(), closedIDs.end(), neighbours[i].id))
            {
                int tempG = current.gCost + 1;

                if (std::count(openIDs.begin(), openIDs.end(), neighbours[i].id))
                {
                    if (tempG < neighbours[i].gCost)
                    {
                        neighbours[i].gCost = tempG;
                    }
                }
                else
                {
                    neighbours[i].gCost = tempG;
                    openList.push_back(neighbours[i]);
                }
                /*float dist = sqrt(pow(neighbours[i].position.x - _mPoints.at(0).x, 2) +
                    pow(neighbours[i].position.y - _mPoints.at(0).y, 2));*/
                //neighbours[i].hCost = dist;
                neighbours[i].fCost = neighbours[i].gCost + neighbours[i].hCost;
                neighbours[i].previousNodePAth = &current;
            }

               
        }
    }


    return startPos;

}

std::vector<glm::vec3> AStar::GetPathPoints()
{
    return _mPoints;
}

void AStar::SetPathPoints(std::vector<glm::vec3> _points)
{
    _mPoints = _points;
}

void AStar::SetMapCoords(std::vector<glm::vec3> mapTiles, int sizeX, int sizeY)
{
    int id;
    //set all map tiles as nodes
    for each (glm::vec3 position in mapTiles)
    {
        MapNode mapTile;
        mapTile.fCost = 0;
        mapTile.hCost = 0;
        mapTile.gCost = 0;
        mapTile.id = id;
        id++;
        mapTile.position = position;
        _mMapNodes.push_back(mapTile);
    }
    _mMapTilesX = sizeX;
    _mMapTilesY = sizeY;

}

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





