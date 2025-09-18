#include "pch.h"

#include "SpriteDirectionComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
SpriteDirectionComponent::SpriteDirectionComponent(GameObject *gameObject) : Component(gameObject)
{
}

void SpriteDirectionComponent::Update(float deltaTime)
{
    auto renderer = rendererPointer.lock();
    auto input = inputPointer.lock();

    if (input && renderer)
    {
        if (input->GetHorizontalAxis() > 0)
        {
            renderer->FlipX(true ^ renderer->IsTextureRightDirected());
        }
        else if (input->GetHorizontalAxis() < 0)
        {
            renderer->FlipX(false ^ renderer->IsTextureRightDirected());
        }
    }
    else
    {
        rendererPointer = gameObject->GetComponentSharedPtr<SpriteRendererComponent>();
        inputPointer = gameObject->GetComponentSharedPtr<InputComponent>();
    }
}
} // namespace GameEngine