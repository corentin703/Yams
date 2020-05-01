#include "QYams.hpp"

using namespace std;

QYams::QYams(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.btnChoice1->hide();
	m_ui.btnChoice1->setText("Choix 1");
	m_ui.btnChoice2->hide();
	m_ui.btnChoice2->setText("Choix 2");
	m_ui.btnChoice3->hide();
	m_ui.btnChoice3->setText("Choix 3");

	// Affichage des boutons de démarrage et de sortie
	m_ui.btnStart->show();
	m_ui.btnQuit->show();

	m_ptrQPlayerGridWidget = m_ui.qPlayerGridsWidget;
	m_ptrQPlayerGridWidget->hide();

	connect(this, &QMainWindow::destroyed, this, &QYams::quit);
	connect(m_ui.btnStart, &QPushButton::clicked, this, &QYams::start);
}

void QYams::_updateChoices(std::list<CDice>& lDices)
{
}

void QYams::start()
{
	/*QMessageBox messageBox;
	messageBox.setText(QString::fromLatin1("Démarrage"));
	messageBox.exec();*/

	// Affichage de la grille de jeu
	m_ptrQPlayerGridWidget->show();

	// On masque les boutons de démarrage et de sortie
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();

	// On active les 3 boutons de choix
	m_ui.btnChoice1->show();
	m_ui.btnChoice2->show();
	m_ui.btnChoice3->show();

	m_ptrCurrentPlayer = new QPlayerGrid("Corentin");
	m_lpQPlayerGrids.push_back(m_ptrCurrentPlayer);
	m_ptrQPlayerGridWidget->addGrid(m_ptrCurrentPlayer);
	
}

void QYams::restart()
{
}

void QYams::quit()
{	
	QCoreApplication::quit();
}

void QYams::updateGrid()
{
}

void QYams::onChoiceChoosed()
{
}

void QYams::updateTurn(std::list<CDice>& lDices)
{
}
