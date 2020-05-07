#include "QYams.hpp"

using namespace std;

QYams::QYams(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ptrQPlayerGridsWidget = m_ui.qPlayerGridsWidget;
	m_ptrQCameraWidget = m_ui.qCameraWidget;

	_beforeStart();

	// Connexion des boutons d�marrer et quitter
	connect(m_ui.btnStart, &QPushButton::clicked, this, &QYams::start);
	connect(m_ui.btnQuit, &QPushButton::clicked, this, &QYams::quit);

	// Connexion des boutons de la barre de menu
	connect(m_ui.actionQuit, &QAction::triggered, this, &QYams::quit);
	connect(m_ui.actionRestart, &QAction::triggered, this, &QYams::restart);
	connect(m_ui.actionAbout, &QAction::triggered, this, &QYams::showAboutWindow);

	// Connexion des boutons choix
	connect(m_ui.btnChoice1, &QPushButton::clicked, [this]() { doAction(m_choice1); });
	connect(m_ui.btnChoice2, &QPushButton::clicked, [this]() { doAction(m_choice2); });
	connect(m_ui.btnChoice3, &QPushButton::clicked, [this]() { doAction(m_choice3); });

	// Connexion des boutons permettant de choisir l'action que l'on veut r�aliser
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

	connect(this, &QYams::playerUpdated, m_ptrQPlayerGridsWidget, &QPlayerGridsWidget::actualizeActionButtons);
	connect(m_ui.btnRedetection, &QPushButton::clicked, m_ptrQCameraWidget, &QCameraWidget::onWrongDetection);
	
	_resetChoices();
}

void QYams::closeEvent(QCloseEvent* event)
{
	QMainWindow::closeEvent(event);
	
	quit();
}

void QYams::_simulate(CDiceSet& diceSet, std::vector<std::pair<QYams::EYamsActions, uint>>& vSortedSimulationResult)
{
	m_mapLastSimulation.clear();
	
	// Simulation pour les as
	m_mapLastSimulation.insert({
		EYamsActions::ACES,
		(!(*m_itPlayerGrids)->isAcesAlreadySet()) ? diceSet.getAces() : 0
	});

	// Simulation pour les deux
	m_mapLastSimulation.insert({
		EYamsActions::TWOS,
		(!(*m_itPlayerGrids)->isTwosAlreadySet()) ? diceSet.getTwos() : 0
		});

	// Simulation pour les trois
	m_mapLastSimulation.insert({
		EYamsActions::THREES,
		(!(*m_itPlayerGrids)->isThreesAlreadySet()) ? diceSet.getThrees() : 0
		});

	// Simulation pour les quatre
	m_mapLastSimulation.insert({
		EYamsActions::FOURS,
		(!(*m_itPlayerGrids)->isFoursAlreadySet()) ? diceSet.getFours() : 0
		});

	// Simulation pour les cinq
	m_mapLastSimulation.insert({
		EYamsActions::FiVES,
		(!(*m_itPlayerGrids)->isFivesAlreadySet()) ? diceSet.getFives() : 0
	});

	// Simulation pour les six
	m_mapLastSimulation.insert({
		EYamsActions::SIXES,
		(!(*m_itPlayerGrids)->isSixesAlreadySet()) ? diceSet.getSixes() : 0
		});

	uint iSmallStraight = 0;
	uint iLargeStraight = 0;
	bool bIsBrelan = false;
	bool bIsCarre = false;
	bool bIsFull = false;
	bool bYams = false;

	for (int i = 1; i <= 6; ++i)
	{
		// Simulation du Brelan
		if (diceSet[i] == 3)
			bIsBrelan = true;

		// Simulation du Carre
		if (diceSet[i] == 3)
			bIsCarre = true;

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
		if (diceSet[i] >= 1)
			iSmallStraight++;
		else if (iSmallStraight < 4)
			iSmallStraight = 0;

		// Simulation de la grande suite
		if (diceSet[i] >= 1)
			iLargeStraight++;
		else if (iLargeStraight < 5)
			iLargeStraight = 0;

		if (diceSet[i] == 5)
			bYams = true;
	}

	// R�sultat du Brelan
	m_mapLastSimulation.insert({
		EYamsActions::BRELAN,
		(bIsBrelan && !(*m_itPlayerGrids)->isBrelanAlreadySet()) ? diceSet.getTotal() : 0
		});

	// R�sultat du Carr�
	m_mapLastSimulation.insert({
		EYamsActions::CARRE,
		(bIsCarre && !(*m_itPlayerGrids)->isCarreAlreadySet()) ? diceSet.getTotal() : 0
		});

	// R�sultat du Full
	m_mapLastSimulation.insert({
		EYamsActions::FULL,
		(bIsFull && !(*m_itPlayerGrids)->isFullAlreadySet()) ? 25 : 0
		});

	// R�sultat de la petite suite
	m_mapLastSimulation.insert({
		EYamsActions::SMALL_STRAIGHT,
		(iSmallStraight >= 4 && !(*m_itPlayerGrids)->isSmallStraightAlreadySet()) ? 30 : 0
		});

	// R�sultat de la grande suite
	m_mapLastSimulation.insert({
		EYamsActions::LARGE_STRAIGHT,
		(iLargeStraight == 5 && !(*m_itPlayerGrids)->isLargeStraightAlreadySet()) ? 40 : 0
		});

	// R�sultat du Yams
	m_mapLastSimulation.insert({
		EYamsActions::YAMS,
		(bYams && !(*m_itPlayerGrids)->isYamsAlreadySet()) ? 50 : 0
		});

	// R�sultat du super Yams (le Yams doit �tre r�alis�)
	m_mapLastSimulation.insert({
		EYamsActions::SUPER_YAMS,
		(bYams && (*m_itPlayerGrids)->isYamsAlreadySet() && !(*m_itPlayerGrids)->getYams() == 0 && !(*m_itPlayerGrids)->IsSuperYamsAlreadySet()) ? 100 : 0
		});

	// Simulation de la chance
	m_mapLastSimulation.insert({
		EYamsActions::CHANCE,
		(!(*m_itPlayerGrids)->isChanceAlreadySet()) ? diceSet.getTotal() : 0
	});
	
	for (pair<EYamsActions, uint> simulation : m_mapLastSimulation)
		vSortedSimulationResult.push_back(simulation);

	std::sort(vSortedSimulationResult.begin(), vSortedSimulationResult.end(), [](pair<QYams::EYamsActions, uint> a, pair<QYams::EYamsActions, uint> b)
	{
		if (a.first == EYamsActions::CHANCE && b.second > 0)
			return false;
		
		return a.second > b.second;
	});
}

void QYams::_nextPlayer()
{
	++m_itPlayerGrids;
	
	if (m_itPlayerGrids == m_lpQPlayerGrids.end())
		m_itPlayerGrids = m_lpQPlayerGrids.begin();
	else if ((*m_itPlayerGrids)->isGridFinished())
	{
		_onEndGame();
		return;
	}

	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));

	emit playerUpdated(*(*m_itPlayerGrids));
	
	_resetChoices();
	m_ptrQPlayerGridsWidget->enableActionButtons(false);
}

void QYams::_onEndGame()
{
	m_ptrEndGameWidget = new QEndGameWidget((*m_itPlayerGrids)->getPlayerName(), this);
	connect(m_ptrEndGameWidget->getRestartButton(), &QPushButton::clicked, this, &QYams::restart);
	connect(m_ptrEndGameWidget->getQuitButton(), &QPushButton::clicked, this, &QYams::quit);
}

void QYams::doAction(EYamsActions selectedAction)
{	
	switch (selectedAction)
	{
	case ACES :
		(*m_itPlayerGrids)->setAces(m_mapLastSimulation[EYamsActions::ACES]);
		break;
	case TWOS :
		(*m_itPlayerGrids)->setTwos(m_mapLastSimulation[EYamsActions::TWOS]);
		break;
	case THREES :
		(*m_itPlayerGrids)->setThrees(m_mapLastSimulation[EYamsActions::THREES]);
		break;
	case FOURS :
		(*m_itPlayerGrids)->setFours(m_mapLastSimulation[EYamsActions::FOURS]);
		break;
	case FiVES :
		(*m_itPlayerGrids)->setFives(m_mapLastSimulation[EYamsActions::FiVES]);
		break;
	case SIXES :
		(*m_itPlayerGrids)->setSixes(m_mapLastSimulation[EYamsActions::SIXES]);
		break;

	case BRELAN :
		(*m_itPlayerGrids)->setBrelan(m_mapLastSimulation[EYamsActions::BRELAN]);
		break;
	case CARRE :
		(*m_itPlayerGrids)->setCarre(m_mapLastSimulation[EYamsActions::CARRE]);
		break;
	case FULL :
		(*m_itPlayerGrids)->setFull(m_mapLastSimulation[EYamsActions::FULL] > 0);
		break;
	case SMALL_STRAIGHT :
		(*m_itPlayerGrids)->setSmallStraight(m_mapLastSimulation[EYamsActions::SMALL_STRAIGHT] > 0);
		break;
	case LARGE_STRAIGHT :
		(*m_itPlayerGrids)->setLargeStraight(m_mapLastSimulation[EYamsActions::LARGE_STRAIGHT] > 0);
		break;
	case YAMS :
		(*m_itPlayerGrids)->setYams(m_mapLastSimulation[EYamsActions::YAMS] > 0);
		break;
	case SUPER_YAMS :
		(*m_itPlayerGrids)->setSuperYams(m_mapLastSimulation[EYamsActions::SUPER_YAMS] > 0);
		break;
	case CHANCE :
		(*m_itPlayerGrids)->setChance(m_mapLastSimulation[EYamsActions::CHANCE]);
		break;

	default:
		throw new exception("Choix inconnu");
	}

	_nextPlayer();
}

void QYams::_resetChoices(EChoices choice)
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

	if (choice == ANYTHING)
		m_ui.btnRedetection->setEnabled(false);
}

void QYams::_hideGameBar(bool hide)
{
	m_ui.lblTurnText->setHidden(hide);
	m_ui.lblTurn->setHidden(hide);
	m_ui.btnChoice1->setHidden(hide);
	m_ui.btnChoice2->setHidden(hide);
	m_ui.btnChoice3->setHidden(hide);
	m_ui.btnRedetection->setHidden(hide);
}

void QYams::_beforeStart()
{
	// Affichage des boutons de d�marrage et de sortie
	m_ui.btnStart->show();
	m_ui.btnQuit->show();

	m_ui.actionRestart->setEnabled(false);
	m_ptrQPlayerGridsWidget->hide();

	m_ptrQPlayerGridsWidget->enableActionButtons(false);
	_hideGameBar(true);
}

void QYams::start()
{
	m_ptrQYamsStartFrom = new QYamsStartFormWidget();

	// On veut que la fen�tre reste au dessus et bloque les clics sur les autres fen�tres de l'application
	m_ptrQYamsStartFrom->show();

	connect(m_ptrQYamsStartFrom, &QYamsStartFormWidget::playerNameSetUp, this, &QYams::launchGame);
}

void QYams::restart()
{	
	if (m_ptrEndGameWidget != nullptr)
	{
		disconnect(m_ptrEndGameWidget->getRestartButton(), &QPushButton::clicked, this, &QYams::restart);
		disconnect(m_ptrEndGameWidget->getQuitButton(), &QPushButton::clicked, this, &QYams::quit);
		
		delete m_ptrEndGameWidget;
		m_ptrEndGameWidget = nullptr;
	}

	for (QPlayerGrid* playerGrid : m_lpQPlayerGrids)
	{
		m_ptrQPlayerGridsWidget->removeGrid(playerGrid);
		delete playerGrid;
	}
	
	m_lpQPlayerGrids.clear();

	_beforeStart();
	start();
}

void QYams::quit()
{	
	QCoreApplication::quit();
}

void QYams::updateTurn(CDiceSet& diceSet, bool isDetectionCorrection)
{
	vector<pair<QYams::EYamsActions, uint>> vSimulation;
	_simulate(diceSet, vSimulation);
	
	if (m_iNbrTurn > 0 || isDetectionCorrection)
	{
		m_ui.btnChoice1->setText(m_YamsActionsNames[vSimulation[0].first] + " (" + QString::number(vSimulation[0].second) + ")");
		m_choice1 = vSimulation[0].first;
		m_ui.btnChoice1->setEnabled(true);

		if (vSimulation[1].second > 0)
		{
			m_ui.btnChoice2->setText(m_YamsActionsNames[vSimulation[1].first] + " (" + QString::number(vSimulation[1].second) + ")");
			m_choice2 = vSimulation[1].first;
			m_ui.btnChoice2->setEnabled(true);
		}
		else
			_resetChoices(EChoices::TWO);
		
		if (vSimulation[2].second > 0)
		{
			m_ui.btnChoice3->setText(m_YamsActionsNames[vSimulation[2].first] + " (" + QString::number(vSimulation[2].second) + ")");
			m_choice3 = vSimulation[2].first;
			m_ui.btnChoice3->setEnabled(true);
		}
		else
			_resetChoices(EChoices::THREE);

		if (!isDetectionCorrection)
		{
			--m_iNbrTurn;
			m_ui.lblTurn->setText(QString::number(m_iNbrTurn));

			if (!m_ui.btnRedetection->isEnabled())
			{
				m_ui.btnRedetection->setEnabled(true);
				m_ptrQPlayerGridsWidget->enableActionButtons(true);
			}
		}
	}
}

void QYams::showAboutWindow()
{
	if (m_ptrAboutWindow == nullptr)
		m_ptrAboutWindow = new QAboutWidget();

	// On veut que la fen�tre reste au dessus et bloque les clics sur les autres fen�tres de l'application
	m_ptrAboutWindow->setWindowModality(Qt::ApplicationModal);
	m_ptrAboutWindow->show();
}

void QYams::launchGame(list<QString>* ptrLPlayerNames)
{	
	delete m_ptrQYamsStartFrom;

	m_ui.actionRestart->setEnabled(true);
	
	QPlayerGrid* playerGrid = nullptr;
	
	for (const QString& sPlayerName : *ptrLPlayerNames)
	{
		playerGrid = new QPlayerGrid(sPlayerName);
		
		m_lpQPlayerGrids.emplace_back(playerGrid);
		m_ptrQPlayerGridsWidget->addGrid(playerGrid);
		
		playerGrid = nullptr;
	}
	
	m_itPlayerGrids = m_lpQPlayerGrids.begin();
	
	// Affichage de la grille de jeu
	m_ptrQPlayerGridsWidget->show();

	// On masque les boutons de d�marrage et de sortie
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();

	// On active les 3 boutons de choix
	_hideGameBar(false);

	m_ui.btnChoice1->setDisabled(true);
	m_ui.btnChoice2->setDisabled(true);
	m_ui.btnChoice3->setDisabled(true);

	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	
	connect(m_ptrQCameraWidget, &QCameraWidget::dicesUpdated, this, &QYams::updateTurn);

	delete ptrLPlayerNames;
}
