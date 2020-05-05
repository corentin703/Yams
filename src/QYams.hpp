#ifndef Q_YAMS_H
#define Q_YAMS_H

#pragma once

// STL
#include <list>
#include <map>
#include <memory>

// Qt
#include <QtWidgets/QMainWindow>

#include "QPlayerGridsWidget.hpp"
#include "QYamsStartFormWidget.hpp"
#include "QAboutWidget.hpp"
#include "image_recognition/QCameraWidget.hpp"
#include "models/QPlayerGrid.hpp"
#include "models/CDiceSet.hpp"
#include "QEndGameWidget.hpp"

#include "ui_QYams.h"

class QYams : public QMainWindow
{
	Q_OBJECT

public:

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

	enum EChoices
	{
		ANYTHING = 0,

		ONE = 1,
		TWO = 2,
		THREE = 3,
	};

	std::map<EYamsActions, QString> m_YamsActionsNames = {
		{EYamsActions::ACES, QString::fromLatin1("As")},
		{EYamsActions::TWOS, QString::fromLatin1("Deux")},
		{EYamsActions::THREES, QString::fromLatin1("Trois")},
		{EYamsActions::FOURS, QString::fromLatin1("Quatre")},
		{EYamsActions::FiVES, QString::fromLatin1("Cinq")},
		{EYamsActions::SIXES, QString::fromLatin1("Six")},
		
		{EYamsActions::BRELAN, QString::fromLatin1("Brelan")},
		{EYamsActions::CARRE, QString::fromLatin1("Carré")},
		{EYamsActions::FULL, QString::fromLatin1("Full")},
		{EYamsActions::SMALL_STRAIGHT, QString::fromLatin1("Petite suite")},
		{EYamsActions::LARGE_STRAIGHT, QString::fromLatin1("Grande suite")},
		{EYamsActions::YAMS, QString::fromLatin1("Yams")},
		{EYamsActions::SUPER_YAMS, QString::fromLatin1("Super Yams")},
		{EYamsActions::CHANCE, QString::fromLatin1("Chance")},
	};
	
private:

	Ui::QYams m_ui;
	QPlayerGridsWidget* m_ptrQPlayerGridsWidget;
	QYamsStartFormWidget* m_ptrQYamsStartFrom;
	QCameraWidget* m_ptrQCameraWidget;
	QAboutWidget* m_ptrAboutWindow = nullptr;
	QEndGameWidget* m_ptrEndGameWidget = nullptr;
	

	std::list<QPlayerGrid*> m_lpQPlayerGrids;

	int m_iNbrTurn = 0;
	std::list<QPlayerGrid*>::iterator m_itPlayerGrids;

	EYamsActions m_choice1;
	EYamsActions m_choice2;
	EYamsActions m_choice3;
	
public:
	QYams(QWidget *parent = Q_NULLPTR);

	
private:
	void closeEvent(QCloseEvent* event) override;
	const std::shared_ptr<std::vector<std::pair<QYams::EYamsActions, uint>>> _simulate(CDiceSet& diceSet) const;

	void _nextPlayer();
	void _onEndGame();
	void _resetChoices(EChoices choice = ANYTHING);
	
	
public slots:
	void start();
	void restart();
	void quit();

	void doAction(EYamsActions selectedAction);
	void updateTurn(CDiceSet& diceSet);
	void launchGame(std::list<QString>* ptrLPlayerNames);
	
	void showAboutWindow();

signals:
	void playerUpdated(QPlayerGrid& playerGrid);


};

#endif // Q_YAMS_H
