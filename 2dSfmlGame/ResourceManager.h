#pragma once
#include "TextureCache.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	bool LoadTexture(const std::string& texturePath);
	bool GetTexture(const std::string& texturePath, std::shared_ptr<sf::Texture>& ptex);

private:
	TextureCache _textureCache;
};
