#include "AStar.h"
#include <algorithm>

//uses a* algorthigm to find path
glm::vec2 AStar::PathFinding(glm::vec2 startPos)
{
    _mPath.clear();

    //startPos = { 0,0 };
    std::vector<MapNode> openList;
    std::vector<MapNode> closedList;
    openList.push_back({ startPos, 0,0,0 });
    //while open list contains something
    while (openList.size() > 0)
    {
        //gets node with lowest fcost
        int lowestIndex = 0;
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].fCost < openList[lowestIndex].fCost)
            {
                lowestIndex = i;
            }
        }

        //sets current node to lowest f cost node
        MapNode current = openList[lowestIndex];

        

        //removes current from open list and adds to closed list to confirm value of node
        closedList.push_back(current);
        openList.erase(openList.begin() + lowestIndex);

        //if lowest f cost position is equal to end point recreate path
        if (current.position == _mPoints[0])
        {
            std::cout << "done" << std::endl;
            MapNode temp = current;
            _mPath.push_back(temp.id);
            while (temp.previousNodePAth != 0)
            {
                _mPath.push_back(temp.previousNodePAth);
                temp = _mMapNodes.at(temp.id);
            }
            return _mMapNodes.at(temp.previousNodePAth).position;
        }
        else {
            //std::cout << "failed" << std::endl;
        }

        //gets neighbours from current
        std::vector<MapNode> neighbours;
        std::vector<int> openIDs;
        std::vector<int> closedIDs;
        int id = current.id; // cant be on edge of map
        if ((id - 1) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id - 1));//mid left
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id + 1) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id + 1));//mid right
        }
        if ((id + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id + _mMapTilesX));//bottom
        }
        if ((id - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id - _mMapTilesX));//top
        }
        if ((id - 1 + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id - 1 + _mMapTilesX));//top left
        }
        if ((id + 1 + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id + 1 + _mMapTilesX));//top right
        }
        if ((id - 1 - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id - 1 - _mMapTilesX));//bottom left
        }
        if ((id + 1 - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id + 1 - _mMapTilesX));//bottom right
        }

        for (int i = 0; i < neighbours.size(); i++)
        {
            if (neighbours.at(i).id < 0)
            {
                neighbours.at(i).id = 0;
            }
            else if(neighbours.at(i).id > _mMapTilesX * _mMapTilesY)
            {
                neighbours.at(i).id = _mMapTilesX * _mMapTilesY;
            }
        }

        //finds ids for open and closed lists
        for (int closedID = 0; closedID < closedList.size(); closedID++)
        {
            closedIDs.push_back(closedList.at(closedID).id);
        }
        for (int openID = 0; openID < openList.size(); openID++)
        {
            openIDs.push_back(openList.at(openID).id);
        }

        //for each neighbour
        for (int i= 0; i < neighbours.size(); i++)
        {
            //if neighbour is not in closed list and if in open list then add 1 to neighbour gcost
            if (!std::count(closedIDs.begin(), closedIDs.end(), neighbours[i].id))
            {
                int tempG = current.gCost + 1;
                //finds distance between current and end position
                float dist = sqrt(pow(neighbours[i].position.x - _mPoints.at(0).x, 2) +
                    pow(neighbours[i].position.y - _mPoints.at(0).y, 2));
                //sets f and h cost and sets previours node as current for path creation
                neighbours[i].gCost = sqrt(pow(neighbours[i].position.x - current.position.x, 2) +
                    pow(neighbours[i].position.y - current.position.y, 2));
                neighbours[i].hCost = sqrt(pow(neighbours[i].position.x - _mPoints.at(0).x, 2) +
                    pow(neighbours[i].position.y - _mPoints.at(0).y, 2));
                neighbours[i].fCost = neighbours[i].gCost + neighbours[i].hCost;
                neighbours[i].previousNodePAth = current.id;
                neighbours[i].hCost = dist;
                if (std::count(openIDs.begin(), openIDs.end(), neighbours[i].id))
                {
                    if (tempG < neighbours[i].gCost)
                    {
                        neighbours[i].gCost = tempG;
                    }
                }
                //else if in closed list then open list includes neighbour
                else
                {
                    neighbours[i].gCost = tempG;
                    openList.push_back(neighbours[i]);
                }
                
            }

               
        }
    }

    std::cout << "fail" << std::endl;
    return startPos;

}

//gets all paths the ai will take
std::vector<glm::vec2> AStar::GetPathPoints()
{
    return _mPoints;
}

//sets new path points
void AStar::SetPathPoints(glm::vec2 _points)
{
    _mPoints.push_back(_points);
}

//sets tile map
void AStar::SetMapCoords(std::vector<TileData> mapTiles, glm::vec2 size)
{
    int id = 0;
    //set all map tiles as nodes
    for each (TileData position in mapTiles)
    {
        MapNode mapTile;
        mapTile.fCost = 0;
        mapTile.hCost = 0;
        mapTile.gCost = 0;
        mapTile.id = id;
        id++;
        mapTile.position.x = position.colXPos;
        mapTile.position.y = position.colYPos;
        mapTile.wall = position.collidable;
        _mMapNodes.push_back(mapTile);
    }
    _mMapTilesX = size.x;
    _mMapTilesY = size.y;

}






