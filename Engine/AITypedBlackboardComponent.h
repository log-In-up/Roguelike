#pragma once
#include <string>
#include <tuple>
#include <unordered_map>

#include "Component.h"

namespace GameEngine
{
template <typename... ValueTypes> class AITypedBlackboardComponent : public Component
{
  public:
    template <typename T> using MapType = std::unordered_map<std::string, T>;
    using Data = std::tuple<MapType<ValueTypes>...>;

    explicit AITypedBlackboardComponent(GameObject *gameObject) : Component(gameObject) {};

    void Update(float deltaTime) override {};

    template <typename T> void Set(std::string key, const T &value)
    {
        std::get<MapType<T>>(data)[key] = value;
    }

    template <typename T> bool Get(std::string key, T &outValue) const
    {
        auto &map = std::get<MapType<T>>(data);
        auto foundIt = map.find(key);
        if (foundIt == map.end())
        {
            return false;
        }
        outValue = foundIt->second;
        return true;
    }

  protected:
    Data data;
};
} // namespace GameEngine
