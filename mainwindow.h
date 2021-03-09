#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "joueur.h"
#include "partie.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_joueur_clicked();

    void on_supprimer_joueur_clicked();

    void on_tab_afficher_joueur_activated(const QModelIndex &index);

    void on_modifier_joueur_clicked();

    void on_ajouter_partie_clicked();

    void on_tab_afficher_partie_activated(const QModelIndex &index);

    void on_supprimer_partie_clicked();

    void on_modifier_partie_clicked();

private:
    Ui::MainWindow *ui;
    Joueur J;
    Partie P;
};
#endif // MAINWINDOW_H
