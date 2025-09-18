#include "Settings.h"

#include "DefaultActorsSettings.h"
#include "LevelCompleteCondition.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike
{
const SettingsStruct Settings::defaultsSettings{
    .screenWidth = 1280,
    .screenHeight = 720,
    .gameName = L"Roguelike",

    .resourcesPath = "Resources\\",
    .soundPath = "Resources\\Sounds\\",
    .fontPath = "Resources\\Fonts\\",
    .texturePath = "Resources\\Textures\\",
    .textureMapsPath = "Resources\\TextureMaps\\",

    .playerTextureMap = {.name = "PlayerTextures",
                         .sourcePath = "Resources\\TextureMaps\\Player.png",
                         .elementPixelSize = {100, 100},
                         .totalElements = 63,
                         .isSmooth = true},
    .enemyTextureMap = {.name = "EnemyTextures",
                        .sourcePath = "Resources\\TextureMaps\\Enemy.png",
                        .elementPixelSize = {100, 100},
                        .totalElements = 48,
                        .isSmooth = false},
    .wallTextureMap = {.name = "WallTextures",
                       .sourcePath = "Resources\\TextureMaps\\Wall.png",
                       .elementPixelSize = {16, 16},
                       .totalElements = 48,
                       .isSmooth = false},
    .floorTextureMap = {.name = "FloorTextures",
                        .sourcePath = "Resources\\TextureMaps\\Floor.png",
                        .elementPixelSize = {16, 16},
                        .totalElements = 49,
                        .isSmooth = false},

    .playerParameters = DefaultSettings::defaultPlayerParameters,
    .aiParameters = DefaultSettings::AIActorParameters,

    .mapTileSize = 150,
    .firstLevelParameters =
        {.builderParameters = {.width = 7, .height = 7, .isAdjustingSizeAndStart = true, .randSeed = -1},
         .completeConditions = {LevelCompleteCondition::Type::ExitReached,
                                LevelCompleteCondition::Type::AllEnemyKilled},
         .enemyCount = 1},
    .timeToRemoveAfterDeath = 4.0F};

GameEngine::Vector2Df Settings::ScreenCenter() const
{
    return Half(ScreenSize());
}

GameEngine::Vector2Df Settings::ScreenSize() const
{
    return GameEngine::Vector2Df({static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
} // namespace Roguelike