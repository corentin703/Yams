#ifndef Q_ABOUT_WIDGET_H
#define Q_ABOUT_WIDGET_H

#pragma once

#include <QWidget>
#include <QMessageBox>

#include <opencv2/core.hpp>

#include "ui_QAboutWidget.h"

class QAboutWidget : public QWidget
{
	Q_OBJECT

public:
	QAboutWidget(QWidget* parent = Q_NULLPTR);
	~QAboutWidget();
	
private:
	Ui::QAboutWidget m_ui;
	
public slots:
	void showAboutQtWindow();
	void showAboutOpenCVWindow();
	
};

#endif // Q_ABOUT_WIDGET_H