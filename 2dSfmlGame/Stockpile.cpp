#include "Stockpile.h"



Stockpile::Stockpile()
{
	m_pile[WOOD] = 100;
	m_pile[STONE] = 0;
	m_pile[FOOD] = 100;
}


Stockpile::~Stockpile()
{
}

int Stockpile::getStock(Stock type)
{
	return m_pile[type];
}

void Stockpile::addStock(Stock type, unsigned int amount)
{
	m_pile[type] += amount;
}

void Stockpile::removeStock(Stock type, unsigned int amount)
{
	if (enoughStock(type,amount))
		m_pile[type] -= amount;

}

bool Stockpile::enoughStock(Stock type, unsigned int amount) 
{
	return (m_pile[type] - amount >= 0);
}
