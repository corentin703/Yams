#include "QPlayerGridWidget.hpp"

QPlayerGridWidget::QPlayerGridWidget(QWidget *parent, QPlayerGrid* ptrPlayerGrid)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	m_ptrQPlayerGrids = ptrPlayerGrid;

	// On défini le nom du joueur
	m_ui.lblPlayerName->setText(m_ptrQPlayerGrids->getPlayerName());
}

QPlayerGridWidget::~QPlayerGridWidget()
{
}

void QPlayerGridWidget::updateGrid()
{
	// Partie supérieure
	m_ui.lbl1->setText(QString::number(m_ptrQPlayerGrids->getAces()));
	m_ui.lbl2->setText(QString::number(m_ptrQPlayerGrids->getTwos()));
	m_ui.lbl3->setText(QString::number(m_ptrQPlayerGrids->getThrees()));
	m_ui.lbl4->setText(QString::number(m_ptrQPlayerGrids->getFours()));
	m_ui.lbl5->setText(QString::number(m_ptrQPlayerGrids->getFives()));
	m_ui.lbl6->setText(QString::number(m_ptrQPlayerGrids->getSixes()));
	m_ui.lblPreTotalSup->setText(QString::number(m_ptrQPlayerGrids->getPreUpperTotal()));
	m_ui.lblBonus->setText(QString::number(m_ptrQPlayerGrids->getBonus()));
	m_ui.lblTotalSup->setText(QString::number(m_ptrQPlayerGrids->getUpperTotal()));

	// Partie inférieure
	m_ui.lblBrelan->setText(QString::number(m_ptrQPlayerGrids->getBrelan()));
	m_ui.lblCarre->setText(QString::number(m_ptrQPlayerGrids->getCarre()));
	m_ui.lblFull->setText(QString::number(m_ptrQPlayerGrids->getFull()));
	m_ui.lblSmallStraight->setText(QString::number(m_ptrQPlayerGrids->getSmallStraight()));
	m_ui.lblLargeStraight->setText(QString::number(m_ptrQPlayerGrids->getLargeStraight()));
	m_ui.lblYams->setText(QString::number(m_ptrQPlayerGrids->getYams()));
	m_ui.lblChance->setText(QString::number(m_ptrQPlayerGrids->getChance()));
	m_ui.lblSuperYams->setText(QString::number(m_ptrQPlayerGrids->getSuperYams()));
	m_ui.lblTotalInf->setText(QString::number(m_ptrQPlayerGrids->getLowerTotal()));

	// Total global
	m_ui.lblTotal->setText(QString::number(m_ptrQPlayerGrids->getTotal()));
}
