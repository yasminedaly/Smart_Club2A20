#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "piece.h"
#include <QLabel>

#include <iostream>

#include <ostream>
#include <fstream>

//_______________________________MAINMENU_________________________________
/**
 * @brief MainMenu::MainMenu, constructor of the main menu
 * @param parent
 */
MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    //QSound::play(":/musique/Musique/Game_of_Thrones.wav");
    ui->setupUi(this);
    this->setFixedSize(this->size());   //Empêche le redimensionnement de la fenêtre en fixant la taille actuelle de la fenêtre
}

/**
 * @brief MainMenu::~MainMenu, desctrutor of the main menu
 */
MainMenu::~MainMenu()
{
    delete ui;
}

//_______________________________METHOD_________________________________

/**
 * @brief MainMenu::on_newGameButton_clicked, launch a new game when the button "New game" is pressed
 */
void MainMenu::on_newGameButton_clicked()
{
    ChessBoard board("initialisation.txt");
    this->hide();
    board.exec();
}

/**
 * @brief MainMenu::on_loadGameButton_clicked, launch the last game save when the button "Continue" is pressed
 */
void MainMenu::on_loadGameButton_clicked()
{
    ChessBoard board("sauvegarde.txt");
    this->hide();
    board.exec();
}

/**
 * @brief MainMenu::on_btnQuitter_clicked, exit the game when the exit button is pressed
 */
void MainMenu::on_btnQuitter_clicked()
{
    this->close();
}

/**
 * @brief MainMenu::on_btnRegle_clicked, show the rules menu when the button "Rules" is pressed
 */
void MainMenu::on_btnRegle_clicked()
{
    pageRegle page;
    this->close();
    page.exec();
}
