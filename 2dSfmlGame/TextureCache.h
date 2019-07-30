#pragma once
#include <SFML/Graphics.hpp>

//Holds all textures for the game
class TextureCache
{
public:

	TextureCache();
	~TextureCache();

	//loads then passes back pointer to texture
	//returns bool of result
	bool LoadTexture(const std::string& texturePath, std::shared_ptr<sf::Texture>& pTex);
	//returns shared pointer to texture
	std::shared_ptr<sf::Texture> GetTexture(const std::string& texturePath);

	std::map<std::string, std::shared_ptr<sf::Texture> > m_Textures;

};

