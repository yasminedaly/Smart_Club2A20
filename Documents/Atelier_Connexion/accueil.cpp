#include "accueil.h"
#include "ui_accueil.h"
#include "mainwindow.h"

accueil::accueil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::accueil)
{
    ui->setupUi(this);

    QMediaPlayer *music=new QMediaPlayer();
    QSound::play(":/new/prefix1/sond/632.wav");

    QPropertyAnimation *animation = new QPropertyAnimation(ui->animation, "geometry");
            animation->setDuration(10000);
            animation->setLoopCount(-1);
            animation->setStartValue(QRect(0, 405, 191,59));
            animation->setEndValue(QRect(690, 405, 191, 59));
            animation->start();

}

accueil::~accueil()
{
    delete ui;
}

void accueil::on_pushButton_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
accueil::close();
MainWindow * m = new MainWindow();
    m->show();
}
