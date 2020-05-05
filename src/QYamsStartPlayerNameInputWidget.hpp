#ifndef Q_YAMS_START_PLAYER_NAME_INPUT_WIDGET_H
#define Q_YAMS_START_PLAYER_NAME_INPUT_WIDGET_H

#pragma once

// Qt
#include <QWidget>
#include "ui_QYamsStartPlayerNameInputWidget.h"

class QYamsStartPlayerNameInputWidget : public QWidget
{
	Q_OBJECT

public:
	QYamsStartPlayerNameInputWidget(QWidget* parent = Q_NULLPTR);
	~QYamsStartPlayerNameInputWidget();

	QLineEdit* getPlayerNameInput() const { return m_ui.iptPlayerName; }

private:
	static int ms_iNbrPlayer;
	
	Ui::QYamsStartPlayerNameInputWidget m_ui;
};

#endif // Q_YAMS_START_PLAYER_NAME_INPUT_WIDGET_H
