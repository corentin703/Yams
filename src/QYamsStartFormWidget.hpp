#ifndef Q_YAMS_START_FORM_WIDGET_H
#define Q_YAMS_START_FORM_WIDGET_H

#pragma once

// STL
#include <list>
#include <memory>

// Qt
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

// UI
#include "ui_QYamsStartFormWidget.h"

class QYamsStartFormWidget : public QWidget
{
	Q_OBJECT

	class CPlayerForm
	{
		QHBoxLayout* m_HBoxLayout;
		QLabel* m_lblPlayerNum;
		QLineEdit* m_iptPlayerName;
		
	public:
		CPlayerForm(QYamsStartFormWidget* parent, uint iPlayerNumber);

		QString getInputName() const { return m_iptPlayerName->text(); }
		QHBoxLayout* getQWidget() const { return m_HBoxLayout; }
	};

public:
	QYamsStartFormWidget(QWidget* parent = Q_NULLPTR);
	
private:
	Ui::QYamsStartFormWidget m_ui;

	std::list<std::unique_ptr<CPlayerForm>> m_lPlayerNameInputs;

private slots:
	void addPlayerNameInput();
	void onPlayerNameSetUp();

signals:
	void playerNameSetUp(std::list<QString>* ptrLPlayerNames);
};

#endif // Q_YAMS_START_FORM_WIDGET_H
