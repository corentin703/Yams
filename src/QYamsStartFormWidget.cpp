#include "QYamsStartFormWidget.hpp"

using namespace std;

#include <QDebug>

QYamsStartFormWidget::CPlayerForm::CPlayerForm(QYamsStartFormWidget* parent, uint iPlayerNumber)
{
	m_HBoxLayout = new QHBoxLayout();
	
	m_lblPlayerNum = new QLabel(QString::number(iPlayerNumber));
	m_iptPlayerName = new QLineEdit();
	m_iptPlayerName->setPlaceholderText("Entrez un nom ici");

	m_HBoxLayout->addWidget(m_lblPlayerNum);
	m_HBoxLayout->addWidget(m_iptPlayerName);
	m_HBoxLayout->setAlignment(Qt::AlignHCenter);
	m_HBoxLayout->setSpacing(10);
}

QYamsStartFormWidget::CPlayerForm::~CPlayerForm()
{
	delete(m_lblPlayerNum);
	delete(m_iptPlayerName);
	delete(m_HBoxLayout);
}

QYamsStartFormWidget::QYamsStartFormWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.btnAddPlayer, &QPushButton::clicked, this, &QYamsStartFormWidget::addPlayerNameInput);
	connect(m_ui.btnDeletePlayer, &QPushButton::clicked, this, &QYamsStartFormWidget::deletePlayerNameInput);
	connect(m_ui.btnSubmit, &QPushButton::clicked, this, &QYamsStartFormWidget::onPlayerNameSetUp);

	addPlayerNameInput();
	addPlayerNameInput();
}

void QYamsStartFormWidget::addPlayerNameInput()
{
	unique_ptr<CPlayerForm> playerForm = make_unique<CPlayerForm>(this, m_lPlayerNameInputs.size() + 1);

	m_ui.verticalLayout->insertLayout(m_lPlayerNameInputs.size(), playerForm->getLayout());
	m_lPlayerNameInputs.push_back(std::move(playerForm));
}

void QYamsStartFormWidget::deletePlayerNameInput()
{
	unique_ptr<CPlayerForm> playerForm = std::move(m_lPlayerNameInputs.back());
	m_lPlayerNameInputs.pop_back();
	m_ui.verticalLayout->removeItem(playerForm->getLayout());
}

void QYamsStartFormWidget::onPlayerNameSetUp()
{
	try
	{
		list<QString>* ptrLPlayerNames = new list<QString>();

		for (unique_ptr<CPlayerForm>& playerNameIpt : m_lPlayerNameInputs)
		{
			if (playerNameIpt->getInputName() < 1)
				throw new runtime_error("Nom trop court");
			
			ptrLPlayerNames->push_back(playerNameIpt->getInputName());
		}

		emit playerNameSetUp(ptrLPlayerNames);
		
	} catch (exception* exception)
	{
		QMessageBox::warning(this, QString::fromUtf8("Erreur"), QString::fromUtf8(
			"Vous devez entrer au moins deux noms. \n"
			"Aucun champ ne doit être vide"));
	}
}
