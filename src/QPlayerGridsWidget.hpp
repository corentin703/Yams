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
	//std::list<QPlayerGridWidget*> m_lQPlayerGridWidget*;

public:
	QPlayerGridsWidget(QWidget *parent = Q_NULLPTR);
	~QPlayerGridsWidget();

	void addGrid(QPlayerGrid* const ptrQPlayerGrids);

};

#endif // Q_PLAYER_GRIDS_WIDGET_H
