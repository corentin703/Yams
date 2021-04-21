#include "QYams.hpp"

using namespace std;

QYams::QYams(QWidget *parent)
	: QMainWindow(parent)
{
	try {
		m_ui.setupUi(this);

        m_pQPlayerGridsWidget = m_ui.qPlayerGridsWidget;
        m_pQCameraWidget = m_ui.qCameraWidget;

		_beforeStart();

		// Connexion des boutons démarrer et quitter
		connect(m_ui.btnStart, &QPushButton::clicked, this, &QYams::start);
		connect(m_ui.btnQuit, &QPushButton::clicked, this, &QYams::quit);

		// Connexion des boutons de la barre de menu
		connect(m_ui.actionQuit, &QAction::triggered, this, &QYams::quit);
		connect(m_ui.actionRestart, &QAction::triggered, this, &QYams::restart);
		connect(m_ui.actionAbout, &QAction::triggered, this, &QYams::showAboutWindow);
		connect(m_ui.actionRules, &QAction::triggered, this, &QYams::_showRules);

		// Connexion des boutons choix
		connect(m_ui.btnChoice1, &QPushButton::clicked, [this]() { doAction(m_choice1); });
		connect(m_ui.btnChoice2, &QPushButton::clicked, [this]() { doAction(m_choice2); });
		connect(m_ui.btnChoice3, &QPushButton::clicked, [this]() { doAction(m_choice3); });

		// Connexion des boutons permettant de choisir l'action que l'on veut réaliser
		connect(m_pQPlayerGridsWidget->getAcesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::ACES); });
		connect(m_pQPlayerGridsWidget->getTwosButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::TWOS); });
		connect(m_pQPlayerGridsWidget->getThreeButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::THREES); });
		connect(m_pQPlayerGridsWidget->getFoursButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FOURS); });
		connect(m_pQPlayerGridsWidget->getFivesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FiVES); });
		connect(m_pQPlayerGridsWidget->getSixesButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SIXES); });
		connect(m_pQPlayerGridsWidget->getBrelanButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::BRELAN); });
		connect(m_pQPlayerGridsWidget->getCarreButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::CARRE); });
		connect(m_pQPlayerGridsWidget->getFullButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::FULL); });
		connect(m_pQPlayerGridsWidget->getSmallStraightButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SMALL_STRAIGHT); });
		connect(m_pQPlayerGridsWidget->getLargeStraightButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::LARGE_STRAIGHT); });
		connect(m_pQPlayerGridsWidget->getYamsButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::YAMS); });
		connect(m_pQPlayerGridsWidget->getSuperYamsButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::SUPER_YAMS); });
		connect(m_pQPlayerGridsWidget->getChanceButton(), &QPushButton::clicked, [this]() { doAction(EYamsActions::CHANCE); });

		connect(this, &QYams::playerUpdated, m_pQPlayerGridsWidget, &QPlayerGridsWidget::actualizeActionButtons);
		connect(m_ui.btnRedetection, &QPushButton::clicked, m_pQCameraWidget, &QCameraWidget::onWrongDetection);
		
		_resetChoices();
	
	} catch (cv::Exception& exception) {
		quit_error(exception);
	}
}

QYams::~QYams()
{
//	if (m_pAboutWindow != nullptr)
//		delete m_pAboutWindow;
//
//	if (m_pEndGameWidget != nullptr)
//		delete m_pEndGameWidget;

    if (m_pQPlayerGridsWidget != nullptr)
        delete m_pQPlayerGridsWidget;

    if (m_pQYamsStartFrom != nullptr)
        delete m_pQYamsStartFrom;

    if (m_pQCameraWidget != nullptr)
        delete m_pQCameraWidget;

    if (m_pAboutWindow != nullptr)
        delete m_pAboutWindow;

    if (m_pEndGameWidget != nullptr)
        delete m_pEndGameWidget;

    for (QPlayerGrid* itPlayers : m_lpQPlayerGrids) {
        delete itPlayers;
    }

}

void QYams::closeEvent(QCloseEvent* event)
{
	QMainWindow::closeEvent(event);
	
	quit();
}

void QYams::_simulate(CDiceSet& diceSet, std::vector<std::pair<QYams::EYamsActions, uint>>& vSortedSimulationResult)
{
	m_mapLastSimulation.clear();

	if (!(*m_itPlayerGrids)->isAcesAlreadySet())
	{
		// Simulation pour les as
		m_mapLastSimulation.insert({
			EYamsActions::ACES,
			diceSet.getAces()
		});
	}

	if (!(*m_itPlayerGrids)->isTwosAlreadySet())
	{
		// Simulation pour les deux
		m_mapLastSimulation.insert({
			EYamsActions::TWOS,
			diceSet.getTwos()
		});
	}
	
	if (!(*m_itPlayerGrids)->isThreesAlreadySet())
	{
		// Simulation pour les trois
		m_mapLastSimulation.insert({
			EYamsActions::THREES,
			diceSet.getThrees()
		});
	}
	
	if (!(*m_itPlayerGrids)->isFoursAlreadySet())
	{
		// Simulation pour les quatre
		m_mapLastSimulation.insert({
			EYamsActions::FOURS,
			diceSet.getFours()
		});
	}
	
	if (!(*m_itPlayerGrids)->isFivesAlreadySet())
	{
		// Simulation pour les cinq
		m_mapLastSimulation.insert({
			EYamsActions::FiVES,
			diceSet.getFives()
		});
	}
	
	if (!(*m_itPlayerGrids)->isSixesAlreadySet())
	{
		// Simulation pour les six
		m_mapLastSimulation.insert({
			EYamsActions::SIXES,
			diceSet.getSixes()
		});
	}

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

		// Simulation du Carré
		if (diceSet[i] == 4)
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

	if (!(*m_itPlayerGrids)->isBrelanAlreadySet())
	{
		// Résultat du Brelan
		m_mapLastSimulation.insert({
			EYamsActions::BRELAN,
			(bIsBrelan) ? diceSet.getTotal() : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isCarreAlreadySet())
	{
		// Résultat du Carré
		m_mapLastSimulation.insert({
			EYamsActions::CARRE,
			(bIsCarre) ? diceSet.getTotal() : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isFullAlreadySet())
	{
		// Résultat du Full
		m_mapLastSimulation.insert({
			EYamsActions::FULL,
			(bIsFull) ? 25 : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isSmallStraightAlreadySet())
	{
		// Résultat de la petite suite
		m_mapLastSimulation.insert({
			EYamsActions::SMALL_STRAIGHT,
			(iSmallStraight >= 4) ? 30 : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isLargeStraightAlreadySet())
	{
		// Résultat de la grande suite
		m_mapLastSimulation.insert({
			EYamsActions::LARGE_STRAIGHT,
			(iLargeStraight == 5) ? 40 : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isYamsAlreadySet())
	{
		// Résultat du Yams
		m_mapLastSimulation.insert({
			EYamsActions::YAMS,
			(bYams) ? 50 : 0
		});
	}
	
	if (!(*m_itPlayerGrids)->isSuperYamsAlreadySet())
	{
		// Résultat du super Yams (le Yams doit être réalisé)
		m_mapLastSimulation.insert({
			EYamsActions::SUPER_YAMS,
			(bYams && !((*m_itPlayerGrids)->getYams() == 0)) ? 100 : 0
		});
	}

	if (!(*m_itPlayerGrids)->isChanceAlreadySet())
	{
		// Simulation de la chance
		m_mapLastSimulation.insert({
			EYamsActions::CHANCE,
			diceSet.getTotal()
		});
	}
	
	
	for (pair<EYamsActions, uint> simulation : m_mapLastSimulation)
		vSortedSimulationResult.push_back(simulation);

	std::sort(vSortedSimulationResult.begin(), vSortedSimulationResult.end(), [](pair<QYams::EYamsActions, uint> a, pair<QYams::EYamsActions, uint> b)
	{
		// La chance est à utiliser de préférence en derniers recours
		if (a.first == EYamsActions::CHANCE && b.second > 0)
			return false;
		else if (a.first == EYamsActions::ACES && a.second >= 3) // Si on a plus de 3 aus As, il vaut mieux inscrire les As qu'un Brelan ou un Carré
			return true;
		else if (a.first == EYamsActions::TWOS && a.second >= 6) // Si on a plus de 6 aux deux, il est plus intéressant d'inscrire les deux
			return true;
		else if (a.first == EYamsActions::THREES && a.second >= 9) // Si on a plus de 9 aux trois, il est plus intéressant d'inscrire les deux
			return true;

		// Mêmes vérifications que ci-dessus mais pour b
		if (b.first == EYamsActions::ACES && b.second >= 3)
			return false;
		else if (b.first == EYamsActions::TWOS && b.second >= 6)
			return false;
		else if (b.first == EYamsActions::THREES && b.second >= 9)
			return false;
		
		return a.second > b.second; // Pour le reste on trie selon la grandeur
	});
}

void QYams::_nextPlayer()
{	
	++m_itPlayerGrids;
	
	if (m_itPlayerGrids == m_lpQPlayerGrids.end())
	{
		m_itPlayerGrids = m_lpQPlayerGrids.begin();

		if ((*m_itPlayerGrids)->isGridFinished())
		{
			m_pQPlayerGridsWidget->enableActionButtons(false);
			_onEndGame();
			return;
		}
	}

	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	m_ui.lblPlayerName->setText((*m_itPlayerGrids)->getPlayerName());
	
	_resetChoices();
	m_pQPlayerGridsWidget->enableActionButtons(false);
}

void QYams::_onEndGame()
{
	if (m_pEndGameWidget == nullptr)
		m_pEndGameWidget = new QEndGameWidget((*m_itPlayerGrids)->getPlayerName());
	
	connect(m_pEndGameWidget->getRestartButton(), &QPushButton::clicked, this, &QYams::restart);
	connect(m_pEndGameWidget->getQuitButton(), &QPushButton::clicked, this, &QYams::quit);
	m_pEndGameWidget->setWindowModality(Qt::ApplicationModal);
	m_pEndGameWidget->show();
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
	case YAMS:
		if (m_mapLastSimulation[EYamsActions::YAMS] == 0 && !(*m_itPlayerGrids)->isSuperYamsAlreadySet())
			(*m_itPlayerGrids)->setSuperYams(false); // Le super Yams nécessite que le Yams soit réalisé pour pouvoir être fait
		else 
			(*m_itPlayerGrids)->setYams(m_mapLastSimulation[EYamsActions::YAMS] > 0);
		break;
	case SUPER_YAMS:
		(*m_itPlayerGrids)->setSuperYams(m_mapLastSimulation[EYamsActions::SUPER_YAMS] > 0);
		break;
	case CHANCE :
		(*m_itPlayerGrids)->setChance(m_mapLastSimulation[EYamsActions::CHANCE]);
		break;

	default:
		throw new runtime_error("Choix inconnu");
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

void QYams::_hideGameBar(bool bHide) const
{
	m_ui.lblTurnText->setHidden(bHide);
	m_ui.lblTurn->setHidden(bHide);
	m_ui.lblPlayerNameText->setHidden(bHide);
	m_ui.lblPlayerName->setHidden(bHide);
	m_ui.btnChoice1->setHidden(bHide);
	m_ui.btnChoice2->setHidden(bHide);
	m_ui.btnChoice3->setHidden(bHide);
	m_ui.btnRedetection->setHidden(bHide);
}

void QYams::_beforeStart()
{
	// Affichage des boutons de démarrage et de sortie
	m_ui.btnStart->show();
	m_ui.btnQuit->show();

	m_ui.actionRestart->setEnabled(false);
	m_pQPlayerGridsWidget->hide();

	m_pQPlayerGridsWidget->enableActionButtons(false);
	_hideGameBar(true);
}

void QYams::_showRules()
{
	QMessageBox::information(this, QString::fromUtf8("Règles du Yams"), QString::fromUtf8(
		"<p>"
		"Le Yams ou Yahtzee est un jeu qui se joue avec 5 dés et se finit lorsque tous les joueurs ont remplis leur grille de jeu."
		"Chaque joueur peut tirer jusqu'à 3 fois une partie ou la totalité des dés afin d'arriver au résultat rapportant le plus de points"
		"Le joueur doit obligatoirement inscrire un score dans une des cases de sa feuille à l'issue de chaque tour"
		"(il peut compter 0 s'il n'a obtenu aucun résultat probant)."
		"</p>"
		"<p>"
		"La partie supérieure se complète en inscrivant le total des dés correspondants lors d'un tour"
		"</p>"
		"<h4>Explications des combinaisons de la partie inférieure</h4>"
		"<ul>"
			"<li>Le Brelan : lorsque le joueur obtient 3 dés identiques, il peut compter le total des dés ;</li>"
			"<li>Le Carré : lorsque le joueur obtient 4 dés identiques, il peut compter le total des dés ;</li>"
			"<li>Le Full : lorsque le joueur obtient 3 dés identiques et 2 autres de la même valeur aussi, il peut compter 25 points ;</li>"
			"<li>La petite suite : lorsque le joueur obtient au moins 4 dés dont la valeur se suit, il peut compter 30 points ;</li>"
			"<li>La grande suite : lorsque le joueur obtient au moins 5 dés dont la valeur se suit, il peut compter 40 points ;</li>"
			"<li>Le Yams : lorsque le joueur obtient 5 dés identiques, il peut compter 50 points ;</li>"
			"<li>Le super Yams : lorsque le joueur obtient 5 dés identiques et a déjà réussi un Yams, il peut compter 100 points.</li>"
		"</ul>"
		"</p>"
	));
}

void QYams::start()
{
    m_pQYamsStartFrom = new QYamsStartFormWidget();

	// On veut que la fenêtre reste au dessus et bloque les clics sur les autres fenêtres de l'application
	m_pQYamsStartFrom->show();

	connect(m_pQYamsStartFrom, &QYamsStartFormWidget::playerNameSetUp, this, &QYams::launchGame);
}

void QYams::restart()
{	
	if (m_pEndGameWidget != nullptr)
	{
		disconnect(m_pEndGameWidget->getRestartButton(), &QPushButton::clicked, this, &QYams::restart);
		disconnect(m_pEndGameWidget->getQuitButton(), &QPushButton::clicked, this, &QYams::quit);
		
		delete m_pEndGameWidget;
		m_pEndGameWidget = nullptr;
	}

	for (QPlayerGrid* playerGrid : m_lpQPlayerGrids)
	{
		m_pQPlayerGridsWidget->removeGrid(playerGrid);
		delete playerGrid;
	}
	
	m_lpQPlayerGrids.clear();

	_beforeStart();
	start();
}

inline void QYams::quit(int iCode)
{	
	QCoreApplication::quit();
	std::exit(iCode);
}

inline void QYams::quit_error(cv::Exception& exception) {
	QMessageBox::critical(this, QString::fromUtf8("Erreur"), QString::fromStdString(exception.err));

	quit(exception.code);
}

void QYams::updateTurn(CDiceSet& diceSet, bool isDetectionCorrection)
{
	vector<pair<QYams::EYamsActions, uint>> vSimulation;
	_simulate(diceSet, vSimulation);
	
	if (m_iNbrTurn > 0 || isDetectionCorrection)
	{
		if (vSimulation.size() > 0)
		{
			m_ui.btnChoice1->setText(m_YamsActionsNames[vSimulation[0].first] + " (" + QString::number(vSimulation[0].second) + ")");
			m_choice1 = vSimulation[0].first;
			m_ui.btnChoice1->setEnabled(true);
		}
		else
			_resetChoices(EChoices::ONE);

		if (vSimulation.size() > 1 && vSimulation[1].second > 0)
		{
			m_ui.btnChoice2->setText(m_YamsActionsNames[vSimulation[1].first] + " (" + QString::number(vSimulation[1].second) + ")");
			m_choice2 = vSimulation[1].first;
			m_ui.btnChoice2->setEnabled(true);
		}
		else
			_resetChoices(EChoices::TWO);
		
		if (vSimulation.size() > 2 && vSimulation[2].second > 0)
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
				m_pQPlayerGridsWidget->enableActionButtons(true);
			}

			emit playerUpdated(*(*m_itPlayerGrids));
		}
	}
}

void QYams::showAboutWindow()
{
	if (m_pAboutWindow == nullptr)
        m_pAboutWindow = new QAboutWidget();

	// On veut que la fenêtre reste au dessus et bloque les clics sur les autres fenêtres de l'application
	m_pAboutWindow->setWindowModality(Qt::ApplicationModal);
	m_pAboutWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	m_pAboutWindow->show();
}

void QYams::launchGame(list<QString>* pLPlayerNames)
{	
	delete m_pQYamsStartFrom;
    m_pQYamsStartFrom = nullptr;

	m_ui.actionRestart->setEnabled(true);
	
	QPlayerGrid* playerGrid = nullptr;
	
	for (const QString& sPlayerName : *pLPlayerNames)
	{
		playerGrid = new QPlayerGrid(sPlayerName);
		
		m_lpQPlayerGrids.emplace_back(playerGrid);
		m_pQPlayerGridsWidget->addGrid(playerGrid);
		
		playerGrid = nullptr;
	}
	
	m_itPlayerGrids = m_lpQPlayerGrids.begin();
	
	// Affichage de la grille de jeu
	m_pQPlayerGridsWidget->show();

	// On masque les boutons de démarrage et de sortie
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();

	// On active les 3 boutons de choix et les indicateurs
	_hideGameBar(false);

	m_ui.btnChoice1->setDisabled(true);
	m_ui.btnChoice2->setDisabled(true);
	m_ui.btnChoice3->setDisabled(true);

	m_iNbrTurn = 3;
	m_ui.lblTurn->setText(QString::number(m_iNbrTurn));
	m_ui.lblPlayerName->setText((*m_itPlayerGrids)->getPlayerName());
	
	connect(m_pQCameraWidget, &QCameraWidget::dicesUpdated, this, &QYams::updateTurn);

	delete pLPlayerNames;
}
