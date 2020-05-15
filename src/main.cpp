/**
 * @mainpage Yams
 * @version 1.0
 *
 * @section intro Introduction
 *
 *  Cette application est une adaptation du jeu de société Yams à la reconnaissance d'image. <br/>
 *  Elle est réalisée avec le framework [Qt](https://www.qt.io) pour la partie graphique et la bibliothèque [OpenCV](https://opencv.org) pour la reconaissance d'image. <br/>
 *
 *  Le jeu prend la forme d'une fenêtre présentant les scores des différents joueurs sous la forme d'un tableau sur la droite,
 *  le rendu caméra sur la gauche et les meilleurs choix en bas de la fenêtre. <br/>
 *  Si l'utilisateur ne trouve pas les choix proposés judicieux,
 *  il peut néanmoins choisir l'action qu'il souhaite faire en cliquant sur le bouton correspondant à l'action
 *  qu'il désire réaliser dans la colonne gauche du tableau des scores. Les boutons des actions déjà réalisées seront grisés. <br/>
 *
 *  Un rappel des règles du jeu se trouve dans le menuAide - Règles du jeu. <br/>
 *  Le Yams étant un jeux se jouant avec un nombre minimal de deux joueurs sans maximum, il
 *  est possible de jouer avec l’application avec autant de contraintes. <br/>
 *  La reconnaissance d’image servant à détecter les dés peut ne pas être infaillible.
 *  C’est pourquoi un bouton \a Redétecter a été disposé à droite des boutons représentant les meilleurs choix.
 *
 *
 *  Pour un fonctionnement optimal de la reconnaissance d'image, merci de :
 *
 *  - Jouer sur une surface sombre ;
 *  - Placer une caméra au dessus du jeu à 20 cm de hauteur ;
 *  - Éviter les reflet et ombres ;
 *  - Jouer dans un environnement lumineux ;
 *  - Faire en sorte de mettre hors champ toute zone de mouvement en dehors du plateau de jeu ; 
 *  - Bien positionner les dés en dessous de l'objectif de la caméra ;
 *  - Maintenir les dés à environ 1cm de distance les uns des autres.
 *
 *
 * @section screenshot Captures d'écran
 *
 * - Menu de démarrage du jeu :
 * @image html welcome.jpg width=650px
 *
 * - Pendant le jeu :
 * @image html in_game.jpg width=650px
 *
 * - Fin de jeu :
 * @image html on_win.jpg width=650px
 *
 */


// Qt
#include <QtWidgets/QApplication>

// Yams
#include "QYams.hpp"


int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	QYams yams;
	yams.show();

	return application.exec();
}
