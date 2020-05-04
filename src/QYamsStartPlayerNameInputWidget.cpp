#include "QYamsStartPlayerNameInputWidget.hpp"

int QYamsStartPlayerNameInputWidget::ms_iNbrPlayer = 1;

QYamsStartPlayerNameInputWidget::QYamsStartPlayerNameInputWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	m_ui.lblPlayerNbr->setText(QString::number(ms_iNbrPlayer));
	ms_iNbrPlayer++;
}

QYamsStartPlayerNameInputWidget::~QYamsStartPlayerNameInputWidget()
{
	if (ms_iNbrPlayer > 0)
	{
		ms_iNbrPlayer--;
	}
}

