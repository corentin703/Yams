#ifndef QPLAYERGRIDWIDGET_H
#define QPLAYERGRIDWIDGET_H

#pragma once

// STL
#include <list>
#include <map>

// Qt
#include <QWidget>
#include "ui_QPlayerGridWidget.h"

#include "models/QPlayerGrid.hpp"

class QPlayerGridWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::QPlayerGridWidget m_ui;
	QPlayerGrid* m_ptrQPlayerGrids;

public:
	QPlayerGridWidget(QWidget* parent, QPlayerGrid* ptrPlayerGrid);
	~QPlayerGridWidget();

public slots:
	void updateGrid();
	
};

#endif // QPLAYERGRIDWIDGET_H
