#ifndef Q_PLAYER_GRID_H
#define Q_PLAYER_GRID_H

#pragma once

// STL
#include <string>

// Qt
#include <QObject>

/**
 * @brief Encapsule une grille de jeu
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QPlayerGrid : public QObject
{
	Q_OBJECT
	
private:
    /**
     * @brief Nom du joueur
     */
	QString m_sPlayerName;

	// Partie supérieure
	/**
	 * @brief Valeur des As
	 */
	uint m_iAces ;

	/**
	 * @brief Vrai si les as ont déjà étés définis
	 */
	bool m_bIsAcesAlreadySet;

    /**
     * @brief Valeur des deux
     */
	uint m_iTwos;

    /**
	 * @brief Vrai si les deux ont déjà étés définis
	 */
	bool m_bIsTwosAlreadySet;

    /**
     * @brief Valeur des trois
     */
	uint m_iThrees;

    /**
     * @brief Vrai si les trois ont déjà étés définis
     */
	bool m_bIsThreesAlreadySet;

    /**
     * @brief Valeur des quatre
     */
	uint m_iFours;

    /**
     * @brief Vrai si les quatre ont déjà étés définis
     */
	bool m_bIsFoursAlreadySet;

    /**
     * @brief Valeur des cinq
     */
	uint m_iFives;

    /**
     * @brief Vrai si les cinq ont déjà étés définis
     */
	bool m_bIsFivesAlreadySet;

    /**
     * @brief Valeur des six
     */
	uint m_iSixes;

    /**
     * @brief Vrai si les six ont déjà étés définis
     */
	bool m_bIsSixesAlreadySet;

    /**
     * @brief Vrai si le bonus est acquis
     */
	bool m_bIsBonus;

	// Partie inférieure
    /**
     * @brief Valeur du Brelan
     */
	uint m_iBrelan;

    /**
     * @brief Vrai si le Brelan a déjà été défini
     */
	bool m_bIsBrelanAlreadySet;

    /**
     * @brief Valeur du Carré
     */
	uint m_iCarre;

    /**
     * @brief Vrai si le Carré a déjà été défini
     */
	bool m_bIsCarreAlreadySet;

    /**
     * @brief Vrai s'il y a Full
     */
	bool m_bIsFull;

    /**
     * @brief Vrai si le Full a déjà été défini
     */
	bool m_bIsFullAlreadySet;

    /**
     * @brief Vrai s'il y a la petite suite
     */
	bool m_bIsSmallStraight;

    /**
     * @brief Vrai si la petite suite a déjà été défini
     */
	bool m_bIsSmallStraightAlreadySet;

    /**
     * @brief Vrai s'il y a la grande suite
     */
	bool m_bIsLargeStraight;

    /**
     * @brief Vrai si le grande suite a déjà été défini
     */
	bool m_bIsLargeStraightAlreadySet;

    /**
     * @brief Vrai s'il y a le Yams
     */
	bool m_bIsYams;

    /**
     * @brief Vrai si le Yams a déjà été défini
     */
	bool m_bIsYamsAlreadySet;

    /**
    * @brief Vrai s'il y a le super Yams
    */
	bool m_bIsSuperYams;

    /**
     * @brief Vrai si le super Yams a déjà été défini
     */
	bool m_bIsSuperYamsAlreadySet;

    /**
     * @brief Valeur de la chance
     */
	uint m_iChance;

    /**
     * @brief Vrai si la chance a déjà été défini
     */
	bool m_bIsChanceAlreadySet;

public:
    /**
     * @brief Constructeur
     *
     * @param sPlayerName : QString& - Nom du joueur
     */
	QPlayerGrid(const QString& sPlayerName);

	/**
	 * @brief Retourne le nom du joueur
	 *
	 * @return QString - Nom du joueur
	 */
	QString getPlayerName() const { return m_sPlayerName; }


	// Getter / Setter partie supérieure
	/**
	 * @brief Retourne la valeur des As
	 * @return const uint&
	 */
	const uint& getAces() const { return m_iAces; }

    /**
     * @brief Retourne vrai si les as ont été défini
     * @return const bool&
     */
	const bool& isAcesAlreadySet() const { return m_bIsAcesAlreadySet; }

    /**
     * @brief Défini la valeur des As
     *
     * @brief iValue : uint
     */
	void setAces(uint iValue);

    /**
     * @brief Retourne la valeur des deux
     * @return const uint&
     */
	const uint& getTwos() const { return m_iTwos; }

    /**
     * @brief Retourne vrai si les deux ont été défini
     * @return const bool&
     */
	const bool& isTwosAlreadySet() const { return m_bIsTwosAlreadySet; }

    /**
     * @brief Défini la valeur des deux
     *
     * @brief iValue : uint
     */
	void setTwos(uint iValue);

    /**
     * @brief Retourne la valeur des trois
     * @return const uint&
     */
	const uint& getThrees() const { return m_iThrees; }

    /**
     * @brief Retourne vrai si les trois ont été défini
     * @return const bool&
     */
	const bool& isThreesAlreadySet() const { return m_bIsThreesAlreadySet; }

    /**
     * @brief Défini la valeur des trois
     *
     * @brief iValue : uint
     */
	void setThrees(uint iValue);

    /**
     * @brief Retourne la valeur des quatre
     * @return const uint&
     */
	const uint& getFours() const { return m_iFours; }

	/**
     * @brief Retourne vrai si les quatre ont été défini
     * @return const bool&
     */
	const bool& isFoursAlreadySet() const { return m_bIsFoursAlreadySet; }

    /**
     * @brief Défini la valeur des quatre
     *
     * @brief iValue : uint
     */
	void setFours(uint iValue);

    /**
     * @brief Retourne la valeur des cinq
     * @return const uint&
     */
	const uint& getFives() const  { return m_iFives; }

    /**
     * @brief Retourne vrai si les cinq ont été défini
     * @return const bool&
     */
	const bool& isFivesAlreadySet() const { return m_bIsFivesAlreadySet; }

    /**
     * @brief Défini la valeur des cinq
     *
     * @brief iValue : uint
     */
	void setFives(uint iValue);

    /**
     * @brief Retourne la valeur des six
     * @return const uint&
     */
	const uint& getSixes() const { return m_iSixes; }

    /**
    * @brief Retourne vrai si les six ont été défini
    * @return const bool&
    */
	const bool& isSixesAlreadySet() const { return m_bIsSixesAlreadySet; }

    /**
     * @brief Défini la valeur des six
     *
     * @brief iValue : uint
     */
	void setSixes(uint iValue);

    /**
     * @brief Retourne le bonus s'il y a
     * @return const uint&
     */
	const uint& getBonus() const { return (m_bIsBonus) ? 35 : 0; }


	// Getter / Setter partie inférieure
    /**
     * @brief Retourne la valeur du Bralan
     * @return const uint&
     */
	const uint& getBrelan() const { return m_iBrelan; }

    /**
    * @brief Retourne vrai si le Brelan a été défini
    * @return const bool&
    */
	const bool& isBrelanAlreadySet() const { return m_bIsBrelanAlreadySet; }

    /**
    * @brief Défini la valeur du Brelan
    *
    * @brief iValue : uint
    */
	void setBrelan(uint iValue);

    /**
     * @brief Retourne la valeur du Carré
     * @return const uint&
     */
	const uint& getCarre() const { return m_iCarre; }

    /**
     * @brief Retourne vrai si le Carré a été défini
     * @return const bool&
     */
	const bool& isCarreAlreadySet() const { return m_bIsCarreAlreadySet; }

    /**
     * @brief Défini la valeur du Carré
     *
     * @brief iValue : uint
     */
	void setCarre(uint iValue);

    /**
     * @brief Retourne la valeur du Full
     * @return const uint&
     */
	const uint& getFull() const { if (m_bIsFull) return 25; else return 0; }

    /**
     * @brief Retourne vrai si le Full a été défini
     * @return const bool&
     */
	const bool& isFullAlreadySet() const { return m_bIsFullAlreadySet; }

    /**
     * @brief Défini s'il y a Full
     *
     * @brief bIsFull : bool
     */
	void setFull(bool bIsFull);

    /**
     * @brief Retourne la valeur de la petite suite
     * @return const uint&
     */
	const uint& getSmallStraight() const { return (m_bIsSmallStraight) ? 30 : 0; }

    /**
     * @brief Retourne vrai si la petite suite a été défini
     * @return const bool&
     */
	const bool& isSmallStraightAlreadySet() const { return m_bIsSmallStraightAlreadySet; }

    /**
     * @brief Défini s'il y a petite suite
     *
     * @brief bIsSmallStraight : bool
     */
	void setSmallStraight(bool bIsSmallStraight);

    /**
     * @brief Retourne la valeur de la grande suite
     * @return const uint&
     */
	const uint& getLargeStraight() const { return (m_bIsLargeStraight) ? 40 : 0; }

    /**
     * @brief Retourne vrai si la grande suite a été défini
     * @return const bool&
     */
	const bool& isLargeStraightAlreadySet() const { return m_bIsLargeStraightAlreadySet; }

    /**
     * @brief Défini s'il y a grande suite
     *
     * @brief bIsLargeStraight : bool
     */
	void setLargeStraight(bool bIsLargeStraight);

    /**
     * @brief Retourne la valeur du Yams
     * @return const uint&
     */
	const uint& getYams() const { return (m_bIsYams) ? 50 : 0; }

    /**
     * @brief Retourne vrai si le Yams a été défini
     * @return const bool&
     */
	const bool& isYamsAlreadySet() const { return m_bIsYamsAlreadySet; }

    /**
     * @brief Défini s'il y a Yams
     *
     * @brief bIsYams : bool
     */
	void setYams(bool bIsYams);

    /**
     * @brief Retourne la valeur du super Yams
     * @return const uint&
     */
	const uint& getSuperYams() const { return (m_bIsSuperYams) ? 100 : 0; }

    /**
     * @brief Retourne vrai si le super Yams a été défini
     * @return const bool&
     */
	const bool& IsSuperYamsAlreadySet() const { return m_bIsSuperYamsAlreadySet; } // TODO Is => is

    /**
     * @brief Défini s'il y a super Yams
     *
     * @brief bIsSuperYams : bool
     */
	void setSuperYams(bool bIsSuperYams);

    /**
     * @brief Retourne la valeur de la chance
     * @return const uint&
     */
	const uint& getChance() const { return m_iChance; }

    /**
     * @brief Retourne vrai si la chance a été défini
     * @return const bool&
     */
	const bool& isChanceAlreadySet() const { return m_bIsChanceAlreadySet; }

    /**
     * @brief Défini la valeur de la chance
     *
     * @brief iChance : uint
     */
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
    /**
     * @brief Vérifie pour la partie supérieure si le joueur a obtenu le bonus ou non
     */
	void _checkBonus();

signals:
    /**
     * @brief Signale que la grille a été mise à jour
     *
     * @param playerGrid : QPlayerGrid*
     */
	void gridUpdated(QPlayerGrid* playerGrid);

};

#endif // Q_PLAYER_GRID_H