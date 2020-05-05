#ifndef C_DICE_SET_H
#define C_DICE_SET_H

#pragma once

typedef unsigned int uint;

class CDiceSet
{

	uint m_iAs;
	uint m_iTwos;
	uint m_iThrees;
	uint m_iFours;
	uint m_iFives;
	uint m_iSixes;

	
public:
	CDiceSet();
	
	uint getAs() const { return m_iAs; }
	//void setAs(uint iAs) const { m_iAs = iAs; }
	
	uint getTwos() const { return 2 * m_iTwos; }
	//void setTwos(uint iTwos) const { m_iTwos = iTwos; }
	
	uint getThrees() const { return 3 * m_iThrees; }
	//void setThrees(uint iThrees) const { m_iThrees = iThrees; }
	
	uint getFours() const { return 4 * m_iFours; }
	//void setFours(uint iFours) const { m_iFours = iFours; }
	
	uint getFives() const { return 5 * m_iFives; }
	//void setFives(uint iFives) const { m_iFives = iFives; }
	
	uint getSixes() const { return 6 * m_iSixes; }
	//void setSixes(uint iSixes) const { m_iSixes = iSixes; }

	uint getTotal() const { return getAs() + getTwos() + getThrees() + getFours() + getFives() + getSixes(); }

	uint& operator[](uint iDiceNumber);
	
	//bool operator==(CDiceSet& const diceSet) { return (getTotal() == diceSet.getTotal()); };
	const bool& operator==(CDiceSet& diceSet);
	bool operator!=(CDiceSet& diceSet) { return !(operator==(diceSet)); }
	
};

inline CDiceSet::CDiceSet()
{
	m_iAs = 0;
	m_iTwos = 0;
	m_iThrees = 0;
	m_iFours = 0;
	m_iFives = 0;
	m_iSixes = 0;
}

inline uint& CDiceSet::operator[](uint iDiceNumber)
{
	switch (iDiceNumber)
	{
	case 1 :
		return m_iAs;
	case 2 :
		return m_iTwos;
	case 3 :
		return m_iThrees;
	case 4 :
		return m_iFours;
	case 5:
		return m_iFives;
	case 6 :
		return m_iSixes;
	default:
		throw new std::exception("Dé demandé inconnu");
	}
}

inline const bool& CDiceSet::operator==(CDiceSet& diceSet)
{
	for (int i = 1; i <= 6; ++i)
	{
		if (operator[](i) != diceSet[i])
		{
			return false;
		}
	}

	return true;
}


#endif
