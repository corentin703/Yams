#include "QYamsStartFormWidget.hpp"

using namespace std;

QYamsStartFormWidget::QYamsStartFormWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	m_lPlayerNameInputs.push_back(m_ui.player_1->getPlayerNameInput());
	m_lPlayerNameInputs.push_back(m_ui.player_2->getPlayerNameInput());

	connect(m_ui.btnAddPlayer, &QPushButton::clicked, this, &QYamsStartFormWidget::addPlayerNameInput);
	connect(m_ui.btnSubmit, &QPushButton::clicked, this, &QYamsStartFormWidget::onPlayerNameSetUp);
}

QYamsStartFormWidget::~QYamsStartFormWidget()
{
}

void QYamsStartFormWidget::addPlayerNameInput()
{
	QYamsStartPlayerNameInputWidget* qPlayerNameInput = new QYamsStartPlayerNameInputWidget(this);
	m_ui.lytInputs->addWidget(qPlayerNameInput);
	m_lPlayerNameInputs.push_back(qPlayerNameInput->getPlayerNameInput());
}

void QYamsStartFormWidget::onPlayerNameSetUp()
{
	list<QString>* ptrLPlayerNames = new list<QString>();

	for (QLineEdit* playerNameIpt : m_lPlayerNameInputs)
	{
		ptrLPlayerNames->push_back(playerNameIpt->text());
	}

	emit playerNameSetUp(ptrLPlayerNames);
}
