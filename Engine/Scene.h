#pragma once
namespace GameEngine
{
class Scene
{
  public:
    virtual ~Scene() = default;

    virtual void Restart() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
};
} // namespace GameEngine
