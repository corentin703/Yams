#include "QPlayerGrid.hpp"

using namespace std;

QPlayerGrid::QPlayerGrid(std::string sName)
{
	m_sPlayerName = sName;
}

QPlayerGrid::~QPlayerGrid()
{
}

int QPlayerGrid::getPreUpperTotal()
{
	return (
		getTotal1() +
		getTotal2() +
		getTotal3() +
		getTotal4() +
		getTotal5() +
		getTotal6()
	);
}

int QPlayerGrid::getLowerTotal()
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
