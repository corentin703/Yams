#ifndef Q_YAMS_START_FORM_WIDGET_H
#define Q_YAMS_START_FORM_WIDGET_H

#pragma once

// STL
#include <list>
#include <memory>

// Qt
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

// UI
#include "ui_QYamsStartFormWidget.h"

/**
 * @brief Fenêtre de saisie des noms de joueur
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QYamsStartFormWidget : public QWidget
{
	Q_OBJECT

	/**
	 * @brief Encapsule le numéro et le champ de texte pour un joueur
	 */
	class CPlayerForm
	{
	    /**
	     * @brief Layout horizontal
	     *
	     * Contient un label à gauche et un champ de texte à droite
	     */
		QHBoxLayout* m_HBoxLayout;

		/**
		 * @brief Label visant affichant le numéro du joueur
		 */
		QLabel* m_lblPlayerNum;

		/**
		 * @brief Champ de texte visant à accueillir le nom du joueur
		 */
		QLineEdit* m_iptPlayerName;
		
	public:
	    /**
	     * @brief Constructeur
	     *
	     * @param parent : QYamsStartFormWidget*
	     * @param iPlayerNumber : uint - Numéro du joueur
	     */
		CPlayerForm(QYamsStartFormWidget* parent, uint iPlayerNumber);

		/**
		 * @brief Retourne le nom saisi par l'utilisateur
		 *
		 * @return QString
		 */
		QString getInputName() const { return m_iptPlayerName->text(); }

		/**
		 * @brief Retourne le layout
		 *
		 * @return QHBoxLayout*
		 */
		QHBoxLayout* getQWidget() const { return m_HBoxLayout; }
	};

public:
    /**
	     * @brief Constructeur
	     *
	     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
	     */
	QYamsStartFormWidget(QWidget* parent = Q_NULLPTR);
	
private:
    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QYamsStartFormWidget m_ui;

	/**
	 * @brief Contient les différentes entrées de noms des joueurs
	 */
	std::list<std::unique_ptr<CPlayerForm>> m_lPlayerNameInputs;

private slots:
    /**
     * @brief Ajoute une entrée supplémentaire pour ajouter un joueur à la liste
     */
	void addPlayerNameInput();

	/**
	 * @brief Action à réaliser lorsque l'utilisateur confirme la saisie
	 *
	 * Vérifie si les saisies ne sont pas vides puis envoie le résulat à @link QYams::launchGame @endlink
	 */
	void onPlayerNameSetUp();

signals:
    /**
     * @brief Signal que les noms sont saisis
     *
     * @param ptrLPlayerNames : std::list<QString>* - Liste des noms saisis
     */
	void playerNameSetUp(std::list<QString>* ptrLPlayerNames);
};

#endif // Q_YAMS_START_FORM_WIDGET_H
