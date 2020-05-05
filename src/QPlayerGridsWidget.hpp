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

	const QPushButton* getAcesButton() const { return m_ui.btnAces; }
	const QPushButton* getTwosButton() const { return m_ui.btnTwos; }
	const QPushButton* getThreeButton() const { return m_ui.btnThrees; }
	const QPushButton* getFoursButton() const { return m_ui.btnFours; }
	const QPushButton* getFivesButton() const { return m_ui.btnFives; }
	const QPushButton* getSixesButton() const { return m_ui.btnSixes; }
	
	const QPushButton* getBrelanButton() const { return m_ui.btnBrelan; }
	const QPushButton* getCarreButton() const { return m_ui.btnCarre; }
	const QPushButton* getFullButton() const { return m_ui.btnFull; }
	const QPushButton* getSmallStraightButton() const { return m_ui.btnSmallStraight; }
	const QPushButton* getLargeStraightButton() const { return m_ui.btnLargeStraight; }
	const QPushButton* getYamsButton() const { return m_ui.btnYams; }
	const QPushButton* getChanceButton() const { return m_ui.btnChance; }
	const QPushButton* getSuperYamsButton() const { return m_ui.btnSuperYams; }
	
	void addGrid(QPlayerGrid* ptrQPlayerGrids);

public slots:
	void actualizeActionButtons(QPlayerGrid& playerGrid) const;
};

#endif // Q_PLAYER_GRIDS_WIDGET_H
