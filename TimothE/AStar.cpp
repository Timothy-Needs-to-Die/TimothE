#include "AStar.h"

glm::vec3 AStar::PathFinding(glm::vec3 startPos)
{
    std::vector<glm::vec3> openList;
    std::vector<glm::vec3> closedList;
    openList.push_back(startPos);
    int f = 0;

    while (openList.size() > 0)
    {
        glm::vec3 current = startPos;
        for (int i = 0; i < openList.size(); i++)
        {

        }
    }

    return glm::vec3(1.0f);
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
    _mMapTiles = mapTiles;
    _mMapTilesX = sizeX;
    _mMapTilesY = sizeY;
}

int AStar::CalculateDistance(Node nodeA, Node nodeB)
{
    int distX = std::abs(nodeA.position.x - nodeB.position.x);
    int distY = std::abs(nodeA.position.y - nodeB.position.y);
    if (distX > distY)
    {
        return 14 * distY + 10 * (distX - distY);
    }
    return 14 * distX + 10 * (distY - distX);
}

std::vector<glm::vec3> AStar::GetNeighbours(Node node)
{
    std::vector<glm::vec3> neighbours;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }
            int checkX = node.position.x;
            int checkY = node.position.y;
            if (checkX >= 0 && checkX < _mMapTilesX && checkY >= 0 && checkY < _mMapTilesY)
            {
                neighbours.push_back({ checkX,checkY,0 });
            }
        }
    }
    return neighbours;
}




