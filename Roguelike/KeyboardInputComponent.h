#pragma once

#include "GameObject.h"
#include "InputComponent.h"

namespace Roguelike
{
class KeyboardInputComponent : public GameEngine::InputComponent
{
  public:
    explicit KeyboardInputComponent(GameEngine::GameObject *gameObject);

    void Update(float deltaTime) override;

  private:
    bool logInput = false;
};
} // namespace Roguelike
