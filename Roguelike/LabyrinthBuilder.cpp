#include "LabyrinthBuilder.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

#include "Floor.h"
#include "Labyrinth.h"
#include "LabyrinthExit.h"
#include "Logger.h"
#include "Settings.h"
#include "TransformComponent.h"
#include "Utility.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike
{
enum class TileType
{
};

LabyrinthBuilder::LabyrinthBuilder()
{
    usableFloorTextureId.push_back(0);
    usableFloorTextureId.push_back(1);
    usableFloorTextureId.push_back(2);
    usableFloorTextureId.push_back(8);
    usableFloorTextureId.push_back(10);
    exitCell = {-1, -1};
}

const GameEngine::Vector2Di &LabyrinthBuilder::GetExitCell() const
{
    return exitCell;
}

GameEngine::Vector2Di LabyrinthBuilder::GetTileSize() const
{
    return GameEngine::Vector2Di(labyrinthTileWidth, labyrinthTileHeight);
}

int LabyrinthBuilder::GetUsedSeed() const
{
    return usedSeed;
}

std::shared_ptr<Labyrinth> LabyrinthBuilder::ConstructLabyrinth()
{
    auto *settings = Settings::Instance();

    std::shared_ptr<Labyrinth> labyrinth =
        std::shared_ptr<Labyrinth>(new Labyrinth(GameEngine::Vector2Di(labyrinthTileWidth, labyrinthTileHeight)));

    labyrinth->startCell = startPosition;
    labyrinth->generationDeadEnd = deadEnds;
    auto *labyrinthTransform = labyrinth->GetGameObject()->GetComponent<GameEngine::TransformComponent>();

    UpdateWallType();

    for (int i = 0; i < tileGrid.size(); ++i)
    {
        for (int j = 0; j < tileGrid[i].size(); ++j)
        {
            if (IsWall(GameEngine::Vector2Di(i, j)))
            {
                labyrinth->isTileWalkable[i][j] = false;
                int textureId = 0;

                switch (tileGrid[i][j])
                {
                case TileType::HorizontalWall:
                    textureId = 36;
                    break;
                case TileType::VerticalWall:
                    textureId = 4;
                    break;
                default:
                    break;
                }
                auto wall = std::make_shared<Wall>(labyrinthTransform->GetWorldPosition(), textureId,
                                                   GameEngine::Vector2Di(settings->mapTileSize, settings->mapTileSize));

                auto *wallTransform = wall->GetGameObject()->GetComponent<GameEngine::TransformComponent>();
                wallTransform->SetParent(labyrinthTransform);
                wallTransform->SetLocalPosition(GetTilePosition({i, j}));
                labyrinth->elements[i][j] = wall;
            }
            else if (tileGrid[i][j] == TileType::Floor)
            {
                labyrinth->isTileWalkable[i][j] = true;
                const int textureId = usableFloorTextureId[rand() % usableFloorTextureId.size()];

                auto floor =
                    std::make_shared<Floor>(labyrinthTransform->GetWorldPosition(), textureId,
                                            GameEngine::Vector2Di(settings->mapTileSize, settings->mapTileSize));

                auto *floorTransform = floor->GetGameObject()->GetComponent<GameEngine::TransformComponent>();

                floorTransform->SetParent(labyrinthTransform);
                floorTransform->SetLocalPosition(GetTilePosition({i, j}));
                labyrinth->elements[i][j] = floor;
            }
            else if (tileGrid[i][j] == TileType::Exit)
            {
                labyrinth->isTileWalkable[i][j] = true;
                const int textureId = 16;
                auto exit = std::make_shared<LabyrinthExit>(
                    labyrinthTransform->GetWorldPosition(), textureId,
                    GameEngine::Vector2Di(settings->mapTileSize, settings->mapTileSize));

                auto *exitTransform = exit->GetGameObject()->GetComponent<GameEngine::TransformComponent>();
                exitTransform->SetParent(labyrinthTransform);
                exitTransform->SetLocalPosition(GetTilePosition({i, j}));
                labyrinth->elements[i][j] = exit;
                labyrinth->exit = exit;
            }
        }
    }
    return labyrinth;
}

void Roguelike::LabyrinthBuilder::AddFloorRect(GameEngine::Vector2Di bottomLeft, GameEngine::Vector2Di size)
{
    AddRect(RectFillingParameters(bottomLeft, size, TileType::Wall, TileType::Floor));
}

void LabyrinthBuilder::AddRect(const RectFillingParameters &parameters)
{
    const GameEngine::Vector2Di bottomLeft = {std::clamp(parameters.bottomLeft.x, 0, labyrinthTileWidth),
                                              std::clamp(parameters.bottomLeft.y, 0, labyrinthTileHeight)};

    const GameEngine::Vector2Di size = {std::clamp(parameters.size.x, 0, labyrinthTileWidth - bottomLeft.x),
                                        std::clamp(parameters.size.y, 0, labyrinthTileWidth - bottomLeft.y)};

    const GameEngine::Vector2Di topRight = bottomLeft + size - GameEngine::Vector2Di(1, 1);

    for (int i = bottomLeft.x; i <= topRight.x; ++i)
    {
        if (tileGrid[i][bottomLeft.y] != parameters.fillingTileType)
        {
            tileGrid[i][bottomLeft.y] = parameters.borderTileType;
        }
        if (tileGrid[i][topRight.y] != parameters.fillingTileType)
        {
            tileGrid[i][topRight.y] = parameters.borderTileType;
        }
    }

    for (int i = bottomLeft.y; i <= topRight.y; ++i)
    {
        if (tileGrid[bottomLeft.x][i] != parameters.fillingTileType)
        {
            tileGrid[bottomLeft.x][i] = parameters.borderTileType;
        }
        if (tileGrid[topRight.x][i] != parameters.fillingTileType)
        {
            tileGrid[topRight.x][i] = parameters.borderTileType;
        }
    }

    for (int i = bottomLeft.x + 1; i < topRight.x; ++i)
    {
        for (int j = bottomLeft.y + 1; j < topRight.y; ++j)
        {
            tileGrid[i][j] = parameters.fillingTileType;
        }
    }
}

void LabyrinthBuilder::Generate(const Parameters &parameters)
{
    usedSeed = parameters.randSeed == -1 ? static_cast<unsigned int>(std::time(nullptr)) : parameters.randSeed;
    std::srand(usedSeed);

    StartBuilding({parameters.width, parameters.height}, TileType::Wall);

    if (parameters.startPosition.x < 0 || parameters.startPosition.y < 0)
    {
        startPosition = {1 + (std::rand() % (labyrinthTileWidth - 2)), 1 + (std::rand() % (labyrinthTileHeight - 2))};
    }
    else
    {
        startPosition = parameters.startPosition;
    }
    if (parameters.isAdjustingSizeAndStart)
    {
        AdjustStartPointAndSize();
    }
    std::vector<std::vector<bool>> visited;
    visited.resize(labyrinthTileWidth, std::vector<bool>(labyrinthTileHeight, false));

    std::stack<GameEngine::Vector2Di> cellStack;
    cellStack.push(startPosition);

    while (!cellStack.empty())
    {
        const auto currentCell = cellStack.top();
        cellStack.pop();

        auto availiableDirections = GetAvaliableDirections(currentCell, visited);
        if (!availiableDirections.empty())
        {
            cellStack.push(currentCell);
            const auto &selectedDirection = availiableDirections[std::rand() % availiableDirections.size()];

            const GameEngine::Vector2Di newCell = currentCell + selectedDirection;
            cellStack.push(newCell);

            const GameEngine::Vector2Di middleCell = {(newCell.x + currentCell.x) / 2, (newCell.y + currentCell.y) / 2};
            ProcessMiddleCell(middleCell, visited, selectedDirection);
        }
        else
        {
            if (!visited[currentCell.x][currentCell.y])
            {
                deadEnds.push_back(currentCell);
            }
        }
        visited[currentCell.x][currentCell.y] = true;
        tileGrid[currentCell.x][currentCell.y] = TileType::Floor;
    }
    FindAndEmplaceExit();
}

void LabyrinthBuilder::SetExitCell(const GameEngine::Vector2Di &newExitCell)
{
    if (InRect({0, 0}, {labyrinthTileWidth, labyrinthTileHeight}, newExitCell))
    {
        exitCell = newExitCell;
    }
    else
    {
        LOG_WARN("newExitCell must be in Labyrinth rect. Data not changed");
    }
}

void LabyrinthBuilder::SetFloor(GameEngine::Vector2Di position)
{
    if (InRect(GameEngine::Vector2Di(), GetTileSize(), position))
    {
        tileGrid[position.x][position.y] = TileType::Floor;
    }
}

void LabyrinthBuilder::SetWall(GameEngine::Vector2Di position)
{
    if (InRect(GameEngine::Vector2Di(), GetTileSize(), position))
    {
        tileGrid[position.x][position.y] = TileType::Wall;
    }
}

void LabyrinthBuilder::StartBuilding(const GameEngine::Vector2Di &newTileSize, const TileType fillTileType)
{
    exitCell = {-1, -1};
    labyrinthTileWidth = newTileSize.x;
    labyrinthTileHeight = newTileSize.y;
    tileGrid = std::vector<std::vector<TileType>>(labyrinthTileWidth,
                                                  std::vector<TileType>(labyrinthTileHeight, fillTileType));
}

bool LabyrinthBuilder::IsWall(GameEngine::Vector2Di position) const
{
    if (InRect(GameEngine::Vector2Di(), GetTileSize(), position))
    {
        switch (tileGrid[position.x][position.y])
        {
        case TileType::Wall:
            return true;
            break;
        case TileType::HorizontalWall:
            return true;
            break;
        case TileType::VerticalWall:
            return true;
            break;
        case TileType::Empty:
            return false;
            break;
        case TileType::Floor:
            return false;
            break;
        default:
            return false;
            break;
        }
    }
    else
    {
        return false;
    }
}

GameEngine::Vector2Df LabyrinthBuilder::GetCenterInTiles() const
{
    const GameEngine::Vector2Df oneVector(1.0F, 1.0F);
    return Half((GameEngine::Convert<GameEngine::Vector2Df, GameEngine::Vector2Di>(GetTileSize()) - oneVector));
}

GameEngine::Vector2Df LabyrinthBuilder::GetTilePosition(GameEngine::Vector2Di tilePosition)
{
    auto *settings = Settings::Instance();
    auto position =
        GameEngine::Convert<GameEngine::Vector2Df, GameEngine::Vector2Di>(tilePosition) - GetCenterInTiles();
    position *= static_cast<float>(settings->mapTileSize);
    return position;
}

std::vector<GameEngine::Vector2Di> LabyrinthBuilder::GetAvaliableDirections(
    const GameEngine::Vector2Di &currentCell, const std::vector<std::vector<bool>> &visitiedCells) const
{
    const std::vector<GameEngine::Vector2Di> directions{
        {0, -2}, // Up
        {2, 0},  // Right
        {0, 2},  // Down
        {-2, 0}  // Left
    };
    const GameEngine::Vector2Di interiorLabyrinthTopLeft = {1, 1};
    const GameEngine::Vector2Di interiorLabyrinthBottomRight = {labyrinthTileWidth - 2, labyrinthTileHeight - 2};
    std::vector<GameEngine::Vector2Di> availableDirections;

    for (const auto &direction : directions)
    {
        auto possibleCell = currentCell + direction;

        if (InRect(interiorLabyrinthTopLeft, interiorLabyrinthBottomRight, possibleCell) &&
            !visitiedCells[possibleCell.x][possibleCell.y])
        {
            availableDirections.push_back(direction);
        }
    }
    return availableDirections;
}

void Roguelike::LabyrinthBuilder::AdjustStartPointAndSize()
{
    labyrinthTileWidth += labyrinthTileWidth % 2 == 0 ? 1 : 0;
    labyrinthTileHeight += labyrinthTileHeight % 2 == 0 ? 1 : 0;
    startPosition.x += startPosition.x % 2 == 0 ? 1 : 0;
    startPosition.y += startPosition.y % 2 == 0 ? 1 : 0;
}

void LabyrinthBuilder::FindAndEmplaceExit()
{
    std::multimap<float, GameEngine::Vector2Di> deadEndsNearEdge;
    for (const auto &deadEnd : deadEnds)
    {
        if (deadEnd.x == 1 || deadEnd.x == labyrinthTileWidth - 2 || deadEnd.y == 1 ||
            deadEnd.y == labyrinthTileHeight - 2)
        {
            deadEndsNearEdge.insert(std::pair<float, GameEngine::Vector2Di>(
                (Convert<GameEngine::Vector2Df>(deadEnd - startPosition)).GetLength(), deadEnd));
        }
    }

    auto cellNearExit = deadEndsNearEdge.crbegin();
    if (cellNearExit != deadEndsNearEdge.crend())
    {
        auto exitCell = cellNearExit->second;
        tileGrid[exitCell.x][exitCell.y] = TileType::Exit;
    }
    else
    {
        RandomlyEmplaceExit();
    }
}

void LabyrinthBuilder::ProcessMiddleCell(const GameEngine::Vector2Di &middleCell,
                                         std::vector<std::vector<bool>> &visited,
                                         const GameEngine::Vector2Di &selectedDirection)
{
    visited[middleCell.x][middleCell.y] = true;
    tileGrid[middleCell.x][middleCell.y] = TileType::Floor;

    if (selectedDirection.y == 0)
    {
        if (middleCell.y - 1 > 0)
        {
            visited[middleCell.x][middleCell.y - 1] = true;
            tileGrid[middleCell.x][middleCell.y - 1] = TileType::Wall;
        }

        if (middleCell.y + 1 < labyrinthTileHeight)
        {
            visited[middleCell.x][middleCell.y + 1] = true;
            tileGrid[middleCell.x][middleCell.y + 1] = TileType::Wall;
        }
    }
    else
    {
        if (middleCell.x - 1 > 0)
        {
            visited[middleCell.x - 1][middleCell.y] = true;
            tileGrid[middleCell.x - 1][middleCell.y] = TileType::Wall;
        }
        if (middleCell.x + 1 < labyrinthTileHeight)
        {
            visited[middleCell.x + 1][middleCell.y] = true;
            tileGrid[middleCell.x + 1][middleCell.y] = TileType::Wall;
        }
    }
}

void LabyrinthBuilder::RandomlyEmplaceExit()
{
    const GameEngine::Vector2Di zeroVector = {0, 0};
    GameEngine::Vector2Di exitCell = zeroVector;
    while (exitCell == zeroVector)
    {
        const int xCoordinate = 1 + (std::rand() % (labyrinthTileWidth - 1));
        const int yCoordinate = 1 + (std::rand() % (labyrinthTileHeight - 1));

        enum Edge
        {
            Up,
            Right,
            Down,
            Left
        };
        const Edge randomEdge = static_cast<Edge>(std::rand() % 4);

        switch (randomEdge)
        {
        case Up:
            if (tileGrid[xCoordinate][1] == TileType::Floor)
            {
                exitCell = {xCoordinate, 1};
            }
            break;
        case Down:
            if (tileGrid[xCoordinate][labyrinthTileHeight - 2] == TileType::Floor)
            {
                exitCell = {xCoordinate, labyrinthTileHeight - 2};
            }
            break;
        case Left:
            if (tileGrid[1][yCoordinate] == TileType::Floor)
            {
                exitCell = {1, yCoordinate};
            }
            break;
        case Right:
            if (tileGrid[labyrinthTileWidth - 2][yCoordinate] == TileType::Floor)
            {
                exitCell = {labyrinthTileWidth - 2, yCoordinate};
            }
            break;
        }
    }
    tileGrid[exitCell.x][exitCell.y] = TileType::Exit;
}

void LabyrinthBuilder::UpdateWallType()
{
    const GameEngine::Vector2Di toLeft(-1, 0);
    const GameEngine::Vector2Di toRight(1, 0);
    const GameEngine::Vector2Di toUp(0, -1);
    const GameEngine::Vector2Di toBottom(0, 1);
    for (int i = 0; i < tileGrid.size(); ++i)
    {
        for (int j = 0; j < tileGrid[i].size(); ++j)
        {
            const GameEngine::Vector2Di currentPosition(i, j);
            if (IsWall(currentPosition))
            {
                if (IsWall(currentPosition + toUp) || IsWall(currentPosition + toBottom))
                {
                    tileGrid[i][j] = TileType::VerticalWall;
                }
                else
                {
                    tileGrid[i][j] = TileType::HorizontalWall;
                }
            }
        }
    }
}
} // namespace Roguelike