#ifndef QPLAYERGRIDWIDGET_H
#define QPLAYERGRIDWIDGET_H

#pragma once

#include <QWidget>
#include "ui_QPlayerGridWidget.h"

class QPlayerGridWidget : public QWidget
{
	Q_OBJECT

private:
	Ui::QPlayerGridWidget m_ui;

public:
	QPlayerGridWidget(QWidget *parent = Q_NULLPTR);
	~QPlayerGridWidget();


};

#endif // QPLAYERGRIDWIDGET_H
