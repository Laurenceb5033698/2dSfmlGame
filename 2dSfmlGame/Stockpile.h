#pragma once
class Stockpile
{
public:
	Stockpile();
	~Stockpile();

	enum Stock { WOOD, STONE, FOOD, _NUMSTOCKS };

	int getStock(Stock type);
	void addStock(Stock type, unsigned int amount);
	void removeStock(Stock type, unsigned int amount);
	bool enoughStock(Stock type, unsigned int amount);

	//has differnt stocks int the pile
	//wood
	//stone
	//food
	//gold?
	//population?

	unsigned int m_pile[_NUMSTOCKS];	//cannot be negative
};

