#include "pch.h"

#include "EventSystem.h"

#include <memory>
#include <unordered_map>
#include <utility>

#include <SFML/Window/Event.hpp>

#include "RenderSystem.h"

namespace GameEngine
{
std::shared_ptr<EventSystem> EventSystem::Instance()
{
    const static std::shared_ptr<EventSystem> instance =
        std::shared_ptr<EventSystem>(new EventSystem(), [](EventSystem *) {});
    return instance;
}

const std::unordered_multimap<sf::Event::EventType, sf::Event> &EventSystem::GetSfEvents() const
{
    return sfEvents;
}

std::pair<EventSystem::ConstIterator, EventSystem::ConstIterator> EventSystem::GetSfEvents(
    const sf::Event::EventType type) const
{
    return sfEvents.equal_range(type);
}

void EventSystem::UpdateSfEvents()
{
    sfEvents.clear();
    auto &window = RenderSystem::Instance()->GetMainWindow();
    sf::Event event;
    while (window.pollEvent(event))
    {
        sfEvents.insert(std::pair<sf::Event::EventType, sf::Event>(event.type, event));
    }
}
} // namespace GameEngine