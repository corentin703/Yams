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
	QString m_sPlayerName;

	// Partie supérieure
	int m_iAces ;
	bool m_bIsAcesAlreadySet;
	
	int m_iTwos;
	bool m_bIsTwosAlreadySet;
	
	int m_iThrees;
	bool m_bIsThreesAlreadySet;
	
	int m_iFours;
	bool m_bIsFoursAlreadySet;
	
	int m_iFives;
	bool m_bIsFivesAlreadySet;
	
	int m_iSixes;
	bool m_bIsSixesAlreadySet;
	
	bool m_bIsBonus;

	// Partie inférieure
	int m_iBrelan;
	bool m_bIsBrelanAlreadySet;
	
	int m_iCarre;
	bool m_bIsCarreAlreadySet;
	
	bool m_bIsFull;
	bool m_bIsFullAlreadySet;
	
	bool m_bIsSmallStraight;
	bool m_bIsSmallStraightAlreadySet;
	
	bool m_bIsLargeStraight;
	bool m_bIsLargeStraightAlreadySet;
	
	bool m_bIsYams;
	bool m_bIsYamsAlreadySet;
	
	bool m_bIsSuperYams;
	bool m_bIsSuperYamsAlreadySet;
	
	int m_iChance;
	bool m_bIsChanceAlreadySet;

public:
	QPlayerGrid(QString sPlayerName);
	~QPlayerGrid();

	QString getPlayerName() { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	int& const getAces() { return m_iAces; }
	bool& const IsAcesAlreadySet() { return m_bIsAcesAlreadySet; }
	void setAces(int& const iValue);

	int& const getTwos() { return m_iTwos; }
	bool& const IsTwosAlreadySet() { return m_bIsTwosAlreadySet; }
	void setTwos(int& const iValue);

	int& const getThrees() { return m_iThrees; }
	bool& const IsThreesAlreadySet() { return m_bIsThreesAlreadySet; }
	void setThrees(int& const iValue);

	int& const getFours() { return m_iFours; }
	bool& const IsFoursAlreadySet() { return m_bIsFoursAlreadySet; }
	void setFours(int& const iValue);

	int& const getFives() { return m_iFives; }
	bool& const IsFivesAlreadySet() { return m_bIsFivesAlreadySet; }
	void setFives(int& const iValue);

	int& const getSixes() { return m_iSixes; }
	bool& const IsSixesAlreadySet() { return m_bIsSixesAlreadySet; }
	void setSixes(int& const iValue);

	int getBonus() { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
	int& const getBrelan() { return m_iBrelan; }
	bool& const IsBrelanAlreadySet() { return m_bIsBrelanAlreadySet; }
	void setBrelan(int& const iValue);

	int& const getCarre() { return m_iCarre; }
	bool& const IsCarreAlreadySet() { return m_bIsCarreAlreadySet; }
	void setCarre(int& const iValue);

	int getFull() { if (m_bIsFull) return 25; else return 0; }
	bool& const IsFullAlreadySet() { return m_bIsFullAlreadySet; }
	void setFull(bool& const bIsFull);

	int getSmallStraight() { return (m_bIsSmallStraight) ? 30 : 0; }
	bool& const IsSmallStraightAlreadySet() { return m_bIsSmallStraightAlreadySet; }
	void setSmallStraight(bool& const bIsSmallStraight);

	int getLargeStraight() { return (m_bIsLargeStraight) ? 40 : 0; }
	bool& const IsLargeStraightAlreadySet() { return m_bIsLargeStraightAlreadySet; }
	void setLargeStraight(bool& const bIsLargeStraight);

	int getYams() { return (m_bIsYams) ? 50 : 0; }
	bool& const IsYamsAlreadySet() { return m_bIsYamsAlreadySet; }
	void setYams(bool& const bIsYams);

	int getSuperYams() { return (m_bIsSuperYams) ? 100 : 0; }
	bool& const IsSuperYamsAlreadySet() { return m_bIsSuperYamsAlreadySet; }
	void setSuperYams(bool& const bIsSuperYams);
	
	int& const getChance() { return m_iChance; }
	bool& const IsChanceAlreadySet() { return m_bIsChanceAlreadySet; }
	void setChance(int& const iChance);


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