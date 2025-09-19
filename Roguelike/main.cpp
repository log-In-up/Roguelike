#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#define NOMINMAX
#include <Windows.h> //NOLINT(misc-include-cleaner) : system specific header
#include <stdio.h>
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT

#include <memory>

// #include "DeveloperLevel.h"
#include "Engine.h"
#include "LevelCompleteCondition.h"
#include "LevelManager.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "Settings.h"

int main()
{
    const std::shared_ptr<GameEngine::Logger> globalLogger = std::make_shared<GameEngine::Logger>();
    GameEngine::LoggerRegister::GetInstance().RegisterLogger("Global", globalLogger);
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
    AllocConsole(); // NOLINT(misc-include-cleaner)
    FILE *console;
    freopen_s(&console, "CONOUT$", "w", stdout);
    globalLogger->AddSink(std::make_shared<GameEngine::ConsoleSink>());
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
    // globalLogger->AddSink(std::make_shared<GameEngine::FileSink>("Log.txt"));

    globalLogger->SetLoggedLevels(GameEngine::LogLevel::ALL);
    LOG_INFO("ProgramStarted");

    auto *settings = Roguelike::Settings::Instance();

    GameEngine::RenderSystem::Instance()->CrateMainWindow(sf::VideoMode(settings->screenWidth, settings->screenHeight),
                                                          settings->gameName);
    GameEngine::RenderSystem::Instance()->SetUpLayers(static_cast<int>(Roguelike::Settings::RenderLayers::Count));
    GameEngine::RenderSystem::LayerBitmask activeLayers;
#ifdef NDEBUG
    activeLayers.SetLayerValue(static_cast<int>(Roguelike::Settings::RenderLayers::Debug), false);
#endif // NDEBUG

    GameEngine::RenderSystem::Instance()->SetActiveLayers(activeLayers);

    GameEngine::ResourceSystem::Instance()->LoadTextureMap(settings->playerTextureMap);
    GameEngine::ResourceSystem::Instance()->LoadTextureMap(settings->enemyTextureMap);
    GameEngine::ResourceSystem::Instance()->LoadTextureMap(settings->wallTextureMap);
    GameEngine::ResourceSystem::Instance()->LoadTextureMap(settings->floorTextureMap);

    GameEngine::ResourceSystem::Instance()->LoadMusic("background",
                                                      settings->soundPath + "Clinthammer__Background_Music.wav");
    GameEngine::ResourceSystem::Instance()->LoadFont("default", settings->fontPath + "Roboto-Regular.ttf");

    Roguelike::LevelManager::Instance()->LoadNextLevel();
    GameEngine::Engine::Instance()->Run();

    return 0;
}