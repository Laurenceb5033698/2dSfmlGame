#include "TextureCache.h"
#include "Utils.h"


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}


bool TextureCache::LoadTexture(const std::string& texturePath, std::shared_ptr<sf::Texture>& pTex)
{
	for (int i(0); i < m_Textures.size(); ++i) {
		if (texturePath == m_Textures.at(i)._filename) {
			pTex = m_Textures.at(i).p_texture;
			return EXIT_SUCCESS;
		}
	}

	//texture wasnt found
	Data newTexture(texturePath);
	if (!newTexture.LoadFromFile())
	{
		DBOUT("Failed to load file: " << texturePath);
		return EXIT_FAILURE;
	}
	m_Textures.push_back(newTexture);
	pTex = newTexture.p_texture;
	return EXIT_SUCCESS;
}


std::shared_ptr<sf::Texture> TextureCache::GetTexture(const std::string& texturePath)
{
	for (int i(0); i < m_Textures.size(); ++i) {
		if (texturePath == m_Textures.at(i)._filename) {
			return m_Textures.at(i).p_texture;
		}
	}
	return nullptr;
}
