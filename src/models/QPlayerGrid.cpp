#include "QPlayerGrid.hpp"

using namespace std;

QPlayerGrid::QPlayerGrid(std::string sName)
{
	m_sPlayerName = sName;
}

QPlayerGrid::~QPlayerGrid()
{
}

int QPlayerGrid::getUpperTotal()
{
	return (
		m_iTotal1 +
		m_iTotal2 +
		m_iTotal3 +
		m_iTotal4 +
		m_iTotal5 +
		m_iTotal6 +
		(m_bIsBonus) ? 35 : 0
	);
}

int QPlayerGrid::getLowerTotal()
{
	return (
		m_iBrelan +
		m_iCarre +
		(m_bIsFull) ? 25 : 0 +
		(m_bIsSmallStraight) ? 30 : 0 +
		(m_bIsLargeStraight) ? 40 : 0 +
		(m_bIsYams) ? 50 : 0 +
		m_iChance
		);
}
