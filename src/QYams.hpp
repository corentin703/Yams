#ifndef Q_YAMS_H
#define Q_YAMS_H

#pragma once

// STL
#include <list>
#include <map>
#include <memory>

// Qt
#include <QtWidgets/QMainWindow>

// UI
#include "ui_QYams.h"

// Reconnaissance d'image
#include "image_recognition/QCameraWidget.hpp"

// Modèles
#include "models/QPlayerGrid.hpp"
#include "models/CDiceSet.hpp"

#include "QAboutWidget.hpp"
#include "QEndGameWidget.hpp"
#include "QPlayerGridsWidget.hpp"
#include "QYamsStartFormWidget.hpp"

/**
 * @brief Contôleur du jeu Yams
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QYams : public QMainWindow
{
	Q_OBJECT

public:

    /**
     * @brief Toutes les actions réalisables par le joueur
     */
	enum EYamsActions
	{
		NOTHING = 0,
		
		ACES = 1,
		TWOS = 2,
		THREES = 3,
		FOURS = 4,
		FiVES = 5,
		SIXES = 6,

		BRELAN = 7,
		CARRE = 8,
		FULL = 9,
		SMALL_STRAIGHT = 10,
		LARGE_STRAIGHT = 11,
		YAMS = 12,
		SUPER_YAMS = 13,
		CHANCE = 14,
	};

	/**
	 * @brief Les choix possibles (1 choix = 1 bouton)
	 */
	enum EChoices
	{
		ANYTHING = 0,

		ONE = 1,
		TWO = 2,
		THREE = 3,
	};

	/**
	 * @brief Associe une action à un texte pour l'affichage
	 */
	std::map<EYamsActions, QString> m_YamsActionsNames = {
		{EYamsActions::ACES, QString::fromUtf8("As")},
		{EYamsActions::TWOS, QString::fromUtf8("Deux")},
		{EYamsActions::THREES, QString::fromUtf8("Trois")},
		{EYamsActions::FOURS, QString::fromUtf8("Quatre")},
		{EYamsActions::FiVES, QString::fromUtf8("Cinq")},
		{EYamsActions::SIXES, QString::fromUtf8("Six")},
		
		{EYamsActions::BRELAN, QString::fromUtf8("Brelan")},
		{EYamsActions::CARRE, QString::fromUtf8("Carré")},
		{EYamsActions::FULL, QString::fromUtf8("Full")},
		{EYamsActions::SMALL_STRAIGHT, QString::fromUtf8("Petite suite")},
		{EYamsActions::LARGE_STRAIGHT, QString::fromUtf8("Grande suite")},
		{EYamsActions::YAMS, QString::fromUtf8("Yams")},
		{EYamsActions::SUPER_YAMS, QString::fromUtf8("Super Yams")},
		{EYamsActions::CHANCE, QString::fromUtf8("Chance")},
	};
	
private:

    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QYams m_ui;

	/**
	 * @brief Vue des grilles des joueurs
	 */
	QPlayerGridsWidget* m_ptrQPlayerGridsWidget;

	/**
	 * @brief Menu de début de jeu
	 *
	 * Permet d'entrer les noms des joueurs
	 */
	QYamsStartFormWidget* m_ptrQYamsStartFrom;

	/**
	 * @brief Widget réalisant la reconnaissance d'image
	 *
	 * La reconnaissance d'image est réalisée grâce à la bibliothèque OpenCV
	 */
	QCameraWidget* m_ptrQCameraWidget;

	/**
	 * @brief Fenêtre "À propos"
	 */
	QAboutWidget* m_ptrAboutWindow = nullptr;

	/**
	 * @brief Menu de fin de jeu
	 *
	 * Affiche le nom du gagnant et des boutons permettant de rejouer ou de quitter le jeu
	 */
	QEndGameWidget* m_ptrEndGameWidget = nullptr;

	/**
	 * @brief Contient la dernière simulation des scores
	 *
	 * La simulation est réutilisée lorsque le joueur choisis quelle action effectuer afin d'éviter de
	 * recalculer plusieurs fois les coups
	 */
	std::map<QYams::EYamsActions, uint> m_mapLastSimulation;
	
    /**
     * @brief Liste contenant toutes les grilles des joueurs
     */
	std::list<QPlayerGrid*> m_lpQPlayerGrids;

	/**
	 * @brief Nombre de lancer effectués durant le tour présent
	 */
	int m_iNbrTurn = 0;

	/**
	 * @brief Joueur actuel
	 *
	 * Itérateur de la liste @link QYams::m_lpQPlayerGrids @endlink
	 * Incrémenté à chaque fin de jours pour obtenir le joueur suivant
	 */
	std::list<QPlayerGrid*>::iterator m_itPlayerGrids;

	/**
	 * @brief Action du bouton "Choix 1"
	 */
	EYamsActions m_choice1;

    /**
     * @brief Action du bouton "Choix 2"
     */
	EYamsActions m_choice2;

    /**
     * @brief Action du bouton "Choix 3"
     */
	EYamsActions m_choice3;
	
public:
    /**
     * @brief Constructeur
     *
     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
     */
	QYams(QWidget *parent = Q_NULLPTR);

	/**
	 * @brief Destructeur
	 */
	~QYams();

	
private:
    /**
     * @brief Action effectué lors de la fermeture de la fenêtre
     *
     * Quitte l'application étant donné que cette fenêtre est la fenêtre principale
     *
     * @param event : QCloseEvent*
     */
	void closeEvent(QCloseEvent* event) override;

	/**
	 * @brief Simule les score pouvant être obtenus avec la combinaison de dés détectée
	 *
	 * @param diceSet : CDiceSet& - Jeu de dés
	 * @param vSortedSimulationResult : std::vector<std::pair<QYams::EYamsActions, uint>>& - Vecteur allant contenir les simulations
	 * triées de la solution optimale à la moins bonne
	 */
	void _simulate(CDiceSet& diceSet, std::vector<std::pair<QYams::EYamsActions, uint>>& vSortedSimulationResult);

	/**
	 * @brief Passe au joueur suivant
	 */
	void _nextPlayer();

	/**
	 * @brief Action à effectuer à la fin de la partie
	 */
	void _onEndGame();

	/**
	 * @brief Remet le ou les bouton(s) de choix à leur état d'origine
	 *
	 * Si le paramètre fourni est EChoices::ANYTHING (valeur par défaut), tous les boutons de choix
	 * seront remis à leur état d'origine
	 *
	 * @param choice : EChoice - Valeur par défaut EChoices::ANYTHING
	 */
	void _resetChoices(EChoices choice = ANYTHING);

	/**
	 * @brief Cache le layout contenant les boutons de choix et le compteur de tour
	 *
	 * @param hide : bool - Si vrai : masque, si faux : affiche
	 */
	void _hideGameBar(bool hide) const;

	/**
	 * @brief Action à effectuer avant de démarrer la partie
	 */
	void _beforeStart();

	/**
	 * @brief Affiche le menu des règles
	 */
	void _showRules();
	
	
public slots:
    /**
     * @brief Démarre une partie
     *
     * Affiche le menu d'entrée des noms de joueur
     */
	void start();

	/**
	 * @brief Redémarre le jeu
	 */
	void restart();

	/**
	 * @brief Quitte l'application
	 */
	void quit();

	/**
	 * @brief Effectue l'action choisie par le joueur
	 *
	 * @param selectedAction : EYamsActions - Action choisie par le joueur
	 */
	void doAction(EYamsActions selectedAction);

	/** TODO : onDiceSetUpdate
	 * @brief Réagit lorsqu'un nouveau jeu de dés est détecté
	 *
	 * @param diceSet : CDiceSet& - Jeu de dés
	 * @param isDetectionCorrection : bool - S'agit-il de la suite d'une erreur signalée par le joueur ?
	 */
	void updateTurn(CDiceSet& diceSet, bool isDetectionCorrection);

	/**
	 * @brief Lance le jeu après la saisie des noms de joueurs
	 *
	 * @param ptrLPlayerNames : std::list<QString>* - Liste des noms saisis
	 */
	void launchGame(std::list<QString>* ptrLPlayerNames);

	/**
	 * @brief Affiche la fenêtre "À propos"
	 */
	void showAboutWindow();

signals:
    /**
     * @brief Signal émit lorsque le tour du joueur a évolué
     *
     * @param playerGrid : QPlayerGrid& - Joueur concerné
     */
	void playerUpdated(QPlayerGrid& playerGrid);


};

#endif // Q_YAMS_H
