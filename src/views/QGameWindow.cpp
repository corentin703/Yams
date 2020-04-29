#include "QGameWindow.hpp"

QGameWindow::QGameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.btnChoice1->hide();
	m_ui.btnChoice2->hide();
	m_ui.btnChoice3->hide();
	m_ui.btnStart->hide();
	m_ui.btnQuit->hide();
}
