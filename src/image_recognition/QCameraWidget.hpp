#ifndef Q_CAMERAWIDGET_H
#define Q_CAMERAWIDGET_H

#pragma once

// STL
#include <list>
#include <cmath>
#include <memory>
#include <thread>
#include <vector>

// Qt
#include <QTimer>
#include <QMessageBox>

// OpenCV
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


#include "../models/CDice.hpp"
#include "../models/CDiceSet.hpp"

// UI
#include "ui_QCameraWidget.h"


/**
 * @brief Encapsule la détection d'image et le rendu vidéo
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QCameraWidget : public QWidget
{
	Q_OBJECT

private:
    /**
     * @brief Largeur minimum d'un dé
     */
	const uint MIN_DICE_WIDTH = 1000;

    /**
     * @brief Largeur maximum d'un dé
     */
	const uint MAX_DICE_WIDTH = 4000;

    /**
     * @brief Largeur minimum d'un point d'un dé
     */
	const uint MIN_DICE_DOT_WIDTH = 10;

    /**
     * @brief Largeur maximum d'un point d'un dé
     */
	const uint MAX_DICE_DOT_WIDTH = 200;

    /**
     * @brief Noyau par défaut utilisé pour les opérations sur image
     */
	const cv::Size DEFAULT_KERNEL = cv::Size(3, 3);

	/**
	 * @brief Seuil minimum pour le seuillage de Canny
	 */
	const uint MIN_CANNY_THRESHOLD = 210;

    /**
     * @brief Seuil maximum pour le seuillage de Canny
     */
	const uint MAX_CANNY_THRESHOLD = 255;

    /**
     * @brief Distance minimale depuis le centre du dé
     */
	const uint MIN_DISTANCE_FROM_DICE_CENTER = 7;

    /**
	 * @brief Seuil minimum pour le seuillage
	 */
	const uint MIN_BLOB_THRESHOLD = 100;

    /**
     * @brief Seuil maximum pour le seuillage
     */
	const uint MAX_BLOB_THRESHOLD = 255;

    /**
     * @brief Aire minimum
     */
	const uint MIN_AREA = 5; // TODO MIN_BLOB_AREA

    /**
    * @brief Aire maximum
    */
	const uint MAX_AREA = 200; // TODO MAX_BLOB_AREA

    /**
    * @brief TODO
    */
	const float MIN_CIRCULARITY = 0.3;

    /**
    * @brief TODO
    */
	const float MIN_INERTIA_RATIO = 0.5;

    /**
    * @brief Tolérance d'écart entre la position d'un même dé sur deux images différentes
    */
	const float SAME_POS_TOLERANCE = 10;


    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QCameraWidget m_ui;

	/**
	 * @brief Capture vidéo
	 */
	cv::VideoCapture m_videoCapture;

	/**
	 * @brief Dernière image capturée
	 */
	std::unique_ptr<cv::Mat> m_matImageCaptured = nullptr;

	/**
	 * @brief Chrono
	 *
	 * Sert à actualiser l'image toutes les 20ms et à lancer l'analyse
	 */
	QTimer m_qTimerFrame;

	/**
	 * @brief Liste des dés détectés
	 */
	std::list<std::shared_ptr<CDice>> m_lDices;

	std::list<std::shared_ptr<CDice>> m_lDicesBuffer; // TODO local

	/**
	 * @brief Jeu de dés nécessitant d'être confirmé par une seconde analyse
	 *
	 * La seconde analyse doit donner un set identique pour valider
	 */
	std::shared_ptr<CDiceSet> m_pLastDiceSet = nullptr;

	/**
	 * @brief Dernier jeu de dés validé
	 */
	std::shared_ptr<CDiceSet> m_pLastValidatedDiceSet = nullptr;

	/**
	 * @brief Est-ce que la dernière détection contenait une erreur ?
	 */
	bool m_bIsWrongDetection = false;

	/**
	 * @brief Active ou désactive le traitement d'image sur deux cœurs
	 *
	 * L'analyse par aire minimum sera faite sur un cœurs et celle par Blob sur l'autre.
	 */
	bool m_bThreadsEnabled = false;

	std::list<std::unique_ptr<std::thread>> m_lThreads; // TODO

public:
    /**
     * @brief Contructeur
     *
     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
     */
	QCameraWidget(QWidget* parent = Q_NULLPTR);

    /**
     * @brief Destructeur
     */
	~QCameraWidget();

public slots:
    /**
     * @brief Callback lorsque l'utilisateur signale une erreur de détection
     */
	void onWrongDetection();
	
private:
    /**
     * @brief Met à jour l'image // TODO
     */
	void _updateWindow();

	/**
	 * @brief Traitement d'image par aire minimum
	 *
	 * @param lDetectedDices : std::list<std::shared_ptr<CDice>>& - Liste des dés détectés
	 * @param iNDetectedDices : size_t& - Nombre de dés détectés
	 */
	void _findDicesByMinArea(std::list<std::shared_ptr<CDice>>& lDetectedDices, size_t& iNDetectedDices) const;

    /**
     * @brief Traitement d'image par simple blob
     *
     * @param iNDetectedDices : size_t& - Nombre de dés détectés
     */
	void _findDicesByBlob(size_t& iNDetectedDices) const;

private slots:
    /**
     * @brief Lance l'analyse de l'image et emmet un jeu de dés si l'analyse est probante
     */
	void _findDices();

signals:
    /**
     * @brief Signale que l'image de la caméra a changé
     */
	void cameraImgUpdated();

	/**
	 * @brief Signale que le jeu de dés a été mis à jour
	 *
	 * @param diceSet : CDiceSet& - Nouveau jeu de dés
	 * @param isDetectionCorrection : bool - Vrai s'il s'agit d'une correction de détection
	 */
	void dicesUpdated(CDiceSet& diceSet, bool isDetectionCorrection);
};

#endif // Q_CAMERAWIDGET_H
