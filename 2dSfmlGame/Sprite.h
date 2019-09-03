#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"



/////////////////////////////////////////////////////////////
//Abstract Sprite class, stores a texture and Knows how to load a texture
class Sprite : public sf::Drawable, public sf::Transformable
{
public:
	Sprite();
	Sprite(std::shared_ptr<sf::Texture> ptex);
	Sprite(std::shared_ptr<sf::Texture> ptex, ResourceManager* r);
	Sprite(ResourceManager* r);
	virtual ~Sprite();

	virtual void Init(ResourceManager* r);
	virtual bool Load(const std::string& file);

protected:
	bool LoadTexture(const std::string& textureFilepath);
	sf::FloatRect getLocalBounds() const;

	void setTextureRect(const sf::IntRect& rectangle);
	virtual void updatePositions() = 0;
	virtual void updateTexCoords() = 0;

private:

public:
	ResourceManager* rm;

	std::shared_ptr<sf::Texture> p_texture;
	sf::IntRect		m_textureRect;


};

/////////////////////////////////////////////////////////////
//Real SingleSprite draws a single texture, nothing fancy
class SingleSprite : public Sprite
{
public:
	void setColor(const sf::Color& color);
	void setTextureRect(const sf::IntRect& rectangle);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	void updatePositions();
	void updateTexCoords();

public:
	sf::Vertex		m_vertices[4];

};

/////////////////////////////////////////////////////////////
//Abstract Multisprite draws n many sprites from array based on one texture
//	-Requires offset knowledge from derived class
class MultiSprite : public Sprite
{
public:
	virtual void setColor(const sf::Color& color) = 0;
	void setTextureRect(const sf::IntRect& rectangle);
protected:
	virtual void updatePositions() = 0;	//requires knowledge of offset (set per derived type)
	virtual void updateTexCoords();

public:
	sf::VertexArray		m_vertices;

};