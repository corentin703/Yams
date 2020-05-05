#include "QPlayerGridsWidget.hpp"

QPlayerGridsWidget::QPlayerGridsWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

QPlayerGridsWidget::~QPlayerGridsWidget()
{
}

void QPlayerGridsWidget::addGrid(QPlayerGrid* ptrQPlayerGrids)
{	
	// Si la vue n'existe pas pour cette grille, on la crée
	QPlayerGridWidget* qPlayerGridWidget = new QPlayerGridWidget(this, ptrQPlayerGrids);
	connect(ptrQPlayerGrids, &QPlayerGrid::gridUpdated, qPlayerGridWidget, &QPlayerGridWidget::updateGrid);
	m_ui.horizontalLayout->addWidget(qPlayerGridWidget);
	emit ptrQPlayerGrids->gridUpdated();
}

void QPlayerGridsWidget::actualizeActionButtons(QPlayerGrid& playerGrid) const
{
	m_ui.btnAces->setEnabled(!playerGrid.IsAcesAlreadySet());
	m_ui.btnTwos->setEnabled(!playerGrid.IsTwosAlreadySet());
	m_ui.btnThrees->setEnabled(!playerGrid.IsThreesAlreadySet());
	m_ui.btnFours->setEnabled(!playerGrid.IsFoursAlreadySet());
	m_ui.btnFives->setEnabled(!playerGrid.IsFivesAlreadySet());
	m_ui.btnSixes->setEnabled(!playerGrid.IsSixesAlreadySet());

	m_ui.btnBrelan->setEnabled(!playerGrid.IsBrelanAlreadySet());
	m_ui.btnCarre->setEnabled(!playerGrid.IsCarreAlreadySet());
	m_ui.btnFull->setEnabled(!playerGrid.IsFullAlreadySet());
	m_ui.btnSmallStraight->setEnabled(!playerGrid.IsSmallStraightAlreadySet());
	m_ui.btnLargeStraight->setEnabled(!playerGrid.IsLargeStraightAlreadySet());
	m_ui.btnYams->setEnabled(!playerGrid.IsYamsAlreadySet());
	m_ui.btnSuperYams->setEnabled(!playerGrid.IsSuperYamsAlreadySet());
	m_ui.btnChance->setEnabled(!playerGrid.IsChanceAlreadySet());
}
