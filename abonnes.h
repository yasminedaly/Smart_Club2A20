#ifndef ABONNES_H
#define ABONNES_H
#include <QString>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "sub.h"
#include "seances.h"
#include <QFileDialog>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QDebug>
#include <QMediaPlaylist>
#include "playlist.h"
#include <QtMultimedia/QMediaPlayer>
#include "QTimer"
#include "QPalette"
#include "vector"
#include "QKeyEvent"
#include "QLineEdit"
#include "todolist.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Abonnes; }
QT_END_NAMESPACE

class Abonnes : public QMainWindow
{

    Q_OBJECT

public:
    Abonnes(QWidget *parent = nullptr);
    
    ~Abonnes();

private slots:


    void on_pb_Abonne_clicked();

    void on_supprimer_Abonnes_clicked();

    void on_pb_Seance_clicked();


    void on_modifier_Abonnes_clicked();

    void on_modifier_seances_clicked();

    void on_supprimer_seances_clicked();

    void on_tri_nom_clicked();

    void on_tri_prenom_clicked();

    void on_tri_ddn_clicked();

    void on_pb_xl_clicked();

    void on_tri_date_clicked();

    void on_tri_capacite_clicked();

    void on_show_abonnes_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_show_seances_activated(const QModelIndex &index);

    void on_recherch__clicked();

    void on_add_clicked();

    void on_remove_clicked();

    void on_save_clicked();

    void on_play_clicked();

    void on_volumeBar_valueChanged(int value);

    void on_seekBar_sliderMoved(int position);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_forward_clicked();

    void on_back_clicked();

    void on_mute_clicked();

    void on_repeat_clicked();

    void on_shuffle_clicked();

    void update();

    void on_searchBar_textChanged(const QString &arg1);

    void on_recherch_ab_clicked();

    void on_stat_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Abonnes *ui;
    sub S;
    sub tmpsub;
    int Cin=211;
    seances A;
    seances tmpseances;
    QPropertyAnimation *animation;
    CToDoList *app;


    void updateList();

    void loadTrack();

    void next();

    void back();

    void shufflePlaylist();

    int getIndex();

    bool repeat = false;

    bool muted = false;

    bool shuffle = false;

    int lCounter = 0;

    Playlist playlist;

    QTimer *updater = new QTimer(this);

    QMediaPlayer *player = new QMediaPlayer();

    vector<unsigned short int> shuffledPlaylist;

protected:
    void keyPressEvent(QKeyEvent *event);



};
#endif // ABONNES_H
