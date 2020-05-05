#include "QPlayerGrid.hpp"

using namespace std;

QPlayerGrid::QPlayerGrid(QString sName)
{
	m_sPlayerName = sName;

	// Partie sup�rieure
	m_iAces = 0;
	m_bIsAcesAlreadySet = false;

	m_iTwos = 0;
	m_bIsTwosAlreadySet = false;

	m_iThrees = 0;
	m_bIsThreesAlreadySet = false;

	m_iFours = 0;
	m_bIsFoursAlreadySet = false;

	m_iFives = 0;
	m_bIsFivesAlreadySet = false;

	m_iSixes = 0;
	m_bIsSixesAlreadySet = false;

	m_bIsBonus = false;

	// Partie inf�rieure
	m_iBrelan = 0;
	m_bIsBrelanAlreadySet = false;

	m_iCarre = 0;
	m_bIsCarreAlreadySet = false;

	m_bIsFull = false;
	m_bIsFullAlreadySet = false;

	m_bIsSmallStraight = false;
	m_bIsSmallStraightAlreadySet = false;

	m_bIsLargeStraight = false;
	m_bIsLargeStraightAlreadySet = false;

	m_bIsYams = false;
	m_bIsYamsAlreadySet = false;

	m_bIsSuperYams = false;
	m_bIsSuperYamsAlreadySet = false;

	m_iChance = 0;
	m_bIsChanceAlreadySet = false;
	
}

QPlayerGrid::~QPlayerGrid()
{
}

void QPlayerGrid::setAces(const uint& iValue)
{
	/*if (m_bIsAcesAlreadySet)
	{
		throw new exception("Les as ont d�j� �t� d�fini");
	}*/
	
	m_iAces = iValue;
	m_bIsAcesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setTwos(const uint& iValue)
{
	/*if (m_bIsTwosAlreadySet)
	{
		throw new exception("Les deux ont d�j� �t� d�fini");
	}*/
	
	m_iTwos = iValue;
	m_bIsTwosAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setThrees(const uint& iValue)
{
	/*if (m_bIsThreesAlreadySet)
	{
		throw new exception("Les trois ont d�j� �t� d�fini");
	}*/
	
	m_iThrees = iValue;
	m_bIsThreesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setFours(const uint& iValue)
{
	if (m_bIsFoursAlreadySet)
	{
		throw new exception("Les quatre ont d�j� �t� d�fini");
	}
	
	m_iFours = iValue;
	m_bIsFoursAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setFives(const uint& iValue)
{
	/*if (m_bIsFivesAlreadySet)
	{
		throw new exception("Les cinq ont d�j� �t� d�fini");
	}*/
	
	m_iFives = iValue;
	m_bIsFivesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setSixes(const uint& iValue)
{/*
	if (m_bIsFivesAlreadySet)
	{
		throw new exception("Les six ont d�j� �t� d�fini");
	}
	*/
	m_iSixes = iValue;
	m_bIsSixesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated();
}

void QPlayerGrid::setBrelan(const uint& iValue)
{
	/*if (m_bIsBrelanAlreadySet)
	{
		throw new exception("Le brelan a d�j� �t� d�fini");
	}*/
	
	m_iBrelan = iValue;
	m_bIsBrelanAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setCarre(const uint& iValue)
{
	if (m_bIsCarreAlreadySet)
	{
		throw new exception("Le carr� a d�j� �t� d�fini");
	}
	
	m_iCarre = iValue;
	m_bIsCarreAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setFull(const bool& bIsFull)
{
	if (m_bIsFullAlreadySet)
	{
		throw new exception("Le full a d�j� �t� d�fini");
	}
	
	m_bIsFull = bIsFull;
	m_bIsFullAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setSmallStraight(const bool& bIsSmallStraight)
{
	if (m_bIsSmallStraightAlreadySet)
	{
		throw new exception("La petite suite a d�j� �t� d�fini");
	}
	
	m_bIsSmallStraight = bIsSmallStraight;
	m_bIsSmallStraightAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setLargeStraight(const bool& bIsLargeStraight)
{
	if (m_bIsSmallStraightAlreadySet)
	{
		throw new exception("La grande suite a d�j� �t� d�fini");
	}
	
	m_bIsLargeStraight = bIsLargeStraight;
	m_bIsLargeStraightAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setYams(const bool& bIsYams)
{
	if (m_bIsYamsAlreadySet)
	{
		throw new exception("Le Yams a d�j� �t� d�fini");
	}
	
	m_bIsYams = bIsYams;
	m_bIsYamsAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setSuperYams(const bool& bIsSuperYams)
{
	if (m_bIsSuperYamsAlreadySet)
	{
		throw new exception("Le Super Yams a d�j� �t� d�fini");
	}
	
	m_bIsSuperYams = bIsSuperYams;
	m_bIsSuperYamsAlreadySet = true;
	
	emit gridUpdated();
}

void QPlayerGrid::setChance(const uint& iChance)
{
	if (m_bIsChanceAlreadySet)
	{
		throw new exception("Le Yams a d�j� �t� d�fini");
	}
	
	m_iChance = iChance;
	m_bIsChanceAlreadySet = true;
	
	emit gridUpdated();
}


const uint& QPlayerGrid::getPreUpperTotal()
{
	return (
		getAces() +
		getTwos() +
		getThrees() +
		getFours() +
		getFives() +
		getSixes()
	);
}

const uint& QPlayerGrid::getLowerTotal()
{
	return (
		getBrelan() +
		getCarre() +
		getFull() +
		getSmallStraight() +
		getLargeStraight() +
		getYams() +
		getSuperYams() +
		getChance()
		);
}

void QPlayerGrid::_checkBonus()
{
	if (getPreUpperTotal() > 63)
	{
		m_bIsBonus = true;
		emit gridUpdated();
	};
}
