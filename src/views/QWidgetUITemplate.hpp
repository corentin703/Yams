#pragma once

#include <QWidget>
#include "ui_QWidgetUITemplate.h"

class QWidgetUITemplate : public QWidget
{
	Q_OBJECT

public:
	QWidgetUITemplate(QWidget *parent = Q_NULLPTR);
	~QWidgetUITemplate();

private:
	Ui::QWidgetUITemplate ui;
};
