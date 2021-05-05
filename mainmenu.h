#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "chessboardyosra.h"
#include <QSound>
#include <QMediaPlayer>
#include "pageregle.h"

namespace Ui {
class MainMenu;


}

class MainMenu : public QDialog
{
    Q_OBJECT



public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_newGameButton_clicked();
    void on_loadGameButton_clicked();


    void on_btnQuitter_clicked();

    void on_btnRegle_clicked();

private:

    Ui::MainMenu *ui;



};

#endif // MAINMENU_H
