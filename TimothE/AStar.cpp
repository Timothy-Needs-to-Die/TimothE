#include "AStar.h"
#include <algorithm>

//uses a* algorthigm to find path
glm::vec2 AStar::PathFinding(glm::vec2 startPos)
{
    _mPath.clear();

    //startPos = { 0,0 };
    std::vector<MapNode> openList;
    std::vector<MapNode> closedList;
    openList.push_back({startPos});
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


        //if lowest f cost position is equal to end point recreate path
        if (current.position == _mEnd)
        {
            
            MapNode temp = current;
            _mPath.push_back(temp.id);
            while (temp.previousNodePAth != 0)
            {
                std::cout << "done" << std::endl;
                _mPath.push_back(temp.previousNodePAth);
                temp = _mMapNodes.at(temp.id);
            }
            return _mMapNodes.at(temp.previousNodePAth).position;
        }
        else {
            //std::cout << "failed" << std::endl;
        }

        //removes current from open list and adds to closed list to confirm value of node
        openList.erase(openList.begin() + lowestIndex);
        closedList.push_back(current);
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
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id + _mMapTilesX));//bottom
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id - _mMapTilesX));//top
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id - 1 + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id - 1 + _mMapTilesX));//top left
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id + 1 + _mMapTilesX) < _mMapTilesX * _mMapTilesY)
        {
            neighbours.push_back(_mMapNodes.at(id + 1 + _mMapTilesX));//top right
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id - 1 - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id - 1 - _mMapTilesX));//bottom left
            neighbours.back().previousNodePAth = current.id;
        }
        if ((id + 1 - _mMapTilesX) > -1)
        {
            neighbours.push_back(_mMapNodes.at(id + 1 - _mMapTilesX));//bottom right
            neighbours.back().previousNodePAth = current.id;
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
                int tempG = current.gCost + sqrt(pow(neighbours[i].position.x - current.position.x, 2) +
                    pow(neighbours[i].position.y - current.position.y, 2));;
                
                if (!std::count(openIDs.begin(), openIDs.end(), neighbours[i].id))
                {

                    openList.push_back(neighbours[i]);
                    
                }
                //else if in closed list then open list includes neighbour
                else if(tempG < neighbours[i].gCost)
                {
                    neighbours[i].gCost = tempG;
                }

                //finds distance between current and end position
                //sets f and h cost and sets previours node as current for path creation
                neighbours[i].gCost = tempG;
                neighbours[i].hCost = sqrt(pow(neighbours[i].position.x - _mEnd.x, 2) +
                    pow(neighbours[i].position.y - _mEnd.y, 2));
                neighbours[i].fCost = neighbours[i].gCost + neighbours[i].hCost;
                neighbours[i].previousNodePAth = current.id;
                
            }

               
        }
    }

    std::cout << "fail" << std::endl;
    return startPos;

}

//sets new path points
void AStar::SetPathPoints(glm::vec2 endPoint)
{
    _mEnd = endPoint;
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






