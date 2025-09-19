#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Texture.hpp>

#include "Component.h"
#include "GameObject.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
struct Animation
{
    std::string textureMapName;
    std::vector<int> frameIDs;
    float time = 0.0F;
    bool isRightDirected = true;
    int priority = 0;
    bool isLoop = false;
};

class SpriteAnimationComponent : public Component
{
  public:
    explicit SpriteAnimationComponent(GameObject *gameObject);

    void Update(float deltaTime) override;

    void AddAnimation(const std::string &animationName, const Animation &animation, bool isDefault = false);
    void RemoveAnimation(const std::string &animationName);
    void StartAnimation(const std::string &animationName, const bool ignorePriority = false);

  protected:
    void ResetAnimation();
    void StartCurrentAnimation();
    void UpdateRenderTexture() const;

    std::unordered_map<std::string, Animation> animations;
    std::string defaultAnimationName;
    std::string currentAnimationName;
    std::vector<const sf::Texture *> framesTextures;
    std::weak_ptr<SpriteRendererComponent> rendererComponent;
    float timePerFrame = 0.0F;
    float timer = 0.0F;
    int currentFrame = 0;
    bool isRigthDirected = true;
    bool isLoop = true;
};
} // namespace GameEngine