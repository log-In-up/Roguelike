#include "pch.h"

#include "SpriteAnimationComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
SpriteAnimationComponent::SpriteAnimationComponent(GameObject *gameObject) : Component(gameObject)
{
    rendererComponent = gameObject->GetComponentSharedPtr<SpriteRendererComponent>();

    if (rendererComponent.expired())
    {
        gameObject->RemoveComponent(this);
        return;
    }
}

void SpriteAnimationComponent::Update(float deltaTime)
{
    timer += deltaTime;

    if (timer >= timePerFrame)
    {
        timer = 0.0F;
        currentFrame++;
        if (currentFrame >= framesTextures.size())
        {
            if (isLoop)
            {
                ResetAnimation();
            }
            else
            {
                currentAnimationName = defaultAnimationName;
                StartCurrentAnimation();
            }
        }

        UpdateRenderTexture();
    }
}

void SpriteAnimationComponent::AddAnimation(const std::string &animationName, const Animation &animation,
                                            bool isDefault)
{
    animations[animationName] = animation;
    if (isDefault || defaultAnimationName.empty())
    {
        defaultAnimationName = animationName;
    }
}

void SpriteAnimationComponent::RemoveAnimation(const std::string &animationName)
{
    auto animationIterator = animations.find(animationName);
    if (animationIterator != animations.end())
    {
        animations.erase(animationIterator);
    }
}

void GameEngine::SpriteAnimationComponent::StartAnimation(const std::string &animationName, const bool ignorePriority)
{
    auto newAnimationFind = animations.find(animationName);
    if (newAnimationFind != animations.end())
    {
        if (animationName != currentAnimationName)
        {
            auto currentAnimationFind = animations.find(currentAnimationName);
            if (ignorePriority || currentAnimationFind == animations.end() ||
                currentAnimationFind->second.priority <= newAnimationFind->second.priority)
            {
                currentAnimationName = animationName;
                StartCurrentAnimation();
            }
        }
    }
}

void SpriteAnimationComponent::ResetAnimation()
{
    timer = 0.0F;
    currentFrame = 0;
    UpdateRenderTexture();
}

void SpriteAnimationComponent::StartCurrentAnimation()
{
    auto animationIter = animations.find(currentAnimationName);
    if (animationIter != animations.end())
    {
        auto &animation = animationIter->second;

        framesTextures.clear();
        framesTextures.reserve(animation.frameIDs.size());
        for (auto &frameID : animation.frameIDs)
        {
            framesTextures.push_back(
                ResourceSystem::Instance()->GetTextureMapElementShared(animation.textureMapName, frameID));
        }
        isRigthDirected = animation.isRightDirected;

        timePerFrame = animation.time / static_cast<float>(animation.frameIDs.size());
        isLoop = animation.isLoop;

        ResetAnimation();
    }
}

void SpriteAnimationComponent::UpdateRenderTexture() const
{
    auto renderer = rendererComponent.lock();
    if (renderer != nullptr && currentFrame < framesTextures.size() && framesTextures[currentFrame] != nullptr)
    {
        renderer->SetTexture(*framesTextures[currentFrame], isRigthDirected);
    }
}
} // namespace GameEngine