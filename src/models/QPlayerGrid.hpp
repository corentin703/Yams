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
	QPlayerGrid(const QString& sPlayerName);
	~QPlayerGrid();

	QString getPlayerName() const { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	const uint& getAces() const { return m_iAces; }
	const bool& IsAcesAlreadySet() const { return m_bIsAcesAlreadySet; }
	void setAces(uint iValue); 

	const uint& getTwos() const { return m_iTwos; }
	const bool& IsTwosAlreadySet() const { return m_bIsTwosAlreadySet; }
	void setTwos(uint iValue);

	const uint& getThrees() const { return m_iThrees; }
	const bool& IsThreesAlreadySet() const { return m_bIsThreesAlreadySet; }
	void setThrees(uint iValue);

	const uint& getFours() const { return m_iFours; }
	const bool& IsFoursAlreadySet() const { return m_bIsFoursAlreadySet; }
	void setFours(uint iValue);

	const uint& getFives() const  { return m_iFives; }
	const bool& IsFivesAlreadySet() const { return m_bIsFivesAlreadySet; }
	void setFives(uint iValue);

	const uint& getSixes() const { return m_iSixes; }
	const bool& IsSixesAlreadySet() const { return m_bIsSixesAlreadySet; }
	void setSixes(uint iValue);

	const uint& getBonus() const { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
	const uint& getBrelan() const { return m_iBrelan; }
	const bool& IsBrelanAlreadySet() const { return m_bIsBrelanAlreadySet; }
	void setBrelan(uint iValue);

	const uint& getCarre() const { return m_iCarre; }
	const bool& IsCarreAlreadySet() const { return m_bIsCarreAlreadySet; }
	void setCarre(uint iValue);

	const uint& getFull() const { if (m_bIsFull) return 25; else return 0; }
	const bool& IsFullAlreadySet() const { return m_bIsFullAlreadySet; }
	void setFull(bool bIsFull);

	const uint& getSmallStraight() const { return (m_bIsSmallStraight) ? 30 : 0; }
	const bool& IsSmallStraightAlreadySet() const { return m_bIsSmallStraightAlreadySet; }
	void setSmallStraight(bool bIsSmallStraight);

	const uint& getLargeStraight() const { return (m_bIsLargeStraight) ? 40 : 0; }
	const bool& IsLargeStraightAlreadySet() const { return m_bIsLargeStraightAlreadySet; }
	void setLargeStraight(bool bIsLargeStraight);

	const uint& getYams() const { return (m_bIsYams) ? 50 : 0; }
	const bool& IsYamsAlreadySet() const { return m_bIsYamsAlreadySet; }
	void setYams(bool bIsYams);

	const uint& getSuperYams() const { return (m_bIsSuperYams) ? 100 : 0; }
	const bool& IsSuperYamsAlreadySet() const { return m_bIsSuperYamsAlreadySet; }
	void setSuperYams(bool bIsSuperYams);
	
	const uint& getChance() const { return m_iChance; }
	const bool& IsChanceAlreadySet() const { return m_bIsChanceAlreadySet; }
	void setChance(uint iChance);


	/**
	  * Retourne le pré-total de la partie supérieure (sans le bonus)
	  *
	  * @return uint
	  */
	uint getPreUpperTotal() const;

	/**
	  * Retourne le total de la partie supérieure en contant le bonus si besoin est
	  *
	  * @return uint
	  */
	uint getUpperTotal() const { return getPreUpperTotal() + getBonus(); }

	/**
	  * Retourne le total de la partie inférieure
	  *
	  * @return uint
	  */
	uint getLowerTotal() const;

	/**
	  * Retourne le total de la partie
	  *
	  *	@return uint
	  */
	uint getTotal() const { return getPreUpperTotal() + getLowerTotal(); }

	/**
	  * Retourne vrai si la grille est complétée
	  *
	  *	@return bool
	  */
	bool isGridFinished() const;

private:
	void _checkBonus();

signals:
	void gridUpdated();

};

#endif // Q_PLAYER_GRID_H