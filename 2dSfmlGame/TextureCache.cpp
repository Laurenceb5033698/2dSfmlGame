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
	std::map<std::string, std::shared_ptr<sf::Texture> >::iterator iter 
		= m_Textures.find(texturePath);
	if (iter != m_Textures.end()) {
		//the object exists!
		pTex = iter->second;
		DBOUT("Texture found, returning success.");

		return EXIT_SUCCESS;
	}
	//texture wasnt found
	std::shared_ptr<sf::Texture> pnewtexture = std::make_shared<sf::Texture>();
	if (!pnewtexture->loadFromFile(texturePath)) {
		DBOUT("failed to load texture " << texturePath);
		return EXIT_FAILURE;
	}
	std::map<std::string, std::shared_ptr<sf::Texture> >::_Pairib data 
		= m_Textures.insert(std::make_pair(texturePath, pnewtexture));

	pTex = (data.first->second);
	return EXIT_SUCCESS;
}


std::shared_ptr<sf::Texture> TextureCache::GetTexture(const std::string& texturePath)
{
	std::map<std::string, std::shared_ptr<sf::Texture> >::iterator iter
		= m_Textures.find(texturePath);
	if (iter != m_Textures.end()) {
		//the object exists!
		return iter->second;
	}
	return NULL;
}
