#include "QEndGameWidget.hpp"

QEndGameWidget::QEndGameWidget(const QString& sWinnerName, QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	m_ui.lblPlayerName->setText(sWinnerName + QString::fromLatin1(" a gagné !"));
}

QEndGameWidget::~QEndGameWidget()
{
}


