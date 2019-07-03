#pragma once
#include <SFML/Graphics.hpp>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	//Load asset and initialise required rendering data
	//Returns TRUE if Loading FAILS
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	void changeTile(sf::Vector2f posistion, sf::Uint32 newTileTex);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//level/texture data
	sf::Vector2u SizeOfTileTexturesPixels;//dimension of texture in pixels
	sf::Vector2u LevelDimensions;		//dimensions of level in pixels
	sf::Vector2u TilesInLevel;			//dimension of level in tiles
	sf::Uint32 NumberOfTilesInTexture;	//number of tiles in texture

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};