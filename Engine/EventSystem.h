#pragma once
#include <memory>
#include <unordered_map>
#include <utility>

#include <SFML/Window/Event.hpp>

namespace GameEngine
{
class EventSystem
{
  public:
    using ConstIterator = std::unordered_multimap<sf::Event::EventType, sf::Event>::const_iterator;

    static std::shared_ptr<EventSystem> Instance();

    const std::unordered_multimap<sf::Event::EventType, sf::Event> &GetSfEvents() const;
    std::pair<ConstIterator, ConstIterator> GetSfEvents(const sf::Event::EventType type) const;
    void UpdateSfEvents();

  private:
    EventSystem() = default;
    ~EventSystem() = default;
    EventSystem(const EventSystem &) = delete;
    EventSystem &operator=(const EventSystem &) = delete;
    std::unordered_multimap<sf::Event::EventType, sf::Event> sfEvents;
};
} // namespace GameEngine
