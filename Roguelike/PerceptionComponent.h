#pragma once
#include <vector>

#include "Component.h"
#include "IObserver.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
class PerceptionComponent : public GameEngine::Component, public GameEngine::IObservable
{
  public:
    struct Parameters
    {
        float visionAngle;
        float visionRadius;
        float visionDirectionX;
        float visionDirectionY;
        float senseRadius;
    };

    static constexpr Parameters defaultParameters = {.visionAngle = 120.0F,
                                                     .visionRadius = 300.0F,
                                                     .visionDirectionX = 1.0F,
                                                     .visionDirectionY = 0.0F,
                                                     .senseRadius = 100.0F};

    explicit PerceptionComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = defaultParameters);
    ~PerceptionComponent();

    void Update(float deltaTime) override;

    const GameEngine::TransformComponent *GetTransform() const;
    const GameEngine::Vector2Df &GetVisionDirection() const;
    const std::vector<GameEngine::GameObject *> *GetDetectedActors();
    float GetSenseRadius() const;
    float GetVisionAngle() const;
    float GetVisionRadius() const;
    void SetSenseRadius(const float newSenseRadius);
    void SetVisionAngle(const float newVisionAngle);
    void SetVisionDirection(const GameEngine::Vector2Df &newVisionDirection);
    void SetVisionRadius(const float newVisionRadius);
    void UpdateDetectedActors();
    void UpdateDetectedActors(const std::vector<GameEngine::GameObject *> &actors);

  protected:
    GameEngine::TransformComponent *transform;
    GameEngine::Vector2Df visionDirection;
    std::vector<GameEngine::GameObject *> detectedActors;
    float visionAngle;
    float visionRadius;
    float senseRadius;
};
} // namespace Roguelike
