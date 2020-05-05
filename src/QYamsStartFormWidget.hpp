#ifndef Q_YAMS_START_FORM_WIDGET_H
#define Q_YAMS_START_FORM_WIDGET_H

#pragma once

// STL
#include <list>

// Qt
#include <QWidget>
#include "ui_QYamsStartFormWidget.h"

#include "QYamsStartPlayerNameInputWidget.hpp"

class QYamsStartFormWidget : public QWidget
{
	Q_OBJECT

public:
	QYamsStartFormWidget(QWidget* parent = Q_NULLPTR);
	~QYamsStartFormWidget();

private:
	Ui::QYamsStartFormWidget m_ui;

	std::list<QLineEdit*> m_lPlayerNameInputs;

private slots:
	void addPlayerNameInput();
	void onPlayerNameSetUp();

signals:
	void playerNameSetUp(std::list<QString>* ptrLPlayerNames);
};

#endif // Q_YAMS_START_FORM_WIDGET_H
