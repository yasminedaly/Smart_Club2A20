#ifndef ACCUEIL_H
#define ACCUEIL_H
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QtMultimedia/QSound>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class accueil;
}

class accueil : public QMainWindow
{
    Q_OBJECT

public:
    explicit accueil(QWidget *parent = nullptr);
    ~accueil();
    bool research();


private slots:
    void on_pushButton_clicked();

    void on_clock_clicked();

    void on_Calculator_clicked();

    void on_radio_clicked();

private:
    Ui::accueil *ui;
    // QSequentialAnimationGroup* animationGroup;

};

#endif // ACCUEIL_H
