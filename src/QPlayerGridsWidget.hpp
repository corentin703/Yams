#ifndef Q_PLAYER_GRIDS_WIDGET_H
#define Q_PLAYER_GRIDS_WIDGET_H

#pragma once

// STL
#include <map>
#include <memory>

// Qt
#include <QWidget>

// UI
#include "ui_QPlayerGridsWidget.h"

// Modèles
#include "models/QPlayerGrid.hpp"

/**
 * @brief Vue des grilles de jeu
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QPlayerGridsWidget : public QWidget
{
	Q_OBJECT

	/**
	 * @brief Encapsule une vue de grille de jeu
	 *
	 * Structure de données visant à simplifier la construction de l'affichage des grilles de jeu
	 */
	class CPlayerGridView
	{
	public :
	    /**
	     * @brief Affichage nom du joueur
	     */
		QLabel* lblPlayerName;

		/**
		 * @brief Affichage de As
		 */
		QLabel* lblAs;
        /**
         * @brief Affichage des deux
         */
		QLabel* lblTwos;
		/**
		 * @brief Affichage des trois
		 */
		QLabel* lblThrees;
		/**
		 * @brief Affichage des quatre
		 */
		QLabel* lblFours;
		/**
		 * @brief Affichage cinq
		 */
		QLabel* lblFives;
		/**
		 * @brief Affichage six
		 */
		QLabel* lblSixes;
		/**
		 * @brief Affichage du total avant ajout du bonus
		 */
		QLabel* lblPreTotalSup;
		/**
		 * @brief Affichage du bonus obtenu
		 */
		QLabel* lblBonus;
		/**
		 * @brief Affichage du total de la partie supérieure
		 */
		QLabel* lblTotalSup;

		/**
		 * @brief Affichage du Brelan
		 */
		QLabel* lblBrelan;
		/**
		 * @brief Affichage du Carré
		 */
		QLabel* lblCarre;
		/**
		 * @brief Affichage du Full
		 */
		QLabel* lblFull;
		/**
		 * @brief Affichage de la petite suite
		 */
		QLabel* lblSmallStraight;
		/**
		 * @brief Affichage de la grande suite
		 */
		QLabel* lblLargeStraight;
		/**
		 * @brief Affichage du Yams
		 */
		QLabel* lblYams;
		/**
		 * @brief Affichage du super Yams
		 */
		QLabel* lblSuperYams;
		/**
		 * @brief Affichage de la chance
		 */
		QLabel* lblChance;
		/**
		 * @brief Affichage du total de la partie inférieure
		 */
		QLabel* lblTotalInf;

		/**
		 * @brief Affichage du total global
		 */
		QLabel* lblTotal;

		/**
		 * @brief Constructeur
		 *
		 * Instancie tous les pointeurs des données membres
		 *
		 * @param parent : QPlayerGridsWidget* - Widget parent
		 * @param sPlayerName : const QString& - Nom du joueur
		 */
		CPlayerGridView(QPlayerGridsWidget* parent, const QString& sPlayerName);
		~CPlayerGridView();
	};
	
private:
    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QPlayerGridsWidget m_ui;

	/**
	 * @brief Associe chaque modèle de grille à sa vue respective
	 */
	std::map<QPlayerGrid*, std::unique_ptr<CPlayerGridView>> m_mapPlayerGridViews;
	

public:
    /**
     * @brief Constructeur
     *
     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
     */
	QPlayerGridsWidget(QWidget *parent = Q_NULLPTR);

	/**
	 * @brief Retourne le bouton des As
	 *
	 * @return QPushButton*
	 */
	const QPushButton* getAcesButton() const { return m_ui.btnAces; }

    /**
     * @brief Retourne le bouton des deux
     *
     * @return QPushButton*
     */
	const QPushButton* getTwosButton() const { return m_ui.btnTwos; }

    /**
     * @brief Retourne le bouton des trois
     *
     * @return QPushButton*
     */
	const QPushButton* getThreeButton() const { return m_ui.btnThrees; }

    /**
     * @brief Retourne le bouton des quatre
     *
     * @return QPushButton*
     */
	const QPushButton* getFoursButton() const { return m_ui.btnFours; }

    /**
     * @brief Retourne le bouton des cinq
     *
     * @return QPushButton*
     */
	const QPushButton* getFivesButton() const { return m_ui.btnFives; }

    /**
     * @brief Retourne le bouton des six
     *
     * @return QPushButton*
     */
	const QPushButton* getSixesButton() const { return m_ui.btnSixes; }

    /**
     * @brief Retourne le bouton du Brelan
     *
     * @return QPushButton*
     */
	const QPushButton* getBrelanButton() const { return m_ui.btnBrelan; }

    /**
     * @brief Retourne le bouton du Carré
     *
     * @return QPushButton*
     */
	const QPushButton* getCarreButton() const { return m_ui.btnCarre; }

    /**
     * @brief Retourne le bouton du Full
     *
     * @return QPushButton*
     */
	const QPushButton* getFullButton() const { return m_ui.btnFull; }

    /**
     * @brief Retourne le bouton de la petite suite
     *
     * @return QPushButton*
     */
	const QPushButton* getSmallStraightButton() const { return m_ui.btnSmallStraight; }

    /**
     * @brief Retourne le bouton de la grande suite
     *
     * @return QPushButton*
     */
	const QPushButton* getLargeStraightButton() const { return m_ui.btnLargeStraight; }

    /**
     * @brief Retourne le bouton du Yams
     *
     * @return QPushButton*
     */
	const QPushButton* getYamsButton() const { return m_ui.btnYams; }

    /**
     * @brief Retourne le bouton de la chance
     *
     * @return QPushButton*
     */
	const QPushButton* getChanceButton() const { return m_ui.btnChance; }

    /**
     * @brief Retourne le bouton du super Yams
     *
     * @return QPushButton*
     */
	const QPushButton* getSuperYamsButton() const { return m_ui.btnSuperYams; }

	/**
	 * @brief Ajoute une grille à la liste d'affichage
	 *
	 * @param pQPlayerGrid : QPlayerGrid* - Grille à ajouter
	 */
	void addGrid(QPlayerGrid* pQPlayerGrid);

    /**
     * @brief Supprime une grille de la liste d'affichage
     *
     * @param pQPlayerGrid : QPlayerGrid* - Grille à supprimer
     */
	void removeGrid(QPlayerGrid* pQPlayerGrid);

    /**
    * @brief Active / désactive les boutons des actions
    *
    * @param bEnable : bool - Si vrai : active, si faux : désactive
    */
	void enableActionButtons(bool bEnable) const;

public slots:
    /**
     * @brief Active et désactive les boutons des actions en fonction des coups déjà réalisés d'un joueur
     *
     * @param playerGrid : QPlayerGrid& - Grille du joueur
     */
	void actualizeActionButtons(QPlayerGrid& playerGrid) const;

    /**
     * @brief Met à jour la vue d'une grille
     *
     * @param pQPlayerGrid : QPlayerGrid& - Grille du joueur
     */
	void updateGrid(QPlayerGrid* pQPlayerGrid);
};

#endif // Q_PLAYER_GRIDS_WIDGET_H
