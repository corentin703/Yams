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
	int m_iTotal1 = 0;
	int m_iTotal2 = 0;
	int m_iTotal3 = 0;
	int m_iTotal4 = 0;
	int m_iTotal5 = 0;
	int m_iTotal6 = 0;
	bool m_bIsBonus = false;

	// Partie inférieure
	int m_iBrelan = 0;
	int m_iCarre = 0;
	bool m_bIsFull = false;
	bool m_bIsSmallStraight = false;
	bool m_bIsLargeStraight = false;
	bool m_bIsYams = false;
	bool m_bIsSuperYams = false;
	int m_iChance = 0;

public:
	QPlayerGrid(std::string sPlayerName);
	~QPlayerGrid();

	std::string getPlayerName() { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	int getTotal1() { return m_iTotal1; }
	void setTotal1(int iValue) { m_iTotal1 = iValue; _checkBonus(); emit gridUpdated(); }

	int getTotal2() { return m_iTotal2; }
	void setTotal2(int iValue) { m_iTotal2 = iValue; _checkBonus(); emit gridUpdated(); }

	int getTotal3() { return m_iTotal3; }
	void setTotal3(int iValue) { m_iTotal3 = iValue; _checkBonus(); emit gridUpdated(); }

	int getTotal4() { return m_iTotal4; }
	void setTotal4(int iValue) { m_iTotal4 = iValue; _checkBonus(); emit gridUpdated(); }

	int getTotal5() { return m_iTotal5; }
	void setTotal5(int iValue) { m_iTotal5 = iValue; _checkBonus(); emit gridUpdated(); }

	int getTotal6() { return m_iTotal6; }
	void setTotal6(int iValue) { m_iTotal6 = iValue; _checkBonus(); emit gridUpdated(); }
	
	int getBonus() { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
	int getBrelan() { return m_iBrelan; }
	void setBrelan(int iValue) { m_iBrelan = iValue; emit gridUpdated(); }

	int getCarre() { return m_iCarre; }
	void setCarre(int iValue) { m_iCarre = iValue; emit gridUpdated(); }

	int getFull() { if (m_bIsFull) return 25; else return 0; }
	void setFull(bool bIsFull) { m_bIsFull = bIsFull; emit gridUpdated(); }

	int getSmallStraight() { return (m_bIsSmallStraight) ? 30 : 0; }
	void setSmallStraight(bool bIsSmallStraight) { m_bIsSmallStraight = bIsSmallStraight; emit gridUpdated(); }

	int getLargeStraight() { return (m_bIsLargeStraight) ? 40 : 0; }
	void setLargeStraight(bool bIsLargeStraight) { m_bIsLargeStraight = bIsLargeStraight; emit gridUpdated(); }

	int getYams() { return (m_bIsYams) ? 50 : 0; }
	void setYams(bool bIsYams) { m_bIsYams = bIsYams; emit gridUpdated(); }

	int getChance() { return m_iChance; }
	void setChance(int iChance) { m_iChance = iChance; emit gridUpdated(); }

	int getSuperYams() { return (m_bIsSuperYams) ? 100 : 0; }
	void setSuperYams(bool bIsSuperYams) { m_bIsSuperYams = bIsSuperYams; emit gridUpdated(); }


	/**
	  * Retourne le pré-total de la partie supérieure (sans le bonus)
	  *
	  * @return int
	  */
	int getPreUpperTotal();

	/**
	  * Retourne le total de la partie supérieure en contant le bonus si besoin est
	  *
	  * @return int
	  */
	int getUpperTotal() { return getPreUpperTotal() + getBonus(); }

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
	int getTotal() { return getPreUpperTotal() + getLowerTotal(); }

private:
	void _checkBonus();

signals:
	void gridUpdated();

};

#endif // Q_PLAYER_GRID_H