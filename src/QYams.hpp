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

#include "ui_QYams.h"

class QYams : public QMainWindow
{
	Q_OBJECT

	Ui::QYams m_ui;
	QPlayerGridsWidget* m_ptrQPlayerGridWidget;
	QYamsStartFormWidget* m_ptrQYamsStartFrom;
	QCameraWidget* m_ptrQCameraWidget;
	QAboutWidget* m_ptrAboutWindow = nullptr;

	std::list<QPlayerGrid*> m_lpQPlayerGrids;
	QPlayerGrid* m_ptrCurrentPlayer;

	int m_iNbrTurn = 0;
	std::list<QPlayerGrid*>::iterator m_itPlayerGrids;

public:
	
	enum EYamsActions
	{
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
	
	QYams(QWidget *parent = Q_NULLPTR);

private:
	void _updateChoices(std::list<CDice>& const lDices);
	void closeEvent(QCloseEvent* event) override;
	std::shared_ptr<std::vector<std::pair<EYamsActions, uint>*>> const _simulate(int* diceSet);

	QString m_YamsActionsNames[14] = {
		QString::fromLatin1("As"),
		QString::fromLatin1("Deux"),
		QString::fromLatin1("Trois"),
		QString::fromLatin1("Quatre"),
		QString::fromLatin1("Cinq"),
		QString::fromLatin1("Six"),

		QString::fromLatin1("Brelan"),
		QString::fromLatin1("Carré"),
		QString::fromLatin1("Full"),
		QString::fromLatin1("Petite suite"),
		QString::fromLatin1("Grande suite"),
		QString::fromLatin1("Yams"),
		QString::fromLatin1("Super Yams"),
		QString::fromLatin1("Chance"),
	};
	
	
public slots:
	void start();
	void restart();
	void quit();
	void onChoiceChoosed();
	void updateTurn(int* const diceSet);
	void launchGame(std::list<QString>* ptrLPlayerNames);
	
	void showAboutWindow();


};

#endif // Q_YAMS_H
