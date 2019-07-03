#pragma once
#include <SFML/Graphics.hpp>

//Holds all textures for the game
class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	struct Data {
		Data() {}
		Data(sf::String filename): 
		_filename(filename), p_texture(nullptr)
		{ }
		bool LoadFromFile() 
		{ return p_texture->loadFromFile(_filename); }
		sf::String _filename;
		std::shared_ptr<sf::Texture> p_texture;
	};

	//loads then passes back pointer to texture
	//returns bool of result
	bool LoadTexture(const std::string& texturePath, std::shared_ptr<sf::Texture>& pTex);

	//returns shared pointer to texture
	std::shared_ptr<sf::Texture> GetTexture(const std::string& texturePath);

	std::vector<Data> m_Textures;
};

