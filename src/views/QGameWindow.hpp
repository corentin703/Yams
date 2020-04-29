#ifndef QGAMEWINDOW_H
#define QGAMEWINDOW_H

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QGameWindow.h"

class QGameWindow : public QMainWindow
{
	Q_OBJECT

public:
	QGameWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::QGameWindow m_ui;
};

#endif // QGAMEWINDOW_H
