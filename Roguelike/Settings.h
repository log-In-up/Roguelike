#pragma once
#include <cstdint>
#include <string>

#include "AIActor.h"
#include "Actor.h"
#include "GameLevel.h"
#include "LabyrinthBuilder.h"
#include "ResourceSystem.h"
#include "Vector.h"

namespace Roguelike
{
struct SettingsStruct
{
    int screenWidth;
    int screenHeight;
    std::wstring gameName;

    std::string resourcesPath;
    std::string soundPath;
    std::string fontPath;
    std::string texturePath;
    std::string textureMapsPath;

    GameEngine::ResourceSystem::TextureMapLoadingParameters playerTextureMap;
    GameEngine::ResourceSystem::TextureMapLoadingParameters enemyTextureMap;
    GameEngine::ResourceSystem::TextureMapLoadingParameters wallTextureMap;
    GameEngine::ResourceSystem::TextureMapLoadingParameters floorTextureMap;

    Actor::Parameters playerParameters;
    AIActor::Parameters aiParameters;

    int mapTileSize;

    GameLevel::Parameters firstLevelParameters;
    float timeToRemoveAfterDeath;
};

class Settings : public SettingsStruct
{
  public:
    enum class RenderLayers
    {
        BackGround,
        Floor,
        Walls,
        Actors,
        UI1,
        UI2,
        Debug,
        Count
    };
    static Settings *Instance()
    {
        static Settings world;
        return &world;
    };

    GameEngine::Vector2Df ScreenCenter() const;
    GameEngine::Vector2Df ScreenSize() const;

  private:
    static const SettingsStruct defaultsSettings;
    Settings() : SettingsStruct(defaultsSettings) {};
    ~Settings() = default;
    Settings(const Settings &) = delete;
    Settings operator=(const Settings &) = delete;
};

enum ActorsGroups
{
    PlayerGroup,
    EnemyGroup
};
}; // namespace Roguelike