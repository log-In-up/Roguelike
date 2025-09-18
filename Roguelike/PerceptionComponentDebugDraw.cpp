#include "PerceptionComponentDebugDraw.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "Logger.h"
#include "PerceptionComponent.h"
#include "RenderSystem.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike
{
constexpr float fullCircleAngle = 360.0F;

PerceptionComponentDebugDraw::PerceptionComponentDebugDraw(GameEngine::GameObject *gameObject, const int layer,
                                                           const int arcLinesCount)
    : Component(gameObject), IRenderable(layer), arcLinesCount(arcLinesCount)
{
    perceptionComponent = gameObject->GetComponentSharedPtr<PerceptionComponent>();
    if (perceptionComponent.expired())
    {
        LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
        gameObject->RemoveComponent(this);
        return;
    }
}

void PerceptionComponentDebugDraw::Render()
{
    constexpr float outlineThickness = -2.0F;
    if (auto perception = perceptionComponent.lock())
    {
        const auto &position = gameObject->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();

        sf::CircleShape senseZone(perception->GetSenseRadius());
        senseZone.setFillColor(sf::Color::Transparent);
        senseZone.setOutlineColor(sf::Color::Red);
        senseZone.setOutlineThickness(outlineThickness);
        senseZone.setPosition(Convert<sf::Vector2f, GameEngine::Vector2Df>(position));
        auto rect = senseZone.getLocalBounds();
        senseZone.setOrigin(Half(rect.width), Half(rect.height));
        GameEngine::RenderSystem::Instance()->Render(senseZone, layer);

        sf::VertexArray visionDirection(sf::PrimitiveType::LineStrip, 2);
        auto direction = Normalized(perception->GetVisionDirection()) * perception->GetVisionRadius();
        visionDirection[0] = sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position), sf::Color::Green);
        visionDirection[1] =
            sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position + direction), sf::Color::Green);
        GameEngine::RenderSystem::Instance()->Render(visionDirection, layer);

        auto visionAngle = perception->GetVisionAngle();
        if (visionAngle < fullCircleAngle)
        {
            sf::VertexArray visionCone(sf::PrimitiveType::LineStrip);

            visionCone.append(sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position), sf::Color::Yellow));

            Rotate(direction, Half(-visionAngle));

            visionCone.append(
                sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position + direction), sf::Color::Yellow));

            const auto angleStep = visionAngle / static_cast<float>(arcLinesCount);

            for (int i = 0; i < arcLinesCount; ++i)
            {
                Rotate(direction, angleStep);
                visionCone.append(
                    sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position + direction), sf::Color::Yellow));
            }

            visionCone.append(sf::Vertex(Convert<sf::Vector2f, GameEngine::Vector2Df>(position), sf::Color::Yellow));
            GameEngine::RenderSystem::Instance()->Render(visionCone, layer);
        }
        else
        {
            sf::CircleShape visionZone(perception->GetVisionRadius());
            visionZone.setFillColor(sf::Color::Transparent);
            visionZone.setOutlineColor(sf::Color::Yellow);
            visionZone.setOutlineThickness(outlineThickness);
            visionZone.setPosition(Convert<sf::Vector2f, GameEngine::Vector2Df>(position));
            GameEngine::RenderSystem::Instance()->Render(visionZone, layer);
        }
    }
    else
    {
        LOG_WARN("PerceptionComponentDebugDraw needs PerceptionComponent");
    }
}

void PerceptionComponentDebugDraw::Update(float deltaTime)
{
}

int PerceptionComponentDebugDraw::GetArcPointCount() const
{
    return arcLinesCount;
}

void PerceptionComponentDebugDraw::SetArcPointCount(const int newArcPointsCount)
{
    arcLinesCount = newArcPointsCount;
}
} // namespace Roguelike