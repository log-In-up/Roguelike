#pragma once
#include <memory>
#include <vector>

#include "Labyrinth.h"
#include "Vector.h"

namespace Roguelike
{
class LabyrinthBuilder
{
  public:
    struct Parameters
    {
        int width;
        int height;
        bool isAdjustingSizeAndStart;
        int randSeed = -1;
        GameEngine::Vector2Di startPosition = {-1, -1};
    };

    enum class TileType
    {
        Empty,
        Floor,
        Wall,
        Exit,
        VerticalWall,
        HorizontalWall
    };

    struct RectFillingParameters
    {
        GameEngine::Vector2Di bottomLeft;
        GameEngine::Vector2Di size;
        TileType borderTileType;
        TileType fillingTileType;
    };

    LabyrinthBuilder();

    const GameEngine::Vector2Di &GetExitCell() const;
    GameEngine::Vector2Di GetTileSize() const;
    int GetUsedSeed() const;
    std::shared_ptr<Labyrinth> ConstructLabyrinth();
    void AddFloorRect(GameEngine::Vector2Di bottomLeft, GameEngine::Vector2Di size);
    void AddRect(const RectFillingParameters &parameters);
    void Generate(const Parameters &parameters);
    void SetExitCell(const GameEngine::Vector2Di &newExitCell);
    void SetFloor(GameEngine::Vector2Di position);
    void SetWall(GameEngine::Vector2Di position);
    void StartBuilding(const GameEngine::Vector2Di &newTileSize, const TileType fillTileType = TileType::Empty);

  private:
    int labyrinthTileWidth = 0;
    int labyrinthTileHeight = 0;
    int usedSeed = -1;
    std::vector<std::vector<TileType>> tileGrid;
    std::vector<int> usableFloorTextureId;
    GameEngine::Vector2Di startPosition;
    GameEngine::Vector2Di exitCell;
    std::vector<GameEngine::Vector2Di> deadEnds;

    bool IsWall(GameEngine::Vector2Di position) const;
    GameEngine::Vector2Df GetCenterInTiles() const;
    GameEngine::Vector2Df GetTilePosition(GameEngine::Vector2Di tilePosition);
    std::vector<GameEngine::Vector2Di> GetAvaliableDirections(
        const GameEngine::Vector2Di &currentCell, const std::vector<std::vector<bool>> &visitiedCells) const;
    void AdjustStartPointAndSize();
    void FindAndEmplaceExit();
    void ProcessMiddleCell(const GameEngine::Vector2Di &middleCell, std::vector<std::vector<bool>> &visited,
                           const GameEngine::Vector2Di &selectedDirection);
    void RandomlyEmplaceExit();
    void UpdateWallType();
};
} // namespace Roguelike
