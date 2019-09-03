#include "Trees.h"


Trees::Trees()
	:_maxResource(100),
	_amount(_maxResource),
	_harvested(5),
	_waitTime(sf::seconds(20)),
	m_treesToDraw(NUM_TREES),
	m_treeType(0)
{}


Trees::~Trees()
{
}

void Trees::Init(ResourceManager * r)
{	//pre-load Initiaisation
	this->Sprite::Init(r);
	
}

void Trees::Update(float dt)
{
	if (_regenerating && _regenTimer.getElapsedTime() > _waitTime)
		RegenerateResource();
}

void Trees::Animate(float dt)
{

}

//setGrid
void Trees::SetGrid(int, int)
{

}

//reduce _amount remaining
int Trees::Harvest()
{
	_amount -= _harvested;
	if (!_regenerating) {
		_regenerating = true;
		_regenTimer.restart();
	}
	updateTrees();
	//return amount harvested
	return _harvested;
}

//increase _amount remaining
void Trees::RegenerateResource()
{
	int val(_maxResource / 5);

	if (_amount += val >= _maxResource) {
		_amount = _maxResource;
		_regenerating = false;
	}
	
	_regenTimer.restart();
	updateTrees();

}

//when a Trees object is drawn, it draws up to 5 of the tree texture
void Trees::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &(*p_texture);//Dereference shared_ptr, then pass texture to renderStates

	// draw the vertex array


	target.draw(m_vertices, states);

	
}



bool Trees::Load(const std::string& spriteTexture) {

	//load texture
	if (LoadTexture(spriteTexture))
		return EXIT_FAILURE;

	//initialse vertexArray
	m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	m_vertices.resize(NUM_TREES * 4);

	//set tree varient
	//	get sprite sheet dimensions
	sf::Vector2u varientSizePx(64, 64);	//size of each varient in pizes
	sf::Vector2u varientSizeDims(VARIENT_X,VARIENT_Y);	//size of texture in varients (2,2) = 2*2 = 4;

	for (int j(0); j < varientSizeDims.y; ++j)
		for (int i(0); i < varientSizeDims.x; ++i)
			m_varientRect[i + j * varientSizeDims.y] = sf::IntRect(i*varientSizePx.x, j*varientSizePx.y, varientSizePx.x, varientSizePx.y);
	
	//set vertex pos, texture rect and texcoords
	setTextureRect(m_varientRect[m_treeType]);
	


	return EXIT_SUCCESS;
}

void Trees::updatePositions() {
	sf::FloatRect bounds = getLocalBounds();
	int treeOffsets[NUM_TREES][2]{ {-5,-20}, {27,-19},{10,-4},{-4,13},{28,12} };	//offsets in pixels

	for (int i(0); i < NUM_TREES; ++i) {
		sf::Vector2f qOffset(treeOffsets[i][0], treeOffsets[i][1]);
		sf::Vertex* quad = &m_vertices[i * 4];


		quad[0].position = sf::Vector2f(0, 0) + qOffset;
		quad[1].position = sf::Vector2f(bounds.width, 0) + qOffset;
		quad[2].position = sf::Vector2f(bounds.width, bounds.height) + qOffset;
		quad[3].position = sf::Vector2f(0, bounds.height) + qOffset;
	}
	
}
void Trees::updateTexCoords() {
	float left = static_cast<float>(m_textureRect.left);
	float right = left + m_textureRect.width;
	float top = static_cast<float>(m_textureRect.top);
	float bottom = top + m_textureRect.height;
	for (int i(0); i < m_vertices.getVertexCount() / 4; ++i) {
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].texCoords = sf::Vector2f(left, top);
		quad[1].texCoords = sf::Vector2f(right, top);
		quad[2].texCoords = sf::Vector2f(right, bottom);
		quad[3].texCoords = sf::Vector2f(left, bottom);
	}
}

void Trees::setColor(const sf::Color& color) {
	//loops over all trees and sets colour for all
	for (int i(0); i < m_vertices.getVertexCount() / 4; ++i) {
		sf::Vertex* quad = &m_vertices[i * 4];

		quad[0].color = color;
		quad[1].color = color;
		quad[2].color = color;
		quad[3].color = color;
	
	}
}

void Trees::setColor(const sf::Color& color, int index) {
	//only sets colour for one quad (one tree)
	sf::Vertex* quad = &m_vertices[index * 4];

	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;

}

void Trees::updateTrees() {

	m_treesToDraw = _amount / 20;

	for (int i(0); i < NUM_TREES; ++i) {
		if (i <= m_treesToDraw) {
			//set opaque
			setColor(sf::Color().White, i);
		}
		else {
			//set transparent
			setColor(sf::Color().Transparent, i);

		}
	}
}