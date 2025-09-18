#pragma once
#include <memory>

#include "Component.h"
#include "IRenderable.h"
#include "PerceptionComponent.h"

namespace Roguelike
{
class PerceptionComponentDebugDraw : public GameEngine::Component, public GameEngine::IRenderable
{
  public:
    static constexpr int defaultArcLineCount = 50;
    explicit PerceptionComponentDebugDraw(GameEngine::GameObject *gameObject, const int layer = 0,
                                          const int arcLinesCount = defaultArcLineCount);

    void Render() override;
    void Update(float deltaTime) override;

    int GetArcPointCount() const;
    void SetArcPointCount(const int newArcPointsCount);

  protected:
    std::weak_ptr<PerceptionComponent> perceptionComponent;
    int arcLinesCount;
};
} // namespace Roguelike