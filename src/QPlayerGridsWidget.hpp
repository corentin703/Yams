#ifndef Q_PLAYER_GRIDS_WIDGET_H
#define Q_PLAYER_GRIDS_WIDGET_H

#pragma once

// STL
//#include <list>
#include <memory>

// Qt
#include <QWidget>
#include "ui_QPlayerGridsWidget.h"

#include "QPlayerGridWidget.hpp"
#include "models/QPlayerGrid.hpp"

class QPlayerGridsWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::QPlayerGridsWidget m_ui;

public:
	QPlayerGridsWidget(QWidget *parent = Q_NULLPTR);
	~QPlayerGridsWidget();

	const QPushButton* getAcesButton() { return m_ui.btnAces; }
	const QPushButton* getTwosButton() { return m_ui.btnTwos; }
	const QPushButton* getThreeButton() { return m_ui.btnThrees; }
	const QPushButton* getFoursButton() { return m_ui.btnFours; }
	const QPushButton* getFivesButton() { return m_ui.btnFives; }
	const QPushButton* getSixesButton() { return m_ui.btnSixes; }
	
	const QPushButton* getBrelanButton() { return m_ui.btnBrelan; }
	const QPushButton* getCarreButton() { return m_ui.btnCarre; }
	const QPushButton* getFullButton() { return m_ui.btnFull; }
	const QPushButton* getSmallStraightButton() { return m_ui.btnSmallStraight; }
	const QPushButton* getLargeStraightButton() { return m_ui.btnLargeStraight; }
	const QPushButton* getYamsButton() { return m_ui.btnYams; }
	const QPushButton* getChanceButton() { return m_ui.btnChance; }
	const QPushButton* getSuperYamsButton() { return m_ui.btnSuperYams; }
	
	void addGrid(QPlayerGrid* const ptrQPlayerGrids);

};

#endif // Q_PLAYER_GRIDS_WIDGET_H
