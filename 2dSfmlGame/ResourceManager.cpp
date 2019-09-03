#include "ResourceManager.h"

//TextureCache ResourceManager::_textureCache;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::LoadTexture(const std::string& texturePath) {
	return _textureCache.LoadTexture(texturePath);
}

bool ResourceManager::GetTexture(const std::string& texturePath, std::shared_ptr<sf::Texture>& ptex) {
	return _textureCache.LoadTexture(texturePath, ptex);
}
