#include "glowne.h"
#include "ui_glowne.h"
#include "plansza.h"


glowne::glowne(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::glowne)
{
    ui->setupUi(this);
    this->setFixedSize(450,200);
       QPixmap bkgnd("C:/Users/DeLL/Desktop/Atelier_Connexion_quiz/z/echec.jpg");
        //QPixmap bkgnd(":/new/prefix1/tlo1.png");
            bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Background, bkgnd);
            this->setPalette(palette);
            ui->liczbaPytan->setMaximum(lista.lista.size());
            ui->label_2->setStyleSheet("QLabel {color : black; }");

}

glowne::~glowne()
{
    delete ui;
}

void glowne::on_lineEdit_editingFinished()
{
    //ui->pushButtonNowaGra->setDisabled(false);
}
/**
 *Glowne::on_lineEdit_textChanged
 * Funkcja włączająca aktywność przyciku po zmianie tekstu
 * @param arg1
 */
void glowne::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButtonNowaGra->setDisabled(false);
}
/**
 * \brief Glowne::on_pushButtonNowaGra_clicked
 * Funkcja uruchamia nową grę
   Po jej wywołaniu uruchamiane jest nowe okno z plansza
 */
void glowne::on_pushButtonNowaGra_clicked()
{
    QString name=ui->lineEdit->text();
    int l=ui->liczbaPytan->text().toInt();
    plansza *board=new plansza(this,name,l);
    //board->set(name, l);
    board->show();


}

void glowne::on_lineEdit_returnPressed()
{

}
