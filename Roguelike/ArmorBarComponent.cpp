#include "ArmorBarComponent.h"

#include <memory>

#include "ArmorComponent.h"
#include "BarComponent.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Roguelike
{
ArmorBarComponent::ArmorBarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters, const int layer)
    : BarComponent(gameObject, parameters, layer)
{
}

void ArmorBarComponent::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    auto lockedArmorComponent = armorComponent.lock();
    if (lockedArmorComponent && lockedArmorComponent == std::dynamic_pointer_cast<ArmorComponent>(observable))
    {
        maxAmount = lockedArmorComponent->GetMaxArmorPoints();
        currentAmount = lockedArmorComponent->GetCurrentArmorPoints();
    }
}

void ArmorBarComponent::Render()
{
    if (!armorComponent.expired())
    {
        BarComponent::Render();
    }
}

void ArmorBarComponent::Update(float deltaTime)
{
}

std::weak_ptr<ArmorComponent> ArmorBarComponent::GetArmorComponent() const
{
    return armorComponent;
}

void ArmorBarComponent::SetArmorComponent(std::shared_ptr<ArmorComponent> newArmorComponent)
{
    newArmorComponent->AddObserver(weak_from_this());
    armorComponent = newArmorComponent;
    maxAmount = newArmorComponent->GetMaxArmorPoints();
    currentAmount = newArmorComponent->GetCurrentArmorPoints();
}
} // namespace Roguelike