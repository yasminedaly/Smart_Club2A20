#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "commande.h"
#include "bibliotheques.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPushButton>
#include <QPrinter>
#include <QPdfWriter>
#include <QApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QTextBrowser>
#include <QFileDialog>
#include <QtTextToSpeech>
#include <QTextBlock>
#include <QTextEdit>
#include <cstdlib>
#include <QRadioButton>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui ( new Ui::MainWindow)
{
    ui->setupUi(this);
  QPixmap pix ("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/gestion commande/connexion bd/back.jpg");
   QPixmap pix2 ("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/gestion commande/connexion bd/back.jpg");


  //  ui->back->setPixmap(pix);
   // ui->pb_ajouter->setBackgroundRole(pix2);
    ui->tableView_2->setModel(Etmp.afficher());
    ui->tableView_bib->setModel(Etmpb.afficher_livre());


}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{

    int id_commande=ui->le_id->text().toInt();

    int nb_produit=ui->le_nb->text().toInt();

    float Prix_t=ui->le_prix->text().toFloat();



     QString Date_commande=ui->dateEdit->date().toString("dd / MM / yyyy ");
    // QString dateabs= ui->date->date().toString("dd / MM / yyyy ");

   //  QString nom_c=ui->nom_liv->text() ;
     QString produit_c = "ajouter" ;
     QString nom_c = "ajouter" ;


    commandeh cc(id_commande , nom_c, produit_c  );

    commande c(id_commande,nb_produit,Prix_t,Date_commande) ;

    bool test=c.ajouter();
    bool test1=cc.ajoutehis() ;

    if (test)

    {
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }






void MainWindow::on_pushButton_sup_clicked()

{
    int id_commande=ui->le_id->text().toInt();
    bool test=Etmp.supprimer(id_commande);

    if (test)

    {
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pushButton_mod_clicked()
{
    int id_commande=ui->le_id->text().toInt();

    int nb_produit=ui->le_nb->text().toInt();

    float Prix_t=ui->le_prix->text().toFloat();

     QString Date_commande=ui->dateEdit->text();

       commande c(id_commande,nb_produit,Prix_t,Date_commande) ;

       bool test=c.modifier(id_commande, nb_produit, Prix_t,Date_commande) ;

       if (test)

       {
           ui->tableView_2->setModel(Etmp.afficher());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modification effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("modification non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pushButton_rch_clicked()
{

    int id_commandeAA=ui->rch_2->text().toInt();

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qeury=new QSqlQuery();
        qeury->prepare("SELECT * from commande where id_commande=:id_commandeAA");
        qeury->bindValue(":id_commandeAA",id_commandeAA);



        qeury->exec();
        if(qeury->next())
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/compteexiste.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
                model->setQuery(*qeury);
                ui->tableView_2->setModel(model) ;
                ui->tableView_2->setModel(Etmp.afficher());//refresh


        }
        else
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/comptenot.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
        }

}

void MainWindow::on_Liv_ajouter_clicked()

    {





    int id_l=ui->id_Liv->text().toInt();
    QString nom_l=ui->nom_liv->text() ;
    QString Ref_livre=ui->ref_liv->text() ;
    QString desc_l=ui->desc_liv->toPlainText() ;
    QString date_s=ui->dateS_liv->date().toString("dd / MM / yyyy ") ;
    QString date_r=ui->dateR_liv->date().toString("dd / MM / yyyy ") ;
    QString displ=ui->oui_liv->text()  ;
   // QString displ1=ui->non_liv_2->text()  ;



    if (ui->oui_liv->isChecked())

    {
    QString displ=ui->oui_liv->text() ;

       }

     QString displ1=ui->non_liv_2->text() ;

      if (ui->non_liv_2->isChecked())
      {
         QString displ1=ui->non_liv_2->text() ;
       }
Bibliotheques B(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;
bool nom_ll , Ref_livree  ;

nom_ll= B.controlSaisieCharVide(nom_l,"nom_ll");
Ref_livree=B.controlsaisieRef(Ref_livre);

if((nom_ll==true)&&(Ref_livree==true))
       {
  //  Bibliotheques B(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

    bool test=B.ajouter_livre();



    if (test)

    {
        ui->tableView_bib->setModel(Etmpb.afficher_livre());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}}

void MainWindow::on_liv_supprimer_clicked()
{

    int id_l=ui->id_Liv->text().toInt();
    bool test=Etmpb.supprimer_livre(id_l);

    if (test)

    {
        ui->tableView_bib->setModel(Etmpb.afficher_livre());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_Liv_modifier_clicked()
{


    int id_l=ui->id_Liv->text().toInt();
    QString nom_l=ui->nom_liv->text() ;
    QString Ref_livre=ui->ref_liv->text() ;
    QString desc_l=ui->desc_liv->toPlainText() ;
    QString date_s=ui->dateS_liv->date().toString("dd / MM / yyyy ") ;
    QString date_r=ui->dateR_liv->date().toString("dd / MM / yyyy ") ;
    QString displ=ui->oui_liv->text()  ;
    QString displ1=ui->non_liv_2->text() ;


    Bibliotheques B(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

       bool test=B.modifier_livre(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

       if (test)

       {
           ui->tableView_bib->setModel(Etmpb.afficher_livre());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modification effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("modification non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);



}





void MainWindow::on_pushButton_rch_livre_clicked()
{


    int id_lAA=ui->rch_livre->text().toInt();

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qeury=new QSqlQuery();
        qeury->prepare("SELECT * from BIBLIOTHEQUE where id_l=:id_lAA");
        qeury->bindValue(":id_lAA",id_lAA);



        qeury->exec();
        if(qeury->next())
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/compteexiste.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
                model->setQuery(*qeury);
                ui->tableView_bib->setModel(model) ;
                ui->tableView_bib->setModel(Etmpb.afficher_livre());

        }
        else
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/comptenot.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
        }
}

void MainWindow::on_tri_commande_clicked()

    {
    ui->tableView_2->setModel(Etmp.tri());
      ui->tableView_2->setModel(Etmp.tri());//refresh

    }

void MainWindow::on_pushButton_tri_livre_clicked()

    {
    ui->tableView_bib->setModel(Etmpb.tri_livre());
      ui->tableView_bib->setModel(Etmpb.tri_livre());

    }

void MainWindow::on_Historique_clicked()
{
    ui->tableView_2->setModel(Etmph.afficherhis()) ;
    ui->tableView_2->setModel(Etmph.afficherhis());//refresh
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
            str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES BIBLIOTHEQUE </font><br /> <br /> "));
            str.append("<table border=1><tr>");
            str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">ID-LIVRE</font>&nbsp;&nbsp;"+"</td>");
            str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">NOM-LIVRE </font>&nbsp;&nbsp;")+"</td>");
            str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">REF-LIVRE</font>&nbsp;&nbsp;")+"</td>");
            str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">DESC-LIVRE</font>&nbsp;&nbsp;"+"</td>");
            str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">DATE-SORTIE</font>&nbsp;&nbsp;"+"</td>");
            str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">DATE-RECUPERATION</font>&nbsp;&nbsp;"+"</td>");


            QSqlQuery * query=new QSqlQuery();
            query->exec("SELECT ID_L ,NOM_L , REF_LIVRE , DESC_L , DATE_S, DATE_R ,DISPL from BIBLIOTHEQUE ");
            while(query->next())
            {
                str.append("<tr><td>");
                str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
                str.append("</td><td>");
                str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
                str.append("</td><td>");
                str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(2).toString()+"&nbsp;&nbsp;");
                 str.append("</td><td>");
                str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(3).toString()+"&nbsp;&nbsp;");
                str.append("</td><td>");
                str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(4).toString()+"&nbsp;&nbsp;");
                str.append("</td><td>");
                str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(5).toString()+"&nbsp;&nbsp;");
                str.append("</td></tr>");

        }

            str.append("</table></center><body></html>");

            QPrinter printer;
            printer.setOrientation(QPrinter::Portrait);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);

            QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des BIBLIOTHEQUE","PDF(*.pdf");
             if(path.isEmpty()) return;
             printer.setOutputFileName(path);
             QTextDocument doc;
             doc.setHtml(str);
             doc.print(&printer);

}

void MainWindow::on_pushButton_3_clicked()
{

    lng="ang";
        // page biblo
        ui->l1->setText("ID BOOK");
       // ui->l1->setStyleSheet("QLabel{color: rgb(255, 255, 255); font: 75 24pt MS Shell Dlg 2;text-decoration:underline;font-weight:600; color:#ffffff;}");
        ui->l2->setText("NAME BOOK");
        ui->l3->setText("BOOK REFERENCE");
        ui->l4->setText("BOOK DESCRIPTION");
        ui->l5->setText("RELEASE DATE");
        ui->l6->setText("RECOVERY DATE");
        ui->l7->setText("AVAILABILITY");
        ui->Liv_ajouter->setText("ADD");
        ui->Liv_modifier->setText("EDIT");
        ui->liv_supprimer->setText("REMOVE");
        ui->pushButton_rch_livre->setText("RESEARCH");
        ui->pushButton_tri_livre->setText("SORTING");
        ui->oui_liv->setText("YES");
        ui->non_liv_2->setText("NO");




        //----------------------------------//


}

void MainWindow::on_pushButton_2_clicked()

{
  lng="fr";

  ui->l1->setText("ID LIVRE");
 // ui->l1->setStyleSheet("QLabel{color: rgb(255, 255, 255); font: 75 24pt MS Shell Dlg 2;text-decoration:underline;font-weight:600; color:#ffffff;}");
  ui->l2->setText("NOM LIVRE");
  ui->l3->setText("REFERENCE LIVRE");
  ui->l4->setText("DESCRIPTION LIVRE");
  ui->l5->setText("DATE DE SORTIE");
  ui->l6->setText("DATE DE RECUPERATION");
  ui->l7->setText("DISPONIBILITE");
  ui->Liv_ajouter->setText("ajouter");
  ui->Liv_modifier->setText("modifier");
  ui->Liv_modifier->setStyleSheet("QPushButton {border:none;background-color:#000000;background-position: left center;background-repeat: no-repeat;border-radius: 5px;border:1px solid transparent;color:rgb(255, 255, 255);text-align: center; border-left:4px solid #000000;}QPushButton:hover {background-color:rgb(0, 0, 128);}QPushButton:pressed { border:2px solid rgb(0, 0, 128); }");
  ui->liv_supprimer->setText("supprimer");
  ui->liv_supprimer->setStyleSheet("QPushButton {border:none;background-color:#000000;background-position: left center;background-repeat: no-repeat;border-radius: 5px;border:1px solid transparent;color:rgb(255, 255, 255);text-align: center; border-left:4px solid #000000;}QPushButton:hover {background-color:rgb(0, 0, 128);}QPushButton:pressed { border:2px solid rgb(0, 0, 128); }");
  ui->pushButton_rch_livre->setText("recherche");
  ui->pushButton_tri_livre->setText("tri");
  ui->oui_liv->setText("oui");

  ui->non_liv_2->setText("non");
   ui->Liv_ajouter->setStyleSheet("QPushButton {border:none;background-color:#000000;background-position: left center;background-repeat: no-repeat;border-radius: 5px;border:1px solid transparent;color:rgb(255, 255, 255);text-align: center; border-left:4px solid #000000;}QPushButton:hover {background-color:rgb(0, 0, 128);}QPushButton:pressed { border:2px solid rgb(0, 0, 128); }");

}

void MainWindow::on_pushButton_5_clicked()
{

        QString k=ui->comboBox_2->currentText();

            ui->tableView_bib->setModel(Etmpb.tri2(k));
            ui->tableView_bib->setModel(model) ;
            ui->tableView_bib->setModel(Etmpb.afficher_livre());

}

void MainWindow::on_recherche_clicked()
{


    QString k = ui->che2->text();
    QString l = ui->che3->text();


    if (l != ""){
   ui->tableView_bib->setModel(Etmpb.chercher_matpar_nom(k)) ;}
    if (k!= ""){
   ui->tableView_bib->setModel(Etmpb.chercher_matpar_ref(l) );}


}
