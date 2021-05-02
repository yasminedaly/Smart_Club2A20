#ifndef PLANSZA_H
#define PLANSZA_H

#include <QMainWindow>
#include <listapytan.h>
namespace Ui {
class plansza;
}

class plansza : public QMainWindow
{
    Q_OBJECT

public:
    explicit plansza(QWidget *parent = nullptr, QString name="", int liczbaP=5);
    ~plansza();
    ///nazwa Gracza
        QString nameUser;
        ///Liczba pytan w pliku
        int liczbaPytanMax;

        ///numer pytania
        int pytanie;
        ///Lista pytan
        ListaPytan lista;
        ///Liczb pytan jaka wybraÅ‚ uÅ¼ytkownik
        int liczbaPytanWybrana;
        ///zmienna zliczajÄ…ca liczbÄ™ pytaÅ„ na ktÃ³re odpowiedziaÅ‚ gracz
        int licznik;
        ///losowana liczba
        int losowa;
private slots:
    void on_pushButton_A_clicked();

    void on_pushButton_B_clicked();

    void on_pushButton_C_clicked();

    void on_pushButton_D_clicked();



private:
    Ui::plansza *ui;
    void losujPytanie();
        void odp(int id);


};

#endif // PLANSZA_H
