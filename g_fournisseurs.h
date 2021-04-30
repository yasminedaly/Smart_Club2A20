#ifndef G_FOURNISSEURS_H
#define G_FOURNISSEURS_H

#include <QMainWindow>
#include "fournisseurs.h"
#include "factures.h"
#include "produits.h"
#include "fournisseur_fidele.h"
#include "arduino.h"
#include "exportexcelobject.h"
#include "notepad.h"
#include "button_g_fournisseurs.h"
#include "calculator_g_fournisseurs.h"
#include "puzzle_main_window_g_fournisseurs.h"
#include "puzzle_g_fournisseurs.h"
#include "pieces_g_fournisseurs.h"
#include "paint_g_fournisseurs.h"
#include "calendar_g_fournisseur.h"





#include <QtMultimedia/QMediaPlayer>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QPropertyAnimation>
#include <QtMultimedia/QSound>
#include <QAbstractSocket>
#include <QTimer>



QT_BEGIN_NAMESPACE
namespace Ui { class G_Fournisseurs; }
QT_END_NAMESPACE

class QMediaPlayer ;

class QSystemTrayIcon ;

class G_Fournisseurs : public QMainWindow
{
    Q_OBJECT

public:
    G_Fournisseurs(QWidget *parent = nullptr);
    ~G_Fournisseurs();

public slots:
    void myfunction();

private slots:
    void on_ajouter_fournisseur__clicked();

    void on_supprimer_fournisseur__clicked();

    void on_modifier_fournisseur__clicked();

    void on_pushButton_ajouterfacture_clicked();

    void on_tableView_Fournisseur_activated(const QModelIndex &index);

    void on_supprimer_facture_clicked();

    void on_tableView_Facture_activated(const QModelIndex &index);

    void on_modifier_facture_clicked();

    void on_supprimer_facture_2_clicked();

    void on_imprimer_clicked();

    void on_recherche_produit_clicked();

    void on_statistiques_factures_clicked();

    void on_chercher_produitss_clicked();

    void on_chercherboutonfacture_clicked();

    void on_chercher_fournisseur__clicked();

    void display_id_fournisseur() ;

    void display_nom_fournisseur() ;

    void display_adresse_fournisseur() ;

    void display_mail_fournisseur() ;

    void display_telephone_fournisseur() ;

    void on_recherche_produits_textChanged();

    void on_verifier_etat_clicked();

    void on_calendar_button_fournisseur_clicked();

    void on_calcul_fournisseurs_clicked();

    void on_puzzle_G_fournisseurs_clicked();

    void on_paint_g_fournisseurs_clicked();

    void on_modifier_facture_fournisseurs_clicked();

    void on_ajouter_produit_fournisseur_clicked();

    void on_notepad_g_fournisseur_clicked();

    void on_excel_g_fournisseurs_clicked();

    void on_tableView_Produit_G_fournisseurs_activated(const QModelIndex &index);

    void on_recherche_tab_facture_textChanged();

    void on_recherche_tab_fournisseurs_textChanged();

    void on_comboBox_factures_fournisseurs_activated(const QString &arg1);

    void on_comboBox_g_fournisseurs_activated(const QString &arg1);

    void on_pdf_g_fournisseur_clicked();

private:
    Ui::G_Fournisseurs *ui;

    calculator_G_Fournisseurs *calculator_G_Fourniss ;

    QMediaPlayer *click;
    QMediaPlayer *success;
    QMediaPlayer *fail;

    Fournisseurs Fotmp;
    Factures Fatmp ;
    Produits Ptmp ;
    Fournisseur_Fidele FF ;

    QPropertyAnimation *animation ;
    QPropertyAnimation *animation2 ;
    QPropertyAnimation *animation3 ;
    QPropertyAnimation *animation4 ;

    QSystemTrayIcon *notif ;

    Notepad *notepad ;

    QByteArray data;

    Arduino A;

    QTimer *timer ;

    Calendar_G_fournisseur *Calendar_G_fournisseurs ;

    Puzzle_Main_Window_G_fournisseurs *Puzzle_G_fournisseurs ;

    Paint_G_fournisseurs *paint_fournisseurs ;



};
#endif // G_FOURNISSEURS_H
