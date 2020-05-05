#include "QPlayerGridsWidget.hpp"

QPlayerGridsWidget::QPlayerGridsWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

QPlayerGridsWidget::~QPlayerGridsWidget()
{
}

void QPlayerGridsWidget::addGrid(QPlayerGrid* const ptrQPlayerGrids)
{	
	// Si la vue n'existe pas pour cette grille, on la crée
	QPlayerGridWidget* qPlayerGridWidget = new QPlayerGridWidget(this, ptrQPlayerGrids);
	connect(ptrQPlayerGrids, &QPlayerGrid::gridUpdated, qPlayerGridWidget, &QPlayerGridWidget::updateGrid);
	m_ui.horizontalLayout->addWidget(qPlayerGridWidget);
	emit ptrQPlayerGrids->gridUpdated();
}
