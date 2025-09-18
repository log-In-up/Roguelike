#pragma once

#include "GameObject.h"
#include "InputComponent.h"
#include "Vector.h"

namespace Roguelike
{
class AIInputComponent : public GameEngine::InputComponent
{
  public:
    explicit AIInputComponent(GameEngine::GameObject *gameObject);

    void Update(float deltaTime) override;

    GameEngine::Vector2Df GetDirection() const;
    void SetDirection(const GameEngine::Vector2Df &newDirection);
};
} // namespace Roguelike
