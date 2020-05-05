#include "QYams.hpp"

using namespace std;

QYams::QYams(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.wdgGameBar->hide();

	// Affichage des boutons de démarrage et de sortie
	m_ui.btnStart->show();
	m_ui.btnQuit->show();

	m_ptrQPlayerGridsWidget = m_ui.qPlayerGridsWidget;
	m_ptrQPlayerGridsWidget->hide();

	m_ptrQCameraWidget = m_ui.qCameraWidget;

	// Connexion des boutons démarrer et quitter
	connect(m_ui.btnStart, &QPushButton::clicked, this, &QYams::start);
	connect(m_ui.btnQuit, &QPushButton::clicked, this, &QYams::quit);

	// Connexion du bouton À propos
	connect(m_ui.actionAbout, &QAction::triggered, this, &QYams::showAboutWindow);

	// Connexion des boutons choix
	connect(m_ui.btnChoice1, &QPushButton::clicked, [this]() { doAction(m_choice1); });
	connect(m_ui.btnChoice2, &QPushButton::clicked, [this]() { doAction(m_choice2); });
	connect(m_ui.btnChoice3, &QPushButton::clicked, [this]() { doAction(m_choice3); });

	connect(m_ptrQPlayerGridsWidget->getAcesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::ACES); });
	connect(m_ptrQPlayerGridsWidget->getTwosButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::TWOS); });
	connect(m_ptrQPlayerGridsWidget->getThreeButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::THREES); });
	connect(m_ptrQPlayerGridsWidget->getFoursButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FOURS); });
	connect(m_ptrQPlayerGridsWidget->getFivesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FiVES); });
	connect(m_ptrQPlayerGridsWidget->getSixesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SIXES); });
	
	connect(m_ptrQPlayerGridsWidget->getBrelanButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::BRELAN); });
	connect(m_ptrQPlayerGridsWidget->getCarreButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::CARRE); });
	connect(m_ptrQPlayerGridsWidget->getFullButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FULL); });
	connect(m_ptrQPlayerGridsWidget->getSmallStraightButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SMALL_STRAIGHT); });
	connect(m_ptrQPlayerGridsWidget->getLargeStraightButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::LARGE_STRAIGHT); });
	connect(m_ptrQPlayerGridsWidget->getYamsButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::YAMS); });
	connect(m_ptrQPlayerGridsWidget->getSuperYamsButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SUPER_YAMS); });
	connect(m_ptrQPlayerGridsWidget->getChanceButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::CHANCE); });

	_resetChoices();
}

void QYams::_updateChoices(std::list<CDice>& lDices)
{
}

void QYams::closeEvent(QCloseEvent* event)
{
	QMainWindow::closeEvent(event);
	
	quit();
}

std::shared_ptr<std::vector<std::pair<QYams::EYamsActions, uint>>> const QYams::_simulate(CDiceSet& diceSet)
{
	shared_ptr<vector<pair<QYams::EYamsActions, uint>>> vActionResult = make_shared<vector<pair<EYamsActions, uint>>>();

	// Simulation pour les as
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::ACES,
		diceSet[1]
		));

	// Simulation pour les deux
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::TWOS,
		diceSet[2] * 2
		));

	// Simulation pour les trois
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::THREES,
		diceSet[3] * 3
		));

	// Simulation pour les quatre
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::FOURS,
		diceSet[4] * 4
		));

	// Simulation pour les cinq
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::FiVES,
		diceSet[5] * 5
		));

	// Simulation pour les six
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::SIXES,
		diceSet[6] * 6
		));
	
	uint iSmallStraight = 0;
	uint iLargeStraight = 0;
	uint iYams = 0;
	bool bIsBrelan = false;
	bool bIsCarre = false;
	bool bIsFull = false;

	for (int i = 1; i <= 6; ++i)
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
			for (int j = 1; j <= 6; ++j)
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
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::BRELAN,
		(bIsBrelan && !m_ptrCurrentPlayer->IsBrelanAlreadySet()) ? diceSet.getTotal() : 0
	));

	// Résultat du Carré
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::CARRE,
		(bIsCarre && !m_ptrCurrentPlayer->IsCarreAlreadySet()) ? diceSet.getTotal() : 0
	));

	// Résultat du Full
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::FULL,
		(bIsFull && !m_ptrCurrentPlayer->IsFullAlreadySet()) ? 25 : 0
	));

	// Résultat de la petite suite
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::SMALL_STRAIGHT,
		(iSmallStraight >= 4 && !m_ptrCurrentPlayer->IsSmallStraightAlreadySet()) ? 30 : 0
	));

	// Résultat de la grande suite
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::LARGE_STRAIGHT,
		(iLargeStraight == 5 && !m_ptrCurrentPlayer->IsLargeStraightAlreadySet()) ? 40 : 0
		));

	// Résultat du Yams
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::YAMS,
		(iYams == 5 && !m_ptrCurrentPlayer->IsYamsAlreadySet()) ? 50 : 0
		));

	// Résultat du super Yams (le Yams doit être réalisé)
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::SUPER_YAMS,
		(iYams == 5 && m_ptrCurrentPlayer->IsYamsAlreadySet() && !m_ptrCurrentPlayer->IsSuperYamsAlreadySet()) ? 100 : 0
		));

	// Simulation de la chance
	vActionResult->push_back(pair<EYamsActions, uint>(
		EYamsActions::CHANCE,
		diceSet.getTotal()
		));

	std::sort(vActionResult->begin(), vActionResult->end(), [](pair<QYams::EYamsActions, uint> a, pair<QYams::EYamsActions, uint> b)
	{
		return a.second > b.second;
	});

	return vActionResult;
}


void QYams::doAction(const EYamsActions& selectedAction)
{
	CDiceSet diceSet = m_ptrQCameraWidget->getDiceSet();
	
	switch (selectedAction)
	{
	case ACES :
		QMessageBox::information(this, " OK", "OJ1");
		m_ptrCurrentPlayer->setAces(diceSet[1]);
		break;
	case TWOS :
		QMessageBox::information(this, " OK", "OJ2");
		m_ptrCurrentPlayer->setTwos(diceSet[2]);
		break;
	case THREES :
		QMessageBox::information(this, " OK", "OJ3");
		m_ptrCurrentPlayer->setThrees(diceSet[3]);
		break;
	case FOURS :
		QMessageBox::information(this, " OK", "OJ4");
		m_ptrCurrentPlayer->setFours(diceSet[4]);
		break;
	case FiVES :
		QMessageBox::information(this, " OK", "OJ5");
		m_ptrCurrentPlayer->setFives(diceSet[5]);
		break;
	case SIXES :
		QMessageBox::information(this, " OK", "OJ6");
		m_ptrCurrentPlayer->setSixes(diceSet[6]);
		break;

	case BRELAN :
		m_ptrCurrentPlayer->setBrelan(diceSet.getTotal());
		break;
	case CARRE :
		m_ptrCurrentPlayer->setCarre(diceSet.getTotal());
		break;
	case FULL :
		m_ptrCurrentPlayer->setFull(true);
		break;
	case SMALL_STRAIGHT :
		m_ptrCurrentPlayer->setSmallStraight(true);
		break;
	case LARGE_STRAIGHT :
		m_ptrCurrentPlayer->setLargeStraight(true);
		break;
	case YAMS :
		m_ptrCurrentPlayer->setYams(true);
		break;
	case SUPER_YAMS :
		m_ptrCurrentPlayer->setSuperYams(true);
		break;
	case CHANCE :
		m_ptrCurrentPlayer->setChance(diceSet.getTotal());
		break;

	default:
		throw new exception("Choix inconnu");
	}

	++m_itPlayerGrids;
	if (m_itPlayerGrids == m_lpQPlayerGrids.end())
	{
		m_itPlayerGrids = m_lpQPlayerGrids.begin();
	}
	
	m_ptrCurrentPlayer = *m_itPlayerGrids;

	
	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	
	_resetChoices();
}

void QYams::_resetChoices(const EChoices& choice)
{
	if (choice == ONE || choice == ANYTHING)
	{
		m_ui.btnChoice1->setText("Choix 1");
		m_choice1 = EYamsActions::NOTHING;
		m_ui.btnChoice1->setEnabled(false);
	}

	if (choice == TWO || choice == ANYTHING)
	{
		m_ui.btnChoice2->setText("Choix 2");
		m_choice2 = EYamsActions::NOTHING;
		m_ui.btnChoice2->setEnabled(false);
	}

	if (choice == THREE || choice == ANYTHING)
	{
		m_ui.btnChoice3->setText("Choix 3");
		m_choice3 = EYamsActions::NOTHING;
		m_ui.btnChoice3->setEnabled(false);
	}
}

void QYams::start()
{
	m_ptrQYamsStartFrom = new QYamsStartFormWidget();

	// On veut que la fenêtre reste au dessus et bloque les clics sur les autres fenêtres de l'application
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

void QYams::updateTurn(CDiceSet& diceSet)
{	
	vector<pair<QYams::EYamsActions, uint>> vSimulation = *_simulate(diceSet);
	
	if (m_iNbrTurn > 0)
	{
		m_ui.btnChoice1->setText(m_YamsActionsNames[vSimulation[0].first - 1] + " (" + QString::number(vSimulation[0].second) + ")");
		m_choice1 = vSimulation[0].first;
		m_ui.btnChoice1->setEnabled(true);

		if (vSimulation[1].second > 0)
		{
			m_ui.btnChoice2->setText(m_YamsActionsNames[vSimulation[1].first - 1] + " (" + QString::number(vSimulation[1].second) + ")");
			m_choice2 = vSimulation[1].first;
			m_ui.btnChoice2->setEnabled(true);
		}
		else
		{
			_resetChoices(EChoices::TWO);
		}
		
		if (vSimulation[2].second > 0)
		{
			m_ui.btnChoice3->setText(m_YamsActionsNames[vSimulation[2].first - 1] + " (" + QString::number(vSimulation[2].second) + ")");
			m_choice3 = vSimulation[2].first;
			m_ui.btnChoice3->setEnabled(true);
		}
		else
		{
			_resetChoices(EChoices::THREE);
		}

		--m_iNbrTurn;
		m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	}
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
		m_ptrQPlayerGridsWidget->addGrid(playerGrid);
		
		playerGrid = nullptr;
	}

	m_itPlayerGrids = m_lpQPlayerGrids.begin();
	m_ptrCurrentPlayer = *m_itPlayerGrids;
	
	// Affichage de la grille de jeu
	m_ptrQPlayerGridsWidget->show();

	// On masque les boutons de démarrage et de sortie
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();

	// On active les 3 boutons de choix
	m_ui.wdgGameBar->show();

	m_ui.btnChoice1->setDisabled(true);
	m_ui.btnChoice2->setDisabled(true);
	m_ui.btnChoice3->setDisabled(true);

	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	
	connect(m_ptrQCameraWidget, &QCameraWidget::dicesUpdated, this, &QYams::updateTurn);

	delete ptrLPlayerNames;
}
