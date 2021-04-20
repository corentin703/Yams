#include "QPlayerGridsWidget.hpp"

using namespace std;

QPlayerGridsWidget::QPlayerGridsWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

void QPlayerGridsWidget::addGrid(QPlayerGrid* pQPlayerGrid)
{
	const uint playerNumber = m_mapPlayerGridViews.size() + 1;
	unique_ptr<CPlayerGridView> playerGridView = make_unique<CPlayerGridView>(this, pQPlayerGrid->getPlayerName());

	// Ligne 0 : Nom
	m_ui.gridLayout->addWidget(playerGridView->lblPlayerName, 0, playerNumber);

	// Ligne 1 : ligne, le widget est remplacé avec les nouvelles propriétés s'il existe déjà
	m_ui.gridLayout->addWidget(m_ui.linePlayerName, 1, 0, 1, m_ui.gridLayout->columnCount());
	
	// Ligne 2 : As
	m_ui.gridLayout->addWidget(playerGridView->lblAs, 2, playerNumber);
	// Ligne 3 : Deux
	m_ui.gridLayout->addWidget(playerGridView->lblTwos, 3, playerNumber);
	// Ligne 4 : Trois
	m_ui.gridLayout->addWidget(playerGridView->lblThrees, 4, playerNumber);
	// Ligne 5 : Quatre
	m_ui.gridLayout->addWidget(playerGridView->lblFours, 5, playerNumber);
	// Ligne 6 : Cinq
	m_ui.gridLayout->addWidget(playerGridView->lblFives, 6, playerNumber);
	// Ligne 7 : Six
	m_ui.gridLayout->addWidget(playerGridView->lblSixes, 7, playerNumber);
	// Ligne 8 : Pré-total
	m_ui.gridLayout->addWidget(playerGridView->lblPreTotalSup, 8, playerNumber);
	// Ligne 9 : Bonus
	m_ui.gridLayout->addWidget(playerGridView->lblBonus, 9, playerNumber);
	// Ligne 10 : TotalSup
	m_ui.gridLayout->addWidget(playerGridView->lblTotalSup, 10, playerNumber);

	// Ligne 11 : Ligne supérieure
	m_ui.gridLayout->addWidget(m_ui.lineSup, 11, 0, 1, m_ui.gridLayout->columnCount());

	// Ligne 12 : Brelan
	m_ui.gridLayout->addWidget(playerGridView->lblBrelan, 12, playerNumber);
	// Ligne 13 : Carré
	m_ui.gridLayout->addWidget(playerGridView->lblCarre, 13, playerNumber);
	// Ligne 14 : Full
	m_ui.gridLayout->addWidget(playerGridView->lblFull, 14, playerNumber);
	// Ligne 15 : Petite suite
	m_ui.gridLayout->addWidget(playerGridView->lblSmallStraight, 15, playerNumber);
	// Ligne 16 : Grande suite
	m_ui.gridLayout->addWidget(playerGridView->lblLargeStraight, 16, playerNumber);
	// Ligne 17 : Yams
	m_ui.gridLayout->addWidget(playerGridView->lblYams, 17, playerNumber);
	// Ligne 18 : Super Yams
	m_ui.gridLayout->addWidget(playerGridView->lblSuperYams, 18, playerNumber);
	// Ligne 19 : Chance
	m_ui.gridLayout->addWidget(playerGridView->lblChance, 19, playerNumber);
	// Ligne 20 : Total inférieur
	m_ui.gridLayout->addWidget(playerGridView->lblTotalInf, 20, playerNumber);

	// Ligne 21 : Ligne inférieure
	m_ui.gridLayout->addWidget(m_ui.lineInf, 21, 0, 1, m_ui.gridLayout->columnCount());

	// Ligne 22 : Total
	m_ui.gridLayout->addWidget(playerGridView->lblTotal, 22, playerNumber);
	
	
	m_mapPlayerGridViews.insert({
		pQPlayerGrid,
		std::move(playerGridView)
	});
	
	connect(pQPlayerGrid, &QPlayerGrid::gridUpdated, this, &QPlayerGridsWidget::updateGrid);

}

void QPlayerGridsWidget::removeGrid(QPlayerGrid* pQPlayerGrid)
{
	m_mapPlayerGridViews.erase(pQPlayerGrid);
}

void QPlayerGridsWidget::actualizeActionButtons(QPlayerGrid& playerGrid) const
{
	m_ui.btnAces->setEnabled(!playerGrid.isAcesAlreadySet());
	m_ui.btnTwos->setEnabled(!playerGrid.isTwosAlreadySet());
	m_ui.btnThrees->setEnabled(!playerGrid.isThreesAlreadySet());
	m_ui.btnFours->setEnabled(!playerGrid.isFoursAlreadySet());
	m_ui.btnFives->setEnabled(!playerGrid.isFivesAlreadySet());
	m_ui.btnSixes->setEnabled(!playerGrid.isSixesAlreadySet());

	m_ui.btnBrelan->setEnabled(!playerGrid.isBrelanAlreadySet());
	m_ui.btnCarre->setEnabled(!playerGrid.isCarreAlreadySet());
	m_ui.btnFull->setEnabled(!playerGrid.isFullAlreadySet());
	m_ui.btnSmallStraight->setEnabled(!playerGrid.isSmallStraightAlreadySet());
	m_ui.btnLargeStraight->setEnabled(!playerGrid.isLargeStraightAlreadySet());
	m_ui.btnYams->setEnabled(!playerGrid.isYamsAlreadySet());
	m_ui.btnSuperYams->setEnabled(!playerGrid.isSuperYamsAlreadySet());
	m_ui.btnChance->setEnabled(!playerGrid.isChanceAlreadySet());
}

void QPlayerGridsWidget::updateGrid(QPlayerGrid* pQPlayerGrid)
{
	// Partie supérieure
	m_mapPlayerGridViews[pQPlayerGrid]->lblAs->setText(QString::number(pQPlayerGrid->getAces()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblTwos->setText(QString::number(pQPlayerGrid->getTwos()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblThrees->setText(QString::number(pQPlayerGrid->getThrees()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblFours->setText(QString::number(pQPlayerGrid->getFours()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblFives->setText(QString::number(pQPlayerGrid->getFives()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblSixes->setText(QString::number(pQPlayerGrid->getSixes()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblPreTotalSup->setText(QString::number(pQPlayerGrid->getPreUpperTotal()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblBonus->setText(QString::number(pQPlayerGrid->getBonus()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblTotalSup->setText(QString::number(pQPlayerGrid->getUpperTotal()));
	
	// Partie inférieure
	m_mapPlayerGridViews[pQPlayerGrid]->lblBrelan->setText(QString::number(pQPlayerGrid->getBrelan()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblCarre->setText(QString::number(pQPlayerGrid->getCarre()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblFull->setText(QString::number(pQPlayerGrid->getFull()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblSmallStraight->setText(QString::number(pQPlayerGrid->getSmallStraight()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblLargeStraight->setText(QString::number(pQPlayerGrid->getLargeStraight()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblYams->setText(QString::number(pQPlayerGrid->getYams()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblChance->setText(QString::number(pQPlayerGrid->getChance()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblSuperYams->setText(QString::number(pQPlayerGrid->getSuperYams()));
	m_mapPlayerGridViews[pQPlayerGrid]->lblTotalInf->setText(QString::number(pQPlayerGrid->getLowerTotal()));

	// Total global
	m_mapPlayerGridViews[pQPlayerGrid]->lblTotal->setText(QString::number(pQPlayerGrid->getTotal()));
}

void QPlayerGridsWidget::enableActionButtons(bool bEnable) const
{
	m_ui.btnAces->setEnabled(bEnable);
	m_ui.btnTwos->setEnabled(bEnable);
	m_ui.btnThrees->setEnabled(bEnable);
	m_ui.btnFours->setEnabled(bEnable);
	m_ui.btnFives->setEnabled(bEnable);
	m_ui.btnSixes->setEnabled(bEnable);

	m_ui.btnBrelan->setEnabled(bEnable);
	m_ui.btnCarre->setEnabled(bEnable);
	m_ui.btnFull->setEnabled(bEnable);
	m_ui.btnSmallStraight->setEnabled(bEnable);
	m_ui.btnLargeStraight->setEnabled(bEnable);
	m_ui.btnYams->setEnabled(bEnable);
	m_ui.btnSuperYams->setEnabled(bEnable);
	m_ui.btnChance->setEnabled(bEnable);
}

QPlayerGridsWidget::CPlayerGridView::CPlayerGridView(QPlayerGridsWidget* parent, const QString& sPlayerName)
{
	lblPlayerName = new QLabel(sPlayerName, parent);
	lblPlayerName->setAlignment(Qt::AlignHCenter);
	
	lblAs = new QLabel("0", parent);
	lblAs->setAlignment(Qt::AlignHCenter);
	lblTwos = new QLabel("0", parent);
	lblTwos->setAlignment(Qt::AlignHCenter);
	lblThrees = new QLabel("0", parent);
	lblThrees->setAlignment(Qt::AlignHCenter);
	lblFours = new QLabel("0", parent);
	lblFours->setAlignment(Qt::AlignHCenter);
	lblFives = new QLabel("0", parent);
	lblFives->setAlignment(Qt::AlignHCenter);
	lblSixes = new QLabel("0", parent);
	lblSixes->setAlignment(Qt::AlignHCenter);
	lblPreTotalSup = new QLabel("0", parent);
	lblPreTotalSup->setAlignment(Qt::AlignHCenter);
	lblBonus = new QLabel("0", parent);
	lblBonus->setAlignment(Qt::AlignHCenter);
	lblTotalSup = new QLabel("0", parent);
	lblTotalSup->setAlignment(Qt::AlignHCenter);

	lblBrelan = new QLabel("0", parent);
	lblBrelan->setAlignment(Qt::AlignHCenter);
	lblCarre = new QLabel("0", parent);
	lblCarre->setAlignment(Qt::AlignHCenter);
	lblFull = new QLabel("0", parent);
	lblFull->setAlignment(Qt::AlignHCenter);
	lblSmallStraight = new QLabel("0", parent);
	lblSmallStraight->setAlignment(Qt::AlignHCenter);
	lblLargeStraight = new QLabel("0", parent);
	lblLargeStraight->setAlignment(Qt::AlignHCenter);
	lblYams = new QLabel("0", parent);
	lblYams->setAlignment(Qt::AlignHCenter);
	lblSuperYams = new QLabel("0", parent);
	lblSuperYams->setAlignment(Qt::AlignHCenter);
	lblChance = new QLabel("0", parent);
	lblChance->setAlignment(Qt::AlignHCenter);
	lblTotalInf = new QLabel("0", parent);
	lblTotalInf->setAlignment(Qt::AlignHCenter);

	lblTotal = new QLabel("0", parent);
	lblTotal->setAlignment(Qt::AlignHCenter);
}

QPlayerGridsWidget::CPlayerGridView::~CPlayerGridView()
{
	delete lblPlayerName;
	 
	delete lblAs;
	delete lblTwos;
	delete lblThrees;
	delete lblFours;
	delete lblFives;
	delete lblSixes;
	delete lblPreTotalSup;
	delete lblBonus;
	delete lblTotalSup;
	 
	delete lblBrelan;
	delete lblCarre;
	delete lblFull;
	delete lblSmallStraight;
	delete lblLargeStraight;
	delete lblYams;
	delete lblSuperYams;
	delete lblChance;
	delete lblTotalInf;
	 
	delete lblTotal;
}
