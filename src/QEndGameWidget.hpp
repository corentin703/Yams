#ifndef Q_END_GAME_WIDGET_H
#define Q_END_GAME_WIDGET_H

#pragma once

#include <QWidget>
#include <QMessageBox>

//#include "QYams.hpp"
#include "ui_QEndGameWidget.h"

class QEndGameWidget : public QWidget
{
	Q_OBJECT

public:
	QEndGameWidget(const QString& sWinnerName, QWidget* parent = Q_NULLPTR);
	~QEndGameWidget();

	const QPushButton* getQuitButton() const { return m_ui.btnQuit; }
	const QPushButton* getRestartButton() const { return m_ui.btnRestart; }
	
private:
	Ui::QEndGameWidget m_ui;
	
};

#endif // Q_END_GAME_WIDGET_H