#ifndef C_DICE_H
#define C_DICE_H

#pragma once

// STL
#include <list>

// OpenCV
#include <opencv2/imgproc.hpp>

/**
 * @brief Encapsule un dé détecté
 *
 * Utile lors de la reconnaissance d'image
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class CDice
{

private: 

    /**
     * @brief Position du rectangle du dé
     */
	cv::RotatedRect m_diceRect;

	/**
	 * @brief Liste des positions des points du dé
	 */
	std::list<cv::RotatedRect> m_lDotRects;

public:
    /**
     * @brief Constructeur
     *
     * @param diceRect : const cv::RotatedRect& - Position du rectangle du dé
     */
	CDice(const cv::RotatedRect& diceRect);

	/**
	 * @brief Retourne la position du rectangle du dé
	 *
	 * @return const cv::RotatedRect& - Position du rectangle du dé
	 */
	const cv::RotatedRect& getDiceRect() const { return m_diceRect; }

    /**
     * @brief Définit la position du rectangle du dé
     *
     * @param diceRect : const cv::RotatedRect& - Position du rectangle du dé
     */
	void setDiceRect(const cv::RotatedRect& diceRect) { m_diceRect = diceRect; }

	/**
	 * @brief Retourne la liste des positions des points du dé
	 *
	 * @return std::list<cv::RotatedRect>& - Liste des positions des points du dé
	 */
	const std::list<cv::RotatedRect>& getDotRects() const { return m_lDotRects; }

	/**
	 * @brief Définit la liste des positions des points du dé
	 *
	 * @param dotRect : std::list<cv::RotatedRect>& - Liste des positions des points du dé
	 */
	void addDotRect(const cv::RotatedRect& dotRect) { m_lDotRects.push_back(dotRect); }

	/**
	 * @brief Retourne le nombre de points détectés
	 *
	 * @return uint - Nombre de dés détectés
	 */
	uint getCount() const { return m_lDotRects.size(); }

};

#endif // C_DICE_H
