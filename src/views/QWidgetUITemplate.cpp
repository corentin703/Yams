#include "QWidgetUITemplate.h"

QWidgetUITemplate::QWidgetUITemplate(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QWidgetUITemplate::~QWidgetUITemplate()
{
}
