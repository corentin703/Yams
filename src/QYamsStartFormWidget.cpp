#include "QYamsStartFormWidget.hpp"

using namespace std;

QYamsStartFormWidget::CPlayerForm::CPlayerForm(QYamsStartFormWidget* parent, uint iPlayerNumber)
{
	m_HBoxLayout = new QHBoxLayout(parent);
	
	m_lblPlayerNum = new QLabel(QString::number(iPlayerNumber), parent);
	m_iptPlayerName = new QLineEdit(parent);
	m_iptPlayerName->setPlaceholderText("Entrez un nom ici");

	m_HBoxLayout->addWidget(m_lblPlayerNum);
	m_HBoxLayout->addWidget(m_iptPlayerName);
	m_HBoxLayout->setAlignment(Qt::AlignHCenter);
	m_HBoxLayout->setSpacing(10);
}

QYamsStartFormWidget::QYamsStartFormWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.btnAddPlayer, &QPushButton::clicked, this, &QYamsStartFormWidget::addPlayerNameInput);
	connect(m_ui.btnSubmit, &QPushButton::clicked, this, &QYamsStartFormWidget::onPlayerNameSetUp);

	addPlayerNameInput();
	addPlayerNameInput();
}

void QYamsStartFormWidget::addPlayerNameInput()
{
	unique_ptr<CPlayerForm> playerForm = make_unique<CPlayerForm>(this, m_lPlayerNameInputs.size() + 1);
	
	m_ui.lytInputs->addLayout(playerForm->getQWidget());
	m_lPlayerNameInputs.push_back(std::move(playerForm));
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
		QMessageBox::warning(this, QString::fromLatin1("Erreur"), QString::fromLatin1(
			"Vous devez entrer au moins deux noms. \n"
			"Aucun champ ne doit être vide"));
	}
	
	
}
