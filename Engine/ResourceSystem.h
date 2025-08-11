#pragma once
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

namespace GameEngine
{
	class ResourceSystem
	{
	private:
		std::map<std::string, sf::Texture*> textures;
		std::map<std::string, std::vector<sf::Texture*>> textureMaps;
		std::map<std::string, sf::SoundBuffer*> sounds;
	public:
		static ResourceSystem* Instance();

		const sf::SoundBuffer* GetSound(const std::string& name) const;
		const sf::Texture* GetTextureMapElementShared(const std::string& name, int elementIndex) const;
		const sf::Texture* GetTextureShared(const std::string& name) const;
		int GetTextureMapElementsCount(const std::string& name) const;
		sf::Texture* GetTextureCopy(const std::string& name) const;
		sf::Texture* GetTextureMapElementCopy(const std::string& name, int elementIndex) const;
		void Clear();
		void DeleteSharedTexture(const std::string& name);
		void DeleteSharedTextureMap(const std::string& name);
		void DeleteSound(const std::string& name);
		void LoadSound(const std::string& name, std::string sourcePath);
		void LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth = true);
		void LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth = true);
	private:
		ResourceSystem() {}
		~ResourceSystem() {}

		ResourceSystem(ResourceSystem const&) = delete;
		ResourceSystem& operator= (ResourceSystem const&) = delete;

		void DeleteAllSounds();
		void DeleteAllTextureMaps();
		void DeleteAllTextures();
	};
}