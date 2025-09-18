#pragma once
namespace GameEngine
{
class ColliderComponent;
struct Trigger
{
  public:
    Trigger(ColliderComponent *first, ColliderComponent *second) : first(first), second(second) {};
    ColliderComponent *first;
    ColliderComponent *second;
};
} // namespace GameEngine
