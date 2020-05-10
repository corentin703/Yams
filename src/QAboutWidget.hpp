#ifndef Q_ABOUT_WIDGET_H
#define Q_ABOUT_WIDGET_H

#pragma once

// Qt
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

// OpenCV
#include <opencv2/core.hpp>

// UI
#include "ui_QAboutWidget.h"

/**
 * @brief Menu À propos de l'application
 *
 * @author Corentin VÉROT
 * @date 2020-05-15
 */
class QAboutWidget : public QWidget
{
	Q_OBJECT

public:
    /**
     * @brief Contructeur
     *
     * @param parent : QWidget* - Widget parent, défaut Q_NULLPTR
     */
	QAboutWidget(QWidget* parent = Q_NULLPTR);
	
private:
    /**
     * @brief Interface utilisateur / vue
     */
	Ui::QAboutWidget m_ui;
	
public slots:
    /**
     * @brief Affiche la fenêtre "About Qt"
     */
	void showAboutQtWindow();

    /**
    * @brief Crée et affiche une fenêtre "About OpenCV"
     *
     * Cette fenêtre est inspirée par la fenêtre "About Qt"
    */
	void showAboutOpenCVWindow();
	
};

#endif // Q_ABOUT_WIDGET_H