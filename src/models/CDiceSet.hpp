#ifndef C_DICE_SET_H
#define C_DICE_SET_H

#pragma once

typedef unsigned int uint;

/**
 * @brief Encapsule un jeu de dés
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class CDiceSet
{
    /**
     * @brief Nombre d'as dans le jeu de dés
     */
	uint m_iAs;

    /**
     * @brief Nombre de deux dans le jeu de dés
     */
	uint m_iTwos;

    /**
     * @brief Nombre de trois dans le jeu de dés
     */
	uint m_iThrees;

    /**
     * @brief Nombre de quatre dans le jeu de dés
     */
	uint m_iFours;

    /**
     * @brief Nombre de cinq dans le jeu de dés
     */
	uint m_iFives;

    /**
     * @brief Nombre de six dans le jeu de dés
     */
	uint m_iSixes;

	
public:
    /**
     * @brief Constructeur
     */
	CDiceSet();

    /**
     * @brief Retourne le score donné par les as
     *
     * @return uint
     */
	uint getAces() const { return m_iAs; }

    /**
     * @brief Retourne le score donné par les deux
     *
     * @return uint
     */
	uint getTwos() const { return 2 * m_iTwos; }

    /**
     * @brief Retourne le score donné par les trois
     *
     * @return uint
     */
	uint getThrees() const { return 3 * m_iThrees; }

    /**
     * @brief Retourne le score donné par les quatre
     *
     * @return uint
     */
	uint getFours() const { return 4 * m_iFours; }

    /**
     * @brief Retourne le score donné par les cinq
     *
     * @return uint
     */
	uint getFives() const { return 5 * m_iFives; }

    /**
     * @brief Retourne le score donné par les six
     *
     * @return uint
     */
	uint getSixes() const { return 6 * m_iSixes; }

    /**
     * @brief Retourne la somme totale du jeu
     *
     * @return uint
     */
	uint getTotal() const { return getAces() + getTwos() + getThrees() + getFours() + getFives() + getSixes(); }

	/**
	 * @brief Permet d'accèder au nombre de dés par valeur
	 *
	 * @param iDiceNumber - Numéro du dé
	 *
	 * @return uint& - Nombre de dés de cette valeur
	 */
	uint& operator[](uint iDiceNumber);

	/**
	 * @brief Teste si un set est égal à l'autre
	 *
	 * @param diceSet : CDiceSet& - Jeu de dés
	 *
	 * @return bool
	 */
	bool operator==(CDiceSet& diceSet);

    /**
     * @brief Teste si un set n'est pas égal à l'autre
     *
     * @param diceSet : CDiceSet& - Jeu de dés
     *
     * @return bool
     */
	bool operator!=(CDiceSet& diceSet) { return !(operator==(diceSet)); }
	
};

inline CDiceSet::CDiceSet()
{
	m_iAs = 0;
	m_iTwos = 0;
	m_iThrees = 0;
	m_iFours = 0;
	m_iFives = 0;
	m_iSixes = 0;
}

inline uint& CDiceSet::operator[](uint iDiceNumber)
{
	switch (iDiceNumber)
	{
	case 1 :
		return m_iAs;
	case 2 :
		return m_iTwos;
	case 3 :
		return m_iThrees;
	case 4 :
		return m_iFours;
	case 5:
		return m_iFives;
	case 6 :
		return m_iSixes;
	default:
		throw new std::runtime_error("Dé demandé inconnu");
	}
}

inline bool CDiceSet::operator==(CDiceSet& diceSet)
{
	for (int i = 1; i <= 6; ++i)
	{
		if (operator[](i) != diceSet[i])
		{
			return false;
		}
	}

	return true;
}


#endif
