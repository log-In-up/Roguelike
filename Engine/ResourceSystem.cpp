#include "pch.h"

#include "ResourceSystem.h"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "Logger.h"
#include "Vector.h"

namespace GameEngine
{
ResourceSystem *ResourceSystem::Instance()
{
    static ResourceSystem resourceSystem;
    return &resourceSystem;
}

const sf::Font *ResourceSystem::GetFontShared(const std::string &name) const
{
    auto fontPair = fonts.find(name);
    assert(fontPair != fonts.end() && "Font not loaded");
    if (fontPair != fonts.end())
    {
        return fontPair->second;
    }
    LOG_WARN(name + " font not loaded");
    return nullptr;
}

const sf::SoundBuffer *ResourceSystem::GetSoundShared(const std::string &name) const
{
    auto soundBufferPair = soundBuffers.find(name);
    assert(soundBufferPair != soundBuffers.end() && "Sound not loaded");
    if (soundBufferPair != soundBuffers.end())
    {
        return soundBufferPair->second;
    }
    LOG_WARN(name + " sound not loaded");
    return nullptr;
}

const sf::Texture *ResourceSystem::GetTextureMapElementShared(const std::string &name, int elementIndex) const
{
    auto textureMap = textureMaps.find(name);
    if (textureMap == textureMaps.end())
    {
        assert(false && "Texture map not loaded");
        LOG_WARN(name + " texture map not loaded");
        return nullptr;
    }
    assert(textureMap->second.size() >= elementIndex && "Texture map have fewer elements");
    if (elementIndex < textureMap->second.size())
    {
        return textureMap->second[elementIndex];
    }
    LOG_WARN(name + " texture map have fewer elements");
    return nullptr;
}

const sf::Texture *ResourceSystem::GetTextureShared(const std::string &name) const
{
    auto texturePair = textures.find(name);
    if (texturePair != textures.end())
    {
        return texturePair->second;
    }
    assert(true && "Texture not loaded");
    LOG_WARN(name + " texture not loaded");
    return nullptr;
}

int ResourceSystem::GetTextureMapElementsCount(const std::string &name) const
{
    auto textureMap = textureMaps.find(name);
    if (textureMap == textureMaps.end())
    {
        LOG_WARN(name + " texture map not founded")
        return -1;
    }
    return static_cast<int>(textureMap->second.size());
}

sf::Font *ResourceSystem::GetFontCopy(const std::string &name) const
{
    auto fontPair = fonts.find(name);
    assert(fontPair != fonts.end() && "Font not loaded");
    if (fontPair != fonts.end())
    {
        sf::Font *newFont = new sf::Font(*fontPair->second);
        return newFont;
    }
    LOG_WARN(name + " font not loaded");
    return nullptr;
}

sf::Music *ResourceSystem::GetMusicShared(const std::string &name) const
{
    auto musicPair = musics.find(name);
    assert(musicPair != musics.end() && "Music not loaded");
    if (musicPair != musics.end())
    {
        return musicPair->second;
    }
    LOG_WARN(name + " music not loaded");
    return nullptr;
}

sf::SoundBuffer *ResourceSystem::GetSoundCopy(const std::string &name) const
{
    auto soundBufferPair = soundBuffers.find(name);
    assert(soundBufferPair != soundBuffers.end() && "Sound not loaded");
    if (soundBufferPair != soundBuffers.end())
    {
        sf::SoundBuffer *newBuffer = new sf::SoundBuffer(*soundBufferPair->second);
        return newBuffer;
    }
    LOG_WARN(name + " sound not loaded");
    return nullptr;
}

sf::Texture *ResourceSystem::GetTectureCopy(const std::string &name) const
{
    auto texturePair = textures.find(name);
    if (texturePair != textures.end())
    {
        return new sf::Texture(*texturePair->second);
    }
    assert(true && "Texture not loaded");
    LOG_WARN(name + " texture not loaded");
    return nullptr;
}

sf::Texture *ResourceSystem::GetTextureMapElementCopy(const std::string &name, int elementIndex) const
{
    auto textureMap = textureMaps.find(name);
    if (textureMap == textureMaps.end())
    {
        assert(false && "Texture map not loaded");
        LOG_WARN(name + " texture map not loaded");
        return nullptr;
    }
    assert(textureMap->second.size() > elementIndex && "Texture map have fewer elements");
    if (elementIndex < textureMap->second.size())
    {
        return new sf::Texture(*(textureMap->second[elementIndex]));
    }
    LOG_WARN(name + " texture map have fewer elements");
    return nullptr;
}

void ResourceSystem::Clear()
{
    DeleteAllTextures();
    DeleteAllTextureMaps();
    DeleteAllSounds();
    DeleteAllMusics();
    DeleteAllFonts();
}

void ResourceSystem::DeleteFont(const std::string &name)
{
    auto fontPair = fonts.find(name);
    assert(fontPair != fonts.end() && "Font not loaded");
    if (fontPair != fonts.end())
    {
        delete fontPair->second;
        fonts.erase(fontPair);
    }
    else
    {
        LOG_WARN(name + " font not loaded before delete attempt")
    }
}

void ResourceSystem::DeleteMusic(const std::string &name)
{
    auto musicPair = musics.find(name);
    if (musicPair != musics.end())
    {
        delete musicPair->second;
        musics.erase(musicPair);
    }
    else
    {
        LOG_WARN(name + " music not loaded before delete");
    }
}

void ResourceSystem::DeleteSharedTexture(const std::string &name)
{
    auto texturePair = textures.find(name);

    if (texturePair != textures.end())
    {
        sf::Texture *deletingtTexture = texturePair->second;
        textures.erase(texturePair);
        delete deletingtTexture;
        LOG_INFO(name + " texture deleted")
    }
    else
    {
        LOG_WARN(name + " texture wasn't found on deleting")
    }
}

void ResourceSystem::DeleteSharedTextureMap(const std::string &name)
{
    auto textureMap = textureMaps.find(name);

    if (textureMap == textureMaps.end())
    {
        LOG_WARN(name + " texture map not founded");
        return;
    }
    for (auto &texture : textureMap->second)
    {
        delete texture;
    }
    textureMaps.erase(textureMap);
}

void ResourceSystem::LoadSound(const std::string &name, std::string sourcePath)
{
    if (soundBuffers.contains(name))
    {
        LOG_WARN(name + " sound already loaded")
        return;
    }

    sf::SoundBuffer *buffer = new sf::SoundBuffer();
    assert(buffer->loadFromFile(sourcePath) && "Sound not loaded");
    if (buffer->loadFromFile(sourcePath))
    {
        soundBuffers.emplace(std::pair<std::string, sf::SoundBuffer *>(name, buffer));
    }
    else
    {
        LOG_WARN(name + " sound not loaded from " + sourcePath);
        delete buffer;
    }
}

void ResourceSystem::DeleteSound(const std::string &name)
{
    auto soundBufferPair = soundBuffers.find(name);
    assert(soundBufferPair != soundBuffers.end() && "Sound not loaded");
    if (soundBufferPair != soundBuffers.end())
    {
        delete soundBufferPair->second;
        soundBuffers.erase(soundBufferPair);
    }
    else
    {
        LOG_WARN(name + " sound not loaded before delete attempt")
    }
}

void ResourceSystem::LoadFont(const std::string &name, std::string sourcePath)
{
    if (fonts.contains(name))
    {
        LOG_WARN(name + " font already loaded");
        return;
    }

    sf::Font *font = new sf::Font();
    assert(font->loadFromFile(sourcePath) && "Font not loaded");
    if (font->loadFromFile(sourcePath))
    {
        fonts.emplace(std::pair<std::string, sf::Font *>(name, font));
    }
    else
    {
        LOG_WARN(name + " font not loaded from " + sourcePath);
        delete font;
    }
}

void ResourceSystem::LoadMusic(const std::string &name, std::string sourcePath)
{
    if (musics.contains(name))
    {
        LOG_WARN(name + " music already loaded");
        return;
    }

    auto *music = new sf::Music();
    assert(music->openFromFile(sourcePath) && "Music not loaded");
    if (music->openFromFile(sourcePath))
    {
        musics.emplace(std::pair<std::string, sf::Music *>(name, music));
    }
    else
    {
        LOG_WARN(name + " music not loaded at path " + sourcePath);
    }
}

void ResourceSystem::LoadTexture(const std::string &name, std::string sourcePath, bool isSmooth)
{
    if (textures.contains(name))
    {
        LOG_WARN(name + " texture was loaded before");
        return;
    }

    sf::Texture *newTexture = new sf::Texture();

    if (newTexture->loadFromFile(sourcePath))
    {
        newTexture->setSmooth(isSmooth);
        textures.emplace(name, newTexture);
        LOG_INFO(name + "Texture loaded");
    }
    else
    {
        assert(newTexture->loadFromFile(sourcePath) && "Texture wasn't loaded");
        LOG_WARN(name + " texture wasn't loaded from " + sourcePath);
        delete newTexture;
    }
}

void ResourceSystem::LoadTextureMap(const std::string &name, std::string sourcePath, sf::Vector2i elementPixelSize,
                                    int totalElements, bool isSmooth)
{
    if (textureMaps.contains(name))
    {
        LOG_WARN(name + " texture map already loaded");
        return;
    }

    sf::Texture textureMap;
    assert(textureMap.loadFromFile(sourcePath) && "Failed to load texture map");
    if (textureMap.loadFromFile(sourcePath))
    {
        std::vector<sf::Texture *> textureMapElements;

        auto textureSize = GameEngine::Convert<sf::Vector2i>(textureMap.getSize());
        int loadedElements = 0;

        for (int topCoordinate = 0; topCoordinate <= textureSize.y - elementPixelSize.y;
             topCoordinate += elementPixelSize.y)
        {
            if (loadedElements == totalElements)
            {
                break;
            }

            for (int leftCoordinate = 0; leftCoordinate <= textureSize.x - elementPixelSize.x;
                 leftCoordinate += elementPixelSize.x)
            {
                if (loadedElements == totalElements)
                {
                    break;
                }

                sf::Texture *newTextureMapElement = new sf::Texture();
                assert(newTextureMapElement->loadFromFile(
                           sourcePath,
                           sf::IntRect(leftCoordinate, topCoordinate, elementPixelSize.x, elementPixelSize.y)) &&
                       "Failed to load texture map element");
                if (newTextureMapElement->loadFromFile(
                        sourcePath, sf::IntRect(leftCoordinate, topCoordinate, elementPixelSize.x, elementPixelSize.y)))
                {
                    newTextureMapElement->setSmooth(isSmooth);
                    textureMapElements.push_back(newTextureMapElement);
                }
                else
                {
                    LOG_WARN("Failed to load texture map element");
                    delete newTextureMapElement;
                }
                ++loadedElements;
            }
        }
        textureMaps.emplace(name, textureMapElements);
    }
    else
    {
        LOG_WARN("Failed to load texture map " + name + " from " + sourcePath);
    }
}

void ResourceSystem::LoadTextureMap(const TextureMapLoadingParameters &parameters)
{
    LoadTextureMap(parameters.name, parameters.sourcePath, parameters.elementPixelSize, parameters.totalElements,
                   parameters.isSmooth);
}

void ResourceSystem::DeleteAllFonts()
{
    std::vector<std::string> keysToDelete;
    for (const auto &fontPair : fonts)
    {
        keysToDelete.push_back(fontPair.first);
    }
    for (const auto &key : keysToDelete)
    {
        DeleteFont(key);
    }
}

void ResourceSystem::DeleteAllMusics()
{
    std::vector<std::string> keysToDelete;
    for (const auto &musicPair : musics)
    {
        keysToDelete.push_back(musicPair.first);
    }
    for (const auto &key : keysToDelete)
    {
        DeleteMusic(key);
    }
}

void ResourceSystem::DeleteAllSounds()
{
    std::vector<std::string> keysToDelete;
    for (const auto &soundPair : soundBuffers)
    {
        keysToDelete.push_back(soundPair.first);
    }
    for (const auto &key : keysToDelete)
    {
        DeleteSound(key);
    }
}

void ResourceSystem::DeleteAllTextureMaps()
{
    std::vector<std::string> keysToDelete;
    for (const auto &textureMapPair : textureMaps)
    {
        keysToDelete.push_back(textureMapPair.first);
    }
    for (const auto &key : keysToDelete)
    {
        DeleteSharedTextureMap(key);
    }
}

void ResourceSystem::DeleteAllTextures()
{
    std::vector<std::string> keysToDelete;
    for (const auto &texturePair : textures)
    {
        keysToDelete.push_back(texturePair.first);
    }
    for (const auto &key : keysToDelete)
    {
        DeleteSharedTexture(key);
    }
}
} // namespace GameEngine