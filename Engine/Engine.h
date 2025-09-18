#pragma once

namespace GameEngine
{
class Engine
{
  public:
    static Engine *Instance();

    void Run();

  private:
    Engine();
    ~Engine() = default;
    Engine(const Engine &app) = delete;
    Engine &operator=(const Engine &) = delete;
};
} // namespace GameEngine
