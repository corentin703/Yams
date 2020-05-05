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
	uint m_iAces ;
	bool m_bIsAcesAlreadySet;
	
	uint m_iTwos;
	bool m_bIsTwosAlreadySet;
	
	uint m_iThrees;
	bool m_bIsThreesAlreadySet;
	
	uint m_iFours;
	bool m_bIsFoursAlreadySet;
	
	uint m_iFives;
	bool m_bIsFivesAlreadySet;
	
	uint m_iSixes;
	bool m_bIsSixesAlreadySet;
	
	bool m_bIsBonus;

	// Partie inférieure
	uint m_iBrelan;
	bool m_bIsBrelanAlreadySet;
	
	uint m_iCarre;
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
	
	uint m_iChance;
	bool m_bIsChanceAlreadySet;

public:
	QPlayerGrid(QString sPlayerName);
	~QPlayerGrid();

	QString getPlayerName() { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	const uint& getAces() { return m_iAces; }
	const bool& IsAcesAlreadySet() { return m_bIsAcesAlreadySet; } 
	void setAces(const uint& iValue);

	const uint& getTwos() { return m_iTwos; }
	const bool& IsTwosAlreadySet() { return m_bIsTwosAlreadySet; }
	void setTwos(const uint& iValue);

	const uint& getThrees() { return m_iThrees; }
	const bool& IsThreesAlreadySet() { return m_bIsThreesAlreadySet; }
	void setThrees(const uint& iValue);

	const uint& getFours() { return m_iFours; }
	const bool& IsFoursAlreadySet() { return m_bIsFoursAlreadySet; }
	void setFours(const uint& iValue);

	const uint& getFives() { return m_iFives; }
	const bool& IsFivesAlreadySet() { return m_bIsFivesAlreadySet; }
	void setFives(const uint& iValue);

	const uint& getSixes() { return m_iSixes; }
	const bool& IsSixesAlreadySet() { return m_bIsSixesAlreadySet; }
	void setSixes(const uint& iValue);

	uint getBonus() { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
	const uint& getBrelan() { return m_iBrelan; }
	const bool& IsBrelanAlreadySet() { return m_bIsBrelanAlreadySet; }
	void setBrelan(const uint& iValue);

	const uint& getCarre() { return m_iCarre; }
	const bool& IsCarreAlreadySet() { return m_bIsCarreAlreadySet; }
	void setCarre(const uint& iValue);

	const uint getFull() { if (m_bIsFull) return 25; else return 0; }
	const bool& IsFullAlreadySet() { return m_bIsFullAlreadySet; }
	void setFull(const bool& bIsFull);

	const uint& getSmallStraight() { return (m_bIsSmallStraight) ? 30 : 0; }
	const bool& IsSmallStraightAlreadySet() { return m_bIsSmallStraightAlreadySet; }
	void setSmallStraight(const bool& bIsSmallStraight);

	const uint& getLargeStraight() { return (m_bIsLargeStraight) ? 40 : 0; }
	const bool& IsLargeStraightAlreadySet() { return m_bIsLargeStraightAlreadySet; }
	void setLargeStraight(const bool& bIsLargeStraight);

	const uint& getYams() { return (m_bIsYams) ? 50 : 0; }
	const bool& IsYamsAlreadySet() { return m_bIsYamsAlreadySet; }
	void setYams(const bool& bIsYams);

	const uint& getSuperYams() { return (m_bIsSuperYams) ? 100 : 0; }
	const bool& IsSuperYamsAlreadySet() { return m_bIsSuperYamsAlreadySet; }
	void setSuperYams(const bool& bIsSuperYams);
	
	const uint& getChance() { return m_iChance; }
	const bool& IsChanceAlreadySet() { return m_bIsChanceAlreadySet; }
	void setChance(const uint& iChance);


	/**
	  * Retourne le pré-total de la partie supérieure (sans le bonus)
	  *
	  * @return uint
	  */
	const uint& getPreUpperTotal();

	/**
	  * Retourne le total de la partie supérieure en contant le bonus si besoin est
	  *
	  * @return uint
	  */
	const uint& getUpperTotal() { return getPreUpperTotal() + getBonus(); }

	/**
	  * Retourne le total de la partie inférieure
	  *
	  * @return uint
	  */
	const uint& getLowerTotal();

	/**
	  * Retourne le total de la partie
	  *
	  *	@return uint
	  */
	const uint& getTotal() { return getPreUpperTotal() + getLowerTotal(); }

private:
	void _checkBonus();

signals:
	void gridUpdated();

};

#endif // Q_PLAYER_GRID_H