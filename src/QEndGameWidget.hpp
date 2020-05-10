#ifndef Q_END_GAME_WIDGET_H
#define Q_END_GAME_WIDGET_H

#pragma once

// Qt
#include <QWidget>
#include <QMessageBox>

// UI
#include "ui_QEndGameWidget.h"

/**
 * @brief Menu de fin de partie
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QEndGameWidget : public QWidget
{
	Q_OBJECT

public:
    /**
     * @brief Constructeur
     *
     * @param sWinnerName : QString& - Nom du joueur
     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
     */
	QEndGameWidget(const QString& sWinnerName, QWidget* parent = Q_NULLPTR);

	/**
	 * @brief Retourne le bouton quitter
	 *
	 * @return const QPushButton*
	 */
	const QPushButton* getQuitButton() const { return m_ui.btnQuit; }

    /**
     * @brief Retourne le bouton redémarrer
     *
     * @return const QPushButton*
     */
	const QPushButton* getRestartButton() const { return m_ui.btnRestart; }
	
private:
    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QEndGameWidget m_ui;
	
};

#endif // Q_END_GAME_WIDGET_H