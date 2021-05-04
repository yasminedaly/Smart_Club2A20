#ifndef GESTIONRH_H
#define GESTIONRH_H

#include <QMainWindow>
#include <QWidget>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QDebug>
#include <QSqlTableModel>
#include "employe.h"
#include <QAbstractItemView>
#include <QRegExp>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QPropertyAnimation>
#include "audioplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GestionRH; }
QT_END_NAMESPACE

class GestionRH : public QMainWindow
{
    Q_OBJECT

public:
    GestionRH(QWidget *parent = nullptr);
    ~GestionRH();

private slots:
    void on_pushButtonAjouterEmploye_clicked();

    void on_pushButtonVider_clicked();

    void on_pushButtonMenu_clicked();

    void on_pushButtonModifier_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButtonRechercher_clicked();

    void on_pushButtonStats_clicked();

    void on_pushButtonExportPDF_clicked();

    void on_pushButtonPDF_2_clicked();

    void on_pushButtonPDF_clicked();

    void on_pushButtonTrier_clicked();

    void on_ajouter_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonSuppr_clicked();

    void on_pushButtonStatistiques_clicked();

    void on_pushButtonRechercherConge_clicked();

    void on_lineEditMail_cursorPositionChanged(int arg1, int arg2);

    void on_clock_clicked();

    void on_clock_2_clicked();

private:
    Ui::GestionRH *ui;
    employe tmpemploye;
    AudioPlayer* audio;
     //  conge tmpconge;
       QRegExp mail_regex;
       QRegExp nom_regex,tel_regex,salaire_regex, id_regex;
};
#endif // GESTIONRH_H
