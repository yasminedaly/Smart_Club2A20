#include "plansza.h"
#include "ui_plansza.h"
#include <listapytan.h>
#include <QString>
#include <QDebug>
#include <qtextcodec.h>
#include <glowne.h>
#include <ctime>
#include <QMessageBox>

/**
 * @brief Plansza::Plansza
 * @param parent
 * @param name
 * Nazwa gracza
 * @param liczbaP
 * wybrana liczba pytań przez gracza
 */
plansza::plansza(QWidget *parent, QString name,int liczbaP) :
    QMainWindow(parent),
    ui(new Ui::plansza)
{

        srand( time( NULL ) );
        liczbaPytanWybrana=liczbaP;
        QPixmap bkgnd("C:/Users/DeLL/Desktop/Atelier_Connexion_quiz/z/3.jpg");
        QSize size=this->size();
        licznik=0;
        bkgnd = bkgnd.scaled(500,400);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        liczbaPytanMax=6;


    ui->setupUi(this);

    this->setFixedSize(500,500);
    ui->labelTrescPytania->setWordWrap(true);
    ui->nameUser->setText(name);
    ui->nameUser->setStyleSheet("QLabel { color : orange; }");
    ui->pushButton_A->setStyleSheet("QPushButton { color : darkblue; }");
    ui->pushButton_B->setStyleSheet("QPushButton { color : brown; }");
    ui->pushButton_C->setStyleSheet("QPushButton { color : darkgreen; }");
    ui->pushButton_D->setStyleSheet("QPushButton { color : darkviolet; }");
    ui->labelTrescPytania->setStyleSheet("QLabel { color : orange; }");
    ui->lcdNumber->setStyleSheet("QLCDNumber{color : red;}");
    ui->lcdNumber->setPalette(Qt::red);


    losujPytanie();


}

plansza::~plansza()
{
    delete ui;
}

void plansza::losujPytanie(){
        qDebug()<<"RozmiarListy"<<lista.lista.size();
        losowa=rand()%lista.lista.size();
        qDebug()<<"\twylosowano:"<<losowa;
        pytanie=losowa;
        QString txt=lista.lista[losowa].trescPytania;
        ui->labelTrescPytania->setText(txt);
        ui->pushButton_A->setText(lista.lista[losowa].tab[0].trescOdp);
        ui->pushButton_B->setText(lista.lista[losowa].tab[1].trescOdp);
        ui->pushButton_C->setText(lista.lista[losowa].tab[2].trescOdp);
        ui->pushButton_D->setText(lista.lista[losowa].tab[3].trescOdp);
        licznik++;
        qDebug()<<"licznik="<<licznik;


}

void plansza::on_pushButton_A_clicked()
{
    odp(1);
}

void plansza::on_pushButton_B_clicked()
{
    odp(2);
}

void plansza::on_pushButton_C_clicked()
{
    odp(3);
}

void plansza::on_pushButton_D_clicked()
{
    odp(4);
}

void plansza::odp(int id){
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("C:/Users/DeLL/Desktop/Atelier_Connexion_quiz/z/ico.png"));
    msgBox.setWindowTitle("Game");

    if(lista.lista[pytanie].prawidlowaOdpowiedz==id){

        msgBox.setText("réponse correcte");
        msgBox.exec();
        ui->lcdNumber->display((ui->lcdNumber->intValue())+1);
    }else{
        msgBox.setText("mauvaise réponse");
        msgBox.exec();
    }
    if(licznik<liczbaPytanWybrana){
        lista.lista.removeAt(losowa);
        losujPytanie();
    }else{

        int w=ui->lcdNumber->intValue();
        QString wynik=QString::number(w);
        msgBox.setText("\n\tfin du jeu!\n\nBonnes réponses: "
                       +wynik+" z "+QString::number(liczbaPytanWybrana)+"\t \n");
        msgBox.exec();
        this->close();
    }
}
