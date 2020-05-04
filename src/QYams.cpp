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

	m_ptrQCameraWidget = m_ui.qCameraWidget;

	connect(m_ui.btnStart, &QPushButton::clicked, this, &QYams::start);
	connect(m_ui.btnQuit, &QPushButton::clicked, this, &QYams::quit);

	connect(m_ui.actionAbout, &QAction::triggered, this, &QYams::showAboutWindow);
}

void QYams::_updateChoices(std::list<CDice>& lDices)
{
}

void QYams::closeEvent(QCloseEvent* event)
{
	QMainWindow::closeEvent(event);
	
	quit();
}

std::shared_ptr<std::vector<std::pair<QYams::EYamsActions, uint>*>> const QYams::_simulate(int* diceSet)
{
	shared_ptr<vector<pair<EYamsActions, uint>*>> vActionResult = make_shared<vector<pair<EYamsActions, uint>*>>();

	// Simulation pour les as
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::ACES,
		diceSet[0]
		));

	// Simulation pour les deux
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::TWOS,
		diceSet[1]
		));

	// Simulation pour les trois
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::THREES,
		diceSet[2]
		));

	// Simulation pour les quatre
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::FOURS,
		diceSet[3]
		));

	// Simulation pour les cinq
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::FOURS,
		diceSet[4]
		));

	// Simulation pour les six
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::SIXES,
		diceSet[5]
		));
	
	const uint iDiceSum = diceSet[0] + diceSet[1] + diceSet[2] + diceSet[3] + diceSet[4] + diceSet[5];
	uint iSmallStraight = 0;
	uint iLargeStraight = 0;
	uint iYams = 0;
	bool bIsBrelan = false;
	bool bIsCarre = false;
	bool bIsFull = false;

	for (int i = 0; i < 6; ++i)
	{
		// Simulation du Brelan
		if (diceSet[i] == 3)
		{
			bIsBrelan = true;
		}
		
		// Simulation du Carre
		if (diceSet[i] == 3)
		{
			bIsCarre = true;
		}

		// Simulation du Full
		if (!bIsFull)
		{
			for (int j = 0; j < 6; ++j)
			{
				
				if ((diceSet[i] == 3 && diceSet[j] == 2) || (diceSet[i] == 2 && diceSet[j] == 3))
				{
					bIsFull = true;
					break;
				}
			}
		}
		
		// Simulation de la petite suite
		if (diceSet[i] < 1)
		{
			iSmallStraight++;
		}
		else if (iSmallStraight < 4)
		{
			iSmallStraight = 0;
		}

		// Simulation de la grande suite
		if (diceSet[i] < 1)
		{
			iLargeStraight++;
		}
		else if (iLargeStraight < 5)
		{
			iLargeStraight = 0;
		}

		if (diceSet[i] == 1)
		{
			iYams++;
		}
	}

	// Résultat du Brelan
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::BRELAN,
		(bIsBrelan && !m_ptrCurrentPlayer->IsBrelanAlreadySet()) ? iDiceSum : 0
	));

	// Résultat du Carré
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::CARRE,
		(bIsCarre && !m_ptrCurrentPlayer->IsCarreAlreadySet()) ? iDiceSum : 0
	));

	// Résultat du Full
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::FULL,
		(bIsFull && !m_ptrCurrentPlayer->IsFullAlreadySet()) ? 25 : -1
	));

	// Résultat de la petite suite
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::SMALL_STRAIGHT,
		(iSmallStraight < 5 && !m_ptrCurrentPlayer->IsSmallStraightAlreadySet()) ? 30 : 0
	));

	// Résultat de la grande suite
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::LARGE_STRAIGHT,
		(iLargeStraight == 5 && !m_ptrCurrentPlayer->IsLargeStraightAlreadySet()) ? 40 : 0
		));

	// Résultat du Yams
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::YAMS,
		(iYams == 5 && !m_ptrCurrentPlayer->IsYamsAlreadySet()) ? 50 : 0
		));

	// Résultat du super Yams (le Yams doit être réalisé)
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::SUPER_YAMS,
		(iYams == 5 && m_ptrCurrentPlayer->IsYamsAlreadySet() && !m_ptrCurrentPlayer->IsSuperYamsAlreadySet()) ? 100 : 0
		));

	// Simulation de la chance
	vActionResult->push_back(new pair<EYamsActions, uint>(
		EYamsActions::CHANCE,
		iDiceSum
		));

	std::sort(vActionResult->begin(), vActionResult->end(), [](pair<EYamsActions, uint>* a, pair<EYamsActions, uint>* b)
	{
		return a->second > b->second;
	});

	return vActionResult;
}


void QYams::start()
{
	m_ptrQYamsStartFrom = new QYamsStartFormWidget();

	// On veut que la fenêtre reste au dessus et bloque les clics sur les autres fenêtres de l'application
	//m_ptrQYamsStartFrom->setWindowModality(Qt::ApplicationModal);
	m_ptrQYamsStartFrom->show();

	connect(m_ptrQYamsStartFrom, &QYamsStartFormWidget::playerNameSetUp, this, &QYams::launchGame);
}

void QYams::restart()
{
}

void QYams::quit()
{	
	QCoreApplication::quit();
}

void QYams::onChoiceChoosed()
{
}

void QYams::updateTurn(int* const diceSet)
{
	vector<pair<EYamsActions, uint>*> vSimulation = *_simulate(diceSet);
	
	m_ui.btnChoice1->setText(m_YamsActionsNames[vSimulation[0]->first]);
	m_ui.btnChoice1->setEnabled(true);

	m_ui.btnChoice2->setText(m_YamsActionsNames[vSimulation[1]->first]);
	m_ui.btnChoice2->setEnabled(true);

	m_ui.btnChoice3->setText(m_YamsActionsNames[vSimulation[3]->first]);
	m_ui.btnChoice3->setEnabled(true);
}

void QYams::showAboutWindow()
{
	if (m_ptrAboutWindow == nullptr)
	{
		m_ptrAboutWindow = new QAboutWidget();
	}

	// On veut que la fenêtre reste au dessus et bloque les clics sur les autres fenêtres de l'application
	m_ptrAboutWindow->setWindowModality(Qt::ApplicationModal);
	m_ptrAboutWindow->show();
}

void QYams::launchGame(list<QString>* ptrLPlayerNames)
{	
	delete m_ptrQYamsStartFrom;
	
	QPlayerGrid* playerGrid = nullptr;
	
	for (QString sPlayerName : *ptrLPlayerNames)
	{
		playerGrid = new QPlayerGrid(sPlayerName);
		
		m_lpQPlayerGrids.push_back(playerGrid);
		m_ptrQPlayerGridWidget->addGrid(playerGrid);
		
		playerGrid = nullptr;
	}

	m_itPlayerGrids = m_lpQPlayerGrids.begin();
	m_ptrCurrentPlayer = *m_itPlayerGrids;
	
	// Affichage de la grille de jeu
	m_ptrQPlayerGridWidget->show();

	// On masque les boutons de démarrage et de sortie
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();

	// On active les 3 boutons de choix
	m_ui.btnChoice1->setDisabled(true);
	m_ui.btnChoice1->show();
	m_ui.btnChoice2->setDisabled(true);
	m_ui.btnChoice2->show();
	m_ui.btnChoice3->setDisabled(true);
	m_ui.btnChoice3->show();

	connect(m_ptrQCameraWidget, &QCameraWidget::dicesUpdated, this, &QYams::updateTurn);

	delete ptrLPlayerNames;
}
