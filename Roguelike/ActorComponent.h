#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Roguelike
{
class ActorComponent : public GameEngine::Component
{
  public:
    explicit ActorComponent(GameEngine::GameObject *gameObject, int groupID = 0);
    ~ActorComponent();

    void Update(float deltaTime) override;

    int GetGroupID() const;
    void SetGroupID(const int newGroupID);

  private:
    int groupID;
};
} // namespace Roguelike
