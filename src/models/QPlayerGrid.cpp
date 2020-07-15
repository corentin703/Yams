#include "QPlayerGrid.hpp"

using namespace std;

QPlayerGrid::QPlayerGrid(const QString& sName)
{
	m_sPlayerName = sName;

	// Partie supérieure
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

	// Partie inférieure
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

void QPlayerGrid::setAces(uint iValue)
{
	if (m_bIsAcesAlreadySet)
	{
		throw new runtime_error("Les as ont déjà été défini");
	}
	
	m_iAces = iValue;
	m_bIsAcesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setTwos(uint iValue)
{
	if (m_bIsTwosAlreadySet)
	{
		throw new runtime_error("Les deux ont déjà été défini");
	}
	
	m_iTwos = iValue;
	m_bIsTwosAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setThrees(uint iValue)
{
	if (m_bIsThreesAlreadySet)
	{
		throw new runtime_error("Les trois ont déjà été défini");
	}
	
	m_iThrees = iValue;
	m_bIsThreesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setFours(uint iValue) 
{
	if (m_bIsFoursAlreadySet)
	{
		throw new runtime_error("Les quatre ont déjà été défini");
	}
	
	m_iFours = iValue;
	m_bIsFoursAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setFives(uint iValue)
{
	if (m_bIsFivesAlreadySet)
	{
		throw new runtime_error("Les cinq ont déjà été défini");
	}
	
	m_iFives = iValue;
	m_bIsFivesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setSixes(uint iValue)
{
	if (m_bIsSixesAlreadySet)
	{
		throw new runtime_error("Les six ont déjà été défini");
	}
	
	m_iSixes = iValue;
	m_bIsSixesAlreadySet = true;
	
	_checkBonus();
	emit gridUpdated(this);
}

void QPlayerGrid::setBrelan(uint iValue)
{
	if (m_bIsBrelanAlreadySet)
	{
		throw new runtime_error("Le brelan a déjà été défini");
	}
	
	m_iBrelan = iValue;
	m_bIsBrelanAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setCarre(uint iValue)
{
	if (m_bIsCarreAlreadySet)
	{
		throw new runtime_error("Le carré a déjà été défini");
	}
	
	m_iCarre = iValue;
	m_bIsCarreAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setFull(bool bIsFull)
{
	if (m_bIsFullAlreadySet)
	{
		throw new runtime_error("Le full a déjà été défini");
	}
	
	m_bIsFull = bIsFull;
	m_bIsFullAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setSmallStraight(bool bIsSmallStraight)
{
	if (m_bIsSmallStraightAlreadySet)
	{
		throw new runtime_error("La petite suite a déjà été défini");
	}
	
	m_bIsSmallStraight = bIsSmallStraight;
	m_bIsSmallStraightAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setLargeStraight(bool bIsLargeStraight)
{
	if (m_bIsLargeStraightAlreadySet)
	{
		throw new runtime_error("La grande suite a déjà été défini");
	}
	
	m_bIsLargeStraight = bIsLargeStraight;
	m_bIsLargeStraightAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setYams(bool bIsYams)
{
	if (m_bIsYamsAlreadySet)
	{
		throw new runtime_error("Le Yams a déjà été défini");
	}
	
	m_bIsYams = bIsYams;
	m_bIsYamsAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setSuperYams(bool bIsSuperYams)
{
	if (m_bIsSuperYamsAlreadySet)
	{
		throw new runtime_error("Le Super Yams a déjà été défini");
	}
	
	m_bIsSuperYams = bIsSuperYams;
	m_bIsSuperYamsAlreadySet = true;
	
	emit gridUpdated(this);
}

void QPlayerGrid::setChance(uint iChance) 
{
	if (m_bIsChanceAlreadySet)
	{
		throw new runtime_error("La chance a déjà été définie");
	}
	
	m_iChance = iChance;
	m_bIsChanceAlreadySet = true;
	
	emit gridUpdated(this);
}


uint QPlayerGrid::getPreUpperTotal() const
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

uint QPlayerGrid::getLowerTotal() const
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

bool QPlayerGrid::isGridFinished() const
{
	return (
		isAcesAlreadySet() &&
		isTwosAlreadySet() &&
		isThreesAlreadySet() &&
		isFoursAlreadySet() &&
		isFivesAlreadySet() &&
		isSixesAlreadySet() &&

		isBrelanAlreadySet() &&
		isCarreAlreadySet() &&
		isFullAlreadySet() &&
		isSmallStraightAlreadySet() &&
		isLargeStraightAlreadySet() &&
		isYamsAlreadySet() &&
		isSuperYamsAlreadySet() &&
		isChanceAlreadySet()
	);
}

void QPlayerGrid::_checkBonus()
{
	if (getPreUpperTotal() > 63)
	{
		m_bIsBonus = true;
		emit gridUpdated(this);
	};
}
