#ifndef Q_PLAYER_GRID_H
#define Q_PLAYER_GRID_H

#pragma once

// STL
#include <string>

// Qt
#include <QObject>

class QPlayerGrid : public QObject
{
	Q_OBJECT
	
private:
	std::string m_sPlayerName;

	// Partie supérieure
	int m_iTotal1;
	int m_iTotal2;
	int m_iTotal3;
	int m_iTotal4;
	int m_iTotal5;
	int m_iTotal6;
	bool m_bIsBonus;

	// Partie inférieure
	int m_iBrelan;
	int m_iCarre;
	bool m_bIsFull;
	bool m_bIsSmallStraight;
	bool m_bIsLargeStraight;
	bool m_bIsYams;
	int m_iChance;

public:
	QPlayerGrid(std::string sPlayerName);
	~QPlayerGrid();

	std::string getPlayerName() { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	int getTotal1() { return m_iTotal1; }
	void setTotal1(int iValue) { m_iTotal1 = iValue; _checkBonus(); }

	int getTotal2() { return m_iTotal2; }
	void setTotal2(int iValue) { m_iTotal2 = iValue; _checkBonus(); }

	int getTotal3() { return m_iTotal3; }
	void setTotal3(int iValue) { m_iTotal3 = iValue; _checkBonus(); }

	int getTotal4() { return m_iTotal4; }
	void setTotal4(int iValue) { m_iTotal4 = iValue; _checkBonus(); }

	int getTotal5() { return m_iTotal5; }
	void setTotal5(int iValue) { m_iTotal5 = iValue; _checkBonus(); }

	int getTotal6() { return m_iTotal6; }
	void setTotal6(int iValue) { m_iTotal6 = iValue; _checkBonus(); }
	
	int getBonus() { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
	int getBrelan() { return m_iBrelan; }
	void setBrelan(int iValue) { m_iBrelan = iValue; }

	int getCarre() { return m_iCarre; }
	void setCarre(int iValue) { m_iCarre = iValue; }

	int getFull() { if (m_bIsFull) return 25; else return 0; }
	void setFull(bool bIsFull) { m_bIsFull = bIsFull; }

	int getSmallStraight() { return (m_bIsSmallStraight) ? 30 : 0; }
	void setSmallStraight(bool bIsSmallStraight) { m_bIsSmallStraight = bIsSmallStraight; }

	int getLargeStraight() { return (m_bIsLargeStraight) ? 40 : 0; }
	void setLargeStraight(bool bIsLargeStraight) { m_bIsLargeStraight = bIsLargeStraight; }

	int getYams() { return (m_bIsYams) ? 50 : 0; }
	void setYams(bool bIsYams) { m_bIsYams = bIsYams; }

	int getChance() { return m_iChance; }
	void setChance(int iChance) { m_iChance = iChance; }


	/**
	  * Retourne le total de la partie supérieure
	  *
	  * @return int
	  */
	int getUpperTotal();

	/**
	  * Retourne le total de la partie inférieure
	  *
	  * @return int
	  */
	int getLowerTotal();

	/**
	  * Retourne le total de la partie
	  *
	  *	@return int
	  */
	int getTotal() { return getUpperTotal() + getLowerTotal(); }

private:
	void _checkBonus() { if (getUpperTotal() > 63) m_bIsBonus = true; };

};

#endif // Q_PLAYER_GRID_H