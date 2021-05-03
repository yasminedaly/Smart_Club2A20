#ifndef GESTIONJEU_H
#define GESTIONJEU_H
#include "joueur.h"
#include "partie.h"
#include "game.h"
//#include "arduino.h"
#include "controls.h"
#include "openroll-config.h"
#include "scoreboard.h"
#include "qcustomplot.h"
#include "notepad.h"
#include "camera.h"
#include "qrplusplus.h"
#include <QPropertyAnimation>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Gestionjeu; }
QT_END_NAMESPACE


//Game *game;


class Gestionjeu : public QMainWindow
{
    Q_OBJECT

public:
    Gestionjeu(QWidget *parent = nullptr);
    ~Gestionjeu();

private slots:
    void on_ajouter_joueur_clicked();

    void on_supprimer_joueur_clicked();

    void on_tab_afficher_joueur_activated(const QModelIndex &index);

    void on_modifier_joueur_clicked();

    void on_ajouter_partie_clicked();

    void on_tab_afficher_partie_activated(const QModelIndex &index);

    void on_supprimer_partie_clicked();

    void on_modifier_partie_clicked();

    void on_chercher_joueur_clicked();

    void on_chercher_partie_clicked();

    void on_trier_joueur_clicked();

    void on_trier_partie_clicked();

    void on_imprimer_partie_clicked();

    void on_excel_joueur_clicked();

    void showTime();

    void on_envoyer_mail_released();

    void on_afficher_tout_joueurs_clicked();

    void on_afficher_tout_parties_clicked();

    void on_stat_joueur_clicked();

    void on_notes_clicked();



    void on_ajouter_photo_j_clicked();

    void on_prendre_photo_clicked();

    void on_qrcode_clicked();

    void on_lancer_partie_clicked();

    void update_label();
    void on_autoriser_acces_clicked();

    void on_refuser_acces_clicked();

    void on_score_clicked();

private:
    Ui::Gestionjeu *ui;
    Joueur J;
    Partie P;
    Controls controls;
    Notepad *notepad;
    Camera *camera;
    QRplusplus *qrcode;
    QPropertyAnimation * animation;
    QCustomPlot *customPlot;


    QByteArray data; // variable contenant les donnÃ©es reÃ§ues

    //Arduino A; // objet temporaire


    QString fileNameImage ;
    QPixmap photo ;
    QByteArray image;
    QPixmap pixmap;
    QByteArray array;

};
#endif // GESTIONJEU_H
