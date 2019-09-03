#include "Sprite.h"
#include "Utils.h"

//Real///////////////////////////////////
//SINGLESPRITE : public Sprite
void SingleSprite::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_textureRect)
	{
		m_textureRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}
void SingleSprite::updatePositions() {
	sf::FloatRect bounds = getLocalBounds();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, bounds.height);
	m_vertices[2].position = sf::Vector2f(bounds.width, 0);
	m_vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
}

void SingleSprite::updateTexCoords() {
	float left = static_cast<float>(m_textureRect.left);
	float right = left + m_textureRect.width;
	float top = static_cast<float>(m_textureRect.top);
	float bottom = top + m_textureRect.height;

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, top);
	m_vertices[3].texCoords = sf::Vector2f(right, bottom);
}

void SingleSprite::setColor(const sf::Color& color) {
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;

}
void SingleSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &(*p_texture);//Dereference shared_ptr, then pass texture to renderStates

	// draw the vertex array
	target.draw(m_vertices, 4, sf::PrimitiveType::TriangleStrip,  states);
	
}	

//Abstract//////////////////////////////////
//MULTISPRITE : public Sprite
void MultiSprite::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_textureRect)
	{
		m_textureRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}
//updatePositions() = 0
void MultiSprite::updateTexCoords()
{
	float left = static_cast<float>(m_textureRect.left);
	float right = left + m_textureRect.width;
	float top = static_cast<float>(m_textureRect.top);
	float bottom = top + m_textureRect.height;
	// define its 4 texture coordinates
	for (int i(0); i < m_vertices.getVertexCount()/4; ++i) {
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].texCoords = sf::Vector2f(left, top);
		quad[1].texCoords = sf::Vector2f(left, bottom);
		quad[2].texCoords = sf::Vector2f(right, top);
		quad[3].texCoords = sf::Vector2f(right, bottom);
	}
}


//Abstract////////////////////////////////////
//SPRITE
Sprite::Sprite()
	:rm(NULL), p_texture()
{}
Sprite::Sprite(std::shared_ptr<sf::Texture> ptex)
	:rm(NULL), p_texture(ptex)
{}
Sprite::Sprite(std::shared_ptr<sf::Texture> ptex, ResourceManager* r)
	:rm(r), p_texture(ptex)
{}
Sprite::Sprite( ResourceManager* r)
	: rm(r), p_texture()
{}

Sprite::~Sprite()
{

}


//////////////////////////////////////////
void Sprite::Init(ResourceManager* r)
{
	rm = r;
}

//Load a single un-animated sprite
bool Sprite::Load(const std::string& spriteTexture)
{
	//load texture
	if (LoadTexture(spriteTexture))
		return EXIT_FAILURE;

	//set vertex pos, texture rect and texcoords
	setTextureRect(sf::IntRect(0, 0, p_texture->getSize().x, p_texture->getSize().y));
	


	return EXIT_SUCCESS;
}


//Drawing sprite is handled per derived class obj
//void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	// apply the transform
//	states.transform *= getTransform();
//
//	// apply the tileset texture
//	states.texture = &(*p_texture);//Dereference shared_ptr, then pass texture to renderStates
//
//	// draw the vertex array
//	target.draw(m_vertices, 4, sf::PrimitiveType::TriangleStrip,  states);
//	
//}	

bool Sprite::LoadTexture(const std::string& textureFilepath)
{
	//Try to Load texture and store it into p_texture
	if (rm->GetTexture(textureFilepath, p_texture)) {
		DBOUT("failed to Get texture" << textureFilepath);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//////////////////////////////
//private internal functions. From SFML/Sprite.cpp
void Sprite::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_textureRect)
	{
		m_textureRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}

sf::FloatRect Sprite::getLocalBounds() const
{
	float width = static_cast<float>(std::abs(m_textureRect.width));
	float height = static_cast<float>(std::abs(m_textureRect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

