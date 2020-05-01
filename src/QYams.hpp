#ifndef QYAMS_H
#define QYAMS_H

#pragma once

// STL
#include <list>

// Qt
#include <QtWidgets/QMainWindow>

#include "QPlayerGridsWidget.hpp"
#include "models/QPlayerGrid.hpp"

#include "ui_QYams.h"

class QYams : public QMainWindow
{
	Q_OBJECT

	Ui::QYams m_ui;
	QPlayerGridsWidget* m_ptrQPlayerGridWidget;

	std::list<QPlayerGrid*> m_lpQPlayerGrids;
	QPlayerGrid* m_ptrCurrentPlayer;

	int m_iNbrTurn = 0;

public:
	QYams(QWidget *parent = Q_NULLPTR);

private:
	void _updateChoices(std::list<CDice>& const lDices);

private slots:
	void start();
	void restart();
	void quit();
	void updateGrid();
	void onChoiceChoosed();
	void updateTurn(std::list<CDice>& lDices);


};

#endif // QYAMS_H
