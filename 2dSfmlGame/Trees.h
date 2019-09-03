#pragma once
#include "Sprite.h"

#define	NUM_TREES 5
#define VARIENT_X 2
#define VARIENT_Y 2

class Trees : public MultiSprite
{
public:
	Trees();
	~Trees();

	void Init(ResourceManager* r) override;
	bool Load(const std::string& file) override;
	void Update(float dt);
	void Animate(float dt);

	//setGrid
	void SetGrid(int, int);
	//reduce _amount remaining
	int Harvest();
	//increase _amount remaining
	void RegenerateResource();

	//when a Trees object is drawn, it draws up to 5 of the tree texture
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setColor(const sf::Color& color) override;
	void setColor(const sf::Color& color, int index);

protected:
	void updatePositions() override;
	void updateTexCoords() override;

private:
	void updateTrees();

public:
	sf::Clock _regenTimer;
	sf::Time _waitTime;
	//cannot regenerate above max
	const int _maxResource;
	//amount of resource remaining
	int _amount;
	//amount harvested per harvest
	int _harvested;

	bool _regenerating;
	int m_treesToDraw;
	int m_treeType;
	sf::IntRect m_varientRect[VARIENT_X*VARIENT_Y];	//multiple varients of tree need different textureRects

};

