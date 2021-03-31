#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("E:/BUREAU/STUDIES/2TIC/2SEM/QT/Maquettes QT/BACK.jpg");
    ui->label_PIC6->setPixmap(pix);
    ui->label_PIC7->setPixmap(pix);
    ui->label_PIC8->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouterfacture_clicked()
{
    int ID_Facture =ui->lineEdit_Idfactureajouter->text().toInt();
    int ID_Fournisseur_Facture=ui->lineEdit_idfournisseurfactureajouter->text().toInt();
    float Total_Facture =ui->lineEdit_idfournisseurfactureajouter->text().toFloat();
    QString Nom_Produit_Facture=ui->lineEdit_nomproduitfactureajouter->text();
    QString Date_Facture= ui->dateEdit_factureajouter->text() ;
    QString Etat_Facture= ui->lineEdit_Etatfactureajouter->text();
    QString IMG_Scanee_Facture = ui->lineEdit_fcaturescaneeajouter->text();




    Factures Fa( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,Nom_Produit_Facture, Date_Facture, Etat_Facture, IMG_Scanee_Facture);

    bool test=Fa.ajouter_Facture();

    if(test)
    {
        ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Ajout effectué .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    int ID_Facture=ui->lineEdit_Idfactureajouter->text().toInt();
    bool test=Fatmp.supprimer_Facture(ID_Facture);
    if(test)
    {
        ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Suppression effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Suppression non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    int ID_Facture =ui->lineEdit_Idfactureajouter->text().toInt();
    int ID_Fournisseur_Facture=ui->lineEdit_idfournisseurfactureajouter->text().toInt();
    float Total_Facture =ui->lineEdit_idfournisseurfactureajouter->text().toFloat();
    QString Nom_Produit_Facture=ui->lineEdit_nomproduitfactureajouter->text();
    QString Date_Facture= ui->dateEdit_factureajouter->text() ;
    QString Etat_Facture= ui->lineEdit_Etatfactureajouter->text();
    QString IMG_Scanee_Facture = ui->lineEdit_fcaturescaneeajouter->text();

    Factures Fa( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,Nom_Produit_Facture, Date_Facture, Etat_Facture, IMG_Scanee_Facture);


    bool test=Fa.modifier_Facture( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,Nom_Produit_Facture, Date_Facture, Etat_Facture, IMG_Scanee_Facture);

    if(test)
    {
        ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Modification effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_ajouterfournisseur_clicked()
{
    int ID_Fournisseur =ui->lineEdit_IDFournisseur->text().toInt();
    QString Nom_Fournisseur=ui->lineEdit_NomFournisseur->text();
    QString Adresse_Fournisseur= ui->lineEdit_Adressefournisseur->text() ;
    int Telephone_Fournisseur=ui->lineEdit_telfournisseur->text().toInt();
    QString Email_Fournisseur= ui->lineEdit_emailfournisseur->text();


    Fournisseurs Fo(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);

    bool test=Fo.ajouter_Fournisseur();

    if(test)
    {
        ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Ajout effectué .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_30_clicked()
{
    int ID_Fournisseur=ui->lineEdit_IDFournisseur->text().toInt();
    bool test=Fotmp.supprimer_Fournisseur(ID_Fournisseur);
    if(test)
    {
        ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Suppression effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Suppression non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    int ID_Fournisseur =ui->lineEdit_IDFournisseur->text().toInt();
    QString Nom_Fournisseur=ui->lineEdit_NomFournisseur->text();
    QString Adresse_Fournisseur= ui->lineEdit_Adressefournisseur->text() ;
    int Telephone_Fournisseur=ui->lineEdit_telfournisseur->text().toInt();
    QString Email_Fournisseur= ui->lineEdit_emailfournisseur->text();

    Fournisseurs Fo(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);


    bool test=Fo.modifier_Fournisseur(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);

    if(test)
    {
        ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Modification effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    int ID_Produit =ui->lineEdit_idproduit->text().toInt();
    QString Nom_Produit=ui->lineEdit_nomproduit->text();
    int Quantite_Produit =ui->lineEdit_quantiteproduit->text().toInt();
    float Prix_Produit=ui->lineEdit_prixproduit->text().toFloat();



    Produits P(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit);

    bool test=P.ajouter_Produit();

    if(test)
    {
        ui->tableView->setModel(Ptmp.afficher_Produit());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Ajout effectué .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    int ID_Produit=ui->lineEdit_idproduit->text().toInt();
    bool test=Ptmp.supprimer_Produit(ID_Produit);
    if(test)
    {
        ui->tableView->setModel(Ptmp.afficher_Produit());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Suppression effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Suppression non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int ID_Produit =ui->lineEdit_idproduit->text().toInt();
    QString Nom_Produit=ui->lineEdit_nomproduit->text();
    int Quantite_Produit =ui->lineEdit_quantiteproduit->text().toInt();
    float Prix_Produit=ui->lineEdit_prixproduit->text().toFloat();


    Produits P(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit);


    bool test=P.modifier_Produit(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit );

    if(test)
    {
        ui->tableView->setModel(Ptmp.afficher_Produit());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Modification effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_lineEdit_6()
{
    ui->tableView_Fournisseur->setModel(Fotmp.afficher(ui->lineEdit_6->text()));
}



                                void mainwindow::on_recherche_produits()
                                {
                                    ui->tableView->setModel(Ptmp.afficher(ui->recherche_produits->text()));
                                }

