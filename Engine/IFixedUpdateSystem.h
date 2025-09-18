#pragma once

namespace GameEngine
{
class IFixedUpdateSystem
{
  public:
    static constexpr float defaultFixedUpdateTime = 0.015F;
    IFixedUpdateSystem();

    virtual ~IFixedUpdateSystem();

    virtual void Update() = 0;

    float GetFixedUpdateTime() const;
    void SetFixedUpdateTime(const float newFixedUpdateTime);

  protected:
    float fixedUpdateTime = defaultFixedUpdateTime;
};
} // namespace GameEngine
