#include "HealthBarComponent.h"

#include <memory>

#include "BarComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "IObserver.h"

namespace Roguelike
{
HealthBarComponent::HealthBarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters,
                                       const int renderLayer)
    : BarComponent(gameObject, parameters, renderLayer)
{
}

void HealthBarComponent::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    auto lockedHealthComponent = healthComponent.lock();
    if (lockedHealthComponent && lockedHealthComponent == std::dynamic_pointer_cast<HealthComponent>(observable))
    {
        maxAmount = lockedHealthComponent->GetMaxHealth();
        currentAmount = lockedHealthComponent->GetCurrentHealth();
    }
}

void HealthBarComponent::Render()
{
    if (!healthComponent.expired())
    {
        BarComponent::Render();
    }
}

void HealthBarComponent::Update(float deltTime)
{
}

std::weak_ptr<HealthComponent> HealthBarComponent::GetHealthComponent() const
{
    return healthComponent;
}

void HealthBarComponent::SetHealthComponent(std::shared_ptr<HealthComponent> newHealthComponent)
{
    newHealthComponent->AddObserver(weak_from_this());
    healthComponent = newHealthComponent;
    maxAmount = newHealthComponent->GetMaxHealth();
    currentAmount = newHealthComponent->GetCurrentHealth();
}
} // namespace Roguelike