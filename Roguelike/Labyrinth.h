#pragma once
#include <memory>
#include <vector>

#include "Floor.h"
#include "GameObjectContainer.h"
#include "LabyrinthElement.h"
#include "LabyrinthExit.h"
#include "Rect.h"
#include "Vector.h"
#include "Wall.h"

namespace Roguelike
{
class Labyrinth : public GameObjectContainer
{
  public:
    friend class LabyrinthBuilder;

    const GameEngine::FloatRect GetLabyrinthCoodinatesRect();
    const GameEngine::Vector2Df GetCellCoordinates(const GameEngine::Vector2Di &cell);
    const GameEngine::Vector2Di &GetStartCell() const;
    const std::vector<GameEngine::Vector2Di> &GetGenerationDeadEnds() const;
    const std::vector<std::vector<bool>> &GetIsTileWalkable() const;
    const std::vector<std::vector<std::shared_ptr<LabyrinthElement>>> &GetElements() const;
    std::shared_ptr<LabyrinthExit> &GetExit();
    std::vector<std::weak_ptr<Floor>> GetFloors() const;
    std::vector<std::weak_ptr<Wall>> GetWalls() const;
    void SetCenterPosition(const GameEngine::Vector2Df newPosition);

  private:
    explicit Labyrinth(const GameEngine::Vector2Di &size);

    GameEngine::Vector2Di size;
    std::vector<std::vector<std::shared_ptr<LabyrinthElement>>> elements;
    std::shared_ptr<LabyrinthExit> exit;
    std::vector<GameEngine::Vector2Di> generationDeadEnd;
    std::vector<std::vector<bool>> isTileWalkable;
    GameEngine::Vector2Di startCell;
};
} // namespace Roguelike
