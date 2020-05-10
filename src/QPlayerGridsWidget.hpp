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

class QPlayerGridsWidget : public QWidget
{
	Q_OBJECT

	class CPlayerGridView
	{
	public :
		QLabel* lblPlayerName;
		
		QLabel* lblAs;
		QLabel* lblTwos;
		QLabel* lblThrees;
		QLabel* lblFours;
		QLabel* lblFives;
		QLabel* lblSixes;
		QLabel* lblPreTotalSup;
		QLabel* lblBonus;
		QLabel* lblTotalSup;
		
		QLabel* lblBrelan;
		QLabel* lblCarre;
		QLabel* lblFull;
		QLabel* lblSmallStraight;
		QLabel* lblLargeStraight;
		QLabel* lblYams;
		QLabel* lblSuperYams;
		QLabel* lblChance;
		QLabel* lblTotalInf;
		
		QLabel* lblTotal;

		CPlayerGridView(QPlayerGridsWidget* parent, const QString& sPlayerName);
		~CPlayerGridView();
	};
	
private:
	Ui::QPlayerGridsWidget m_ui;

	std::map<QPlayerGrid*, std::unique_ptr<CPlayerGridView>> m_mapPlayerGridViews;
	

public:
	QPlayerGridsWidget(QWidget *parent = Q_NULLPTR);

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
	
	void addGrid(QPlayerGrid* ptrQPlayerGrid);
	void removeGrid(QPlayerGrid* ptrQPlayerGrid);
	void enableActionButtons(bool bEnable) const;

public slots:
	void actualizeActionButtons(QPlayerGrid& playerGrid) const;
	void updateGrid(QPlayerGrid* ptrQPlayerGrid);
};

#endif // Q_PLAYER_GRIDS_WIDGET_H
