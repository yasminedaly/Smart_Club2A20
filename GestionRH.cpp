#include "GestionRH.h"
#include "ui_GestionRH.h"
#include <QFileDialog>
#include <QPrinter>
#include "conge.h"
#include "employe.h"
#include "digitalclock.h"
GestionRH::GestionRH(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionRH)
{
    ui->setupUi(this);
   // QMediaPlayer *music=new QMediaPlayer();
  //  QSound::play(":/new/prefix1/sond/632.wav");
    mail_regex=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    nom_regex=QRegExp("[a-zA-Z ]+$");
    salaire_regex=QRegExp("([0-9]+)*[.]*[0-9]+$");
    tel_regex=QRegExp("[0-9]{8}$");
    id_regex=QRegExp("^[0-9]*$");
    ui->dateEditAdhesion->setMaximumDate(QDate::currentDate());
    ui->lineEditNum->setMaxLength(8);
    ui->dateEditDebut->setMinimumDate(QDate::currentDate());
    QDate date=ui->dateEditDebut->date();
    ui->dateEditFin->setMinimumDate(date);

    ui->tableViewEmploye->setModel(tmpemploye.afficher());
    ui->tableViewEmploye->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewEmploye->setSelectionMode(QAbstractItemView::SingleSelection);

   // QSqlQueryModel * modell = tmpconge.afficher();
    //ui->tableViewConge->setModel( modell);
    QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
    mm->setDynamicSortFilter(true);
    //mm->setSourceModel(modell);

    //ui->tableViewConge->setModel(modell);
    ui->tableViewConge->setSortingEnabled(true);

    ui->tableViewConge->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewConge->setSelectionMode(QAbstractItemView::SingleSelection);

    QSqlQueryModel *modellll = new QSqlQueryModel;
    modellll->setQuery("SELECT ID FROM EMPLOYE");
  //  ui->comboBoxNom->setModel(modellll);

}

GestionRH::~GestionRH()
{
    delete ui;
}




void GestionRH::on_pushButtonAjouterEmploye_clicked()
{
            bool mail_verif = mail_regex.exactMatch(ui->lineEditMail->text());
            bool nom_verif = nom_regex.exactMatch(ui->lineEditNom->text());
            bool tel_verif = tel_regex.exactMatch(ui->lineEditNum->text());
            bool id_verif= id_regex.exactMatch(ui->lineEditID->text());
            bool depart_verif=nom_regex.exactMatch(ui->lineEditDepart->text());
            bool tel_verif2=true;
            bool salaire_verif=salaire_regex.exactMatch(ui->lineEditSalaire->text());

            if (ui->lineEditNum->text().at(0)!='2' && ui->lineEditNum->text().at(0)!='5' && ui->lineEditNum->text().at(0)!='9' && ui->lineEditNum->text().at(0)!='7')
                   tel_verif2=false;

            if (ui->lineEditID->text()!="" &&
                ui->lineEditNom->text()!="" &&
                ui->lineEditNum->text()!="" &&
                ui->lineEditDepart->text()!="" &&
                ui->lineEditSalaire->text()!=""
                ){
                if(id_verif && nom_verif && tel_verif && tel_verif2 && mail_verif && depart_verif && salaire_verif)
                {
                    QString id=ui->lineEditID->text();
                    QString nom=ui->lineEditNom->text();
                    QString num=ui->lineEditNum->text();
                    QString mail=ui->lineEditMail->text();
                    QString dateAd=ui->dateEditAdhesion->date().toString();
                    QString sexe=ui->comboBoxSexe->currentText();
                    QString depart=ui->lineEditDepart->text();
                    QString salaire=ui->lineEditSalaire->text();
                    employe empl(id,nom,num,mail,dateAd,sexe,depart,salaire);

                    bool test=empl.ajouter();
                    if (test)
                        ui->tableViewEmploye->setModel(tmpemploye.afficher());
                    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                        widget->clear();
                    }
                    ui->lineEditID->setStyleSheet("color: black");
                    ui->lineEditNom->setStyleSheet("color: black");
                    ui->lineEditNum->setStyleSheet("color: black");
                    ui->lineEditMail->setStyleSheet("color: black");
                //    ui->lineEditDepart->setStyleSheet("color: black");
                    ui->lineEditSalaire->setStyleSheet("color: black");
                }
                else{
                    if (!mail_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","E-mail invalid");
                        ui->lineEditMail->setStyleSheet("color: red");

                    }
                    if (!id_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","ID invalid");
                        ui->lineEditID->setStyleSheet("color: red");

                    }
                    if(!nom_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","Nom invalid");
                        ui->lineEditNom->setStyleSheet("color: red");

                    }
                    if(!tel_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","Numero De Tel invalid");
                        ui->lineEditNum->setStyleSheet("color: red");

                    }
                    if(!depart_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","Departement invalid");
                  //      ui->lineEditDepart->setStyleSheet("color: red");
                    }
                    if(!salaire_verif){
                        QMessageBox::warning(this,"Erreur lors de l'ajout","Salaire invalid");
                        ui->lineEditSalaire->setStyleSheet("color: red");

                    }
                }
    }
            else {
                QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez compléter tous les champs");
            }
            QSqlQueryModel *modellll = new QSqlQueryModel;
            modellll->setQuery("SELECT ID FROM EMPLOYE");
            //ui->comboBoxNom->setModel(modellll);
}


/*void GestionRH::on_pushButtonAfficherTout_clicked()
{
    ui->tableViewEmploye->setModel(tmpemploye.afficher());
}*/

void GestionRH::on_pushButtonModifier_clicked()
{
    if (ui->pushButtonModifier->isChecked())
                {
                    ui->pushButtonModifier->setDisabled(true);
                    ui->pushButtonModifier->setText("Modifiable");
                    QSqlTableModel *tableModel= new QSqlTableModel();
                    tableModel->setTable("EMPLOYE");
                    tableModel->select();
                    ui->tableViewEmploye->setModel(tableModel);
                }
                else
                {
                    ui->pushButtonModifier->setText("Modifier");QSqlQueryModel * model = tmpemploye.afficher();
                    ui->tableViewEmploye->setModel( model);
                    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
                    m->setDynamicSortFilter(true);
                    m->setSourceModel(model);
                    ui->tableViewEmploye->setModel(m);
                    ui->tableViewEmploye->setSortingEnabled(true);
                }
    ui->pushButtonModifier->setChecked(false);
}

void GestionRH::on_pushButtonSupprimer_clicked()
{
    QItemSelectionModel *select = ui->tableViewEmploye->selectionModel();
    QString idemploye =select->selectedRows(0).value(0).data().toString();
    if(tmpemploye.supprimer(idemploye))
            {
                ui->pushButtonModifier->setText("Modifier");QSqlQueryModel * model = tmpemploye.afficher();
                ui->tableViewEmploye->setModel( model);
                QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
                m->setDynamicSortFilter(true);
                m->setSourceModel(model);
                ui->tableViewEmploye->setModel(m);
                ui->tableViewEmploye->setSortingEnabled(true);

                QSqlQueryModel *modellll = new QSqlQueryModel;
                modellll->setQuery("SELECT ID FROM EMPLOYE");
              //  ui->comboBoxNom->setModel(modellll);
            }

}


void GestionRH::on_pushButtonRechercher_clicked()
{
    QString nom=ui->lineEditChercher->text();
    QDate date=ui->date_recherche->date();
    QString sexe;
    QString email=ui->lineEditChercher->text();
    if (ui->radioButtonHomme->isChecked())
       sexe=ui->radioButtonHomme->text();
    else if (ui->radioButtonFemme->isChecked())
       sexe=ui->radioButtonFemme->text();
    if (ui->checkBoxDate->isChecked())
        {

            QSqlQueryModel *verif_combinaison=tmpemploye.rechercher_combinaison_all(nom,sexe,date);
            if (verif_combinaison!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_combinaison);
            }

        }
    else if (!ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_sexe=tmpemploye.rechercher_sexe(sexe);
            if (verif_sexe!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_sexe);
            }
        }
        else if (ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_date=tmpemploye.rechercher_date(date);
            if (verif_date!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_date);
            }
        }
        else if (!ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_nom=tmpemploye.rechercher_nom(nom);
            if (verif_nom!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_nom);
            }
        }
        else if (!ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_nom_sexe=tmpemploye.rechercher_combinaison_nom_sexe(nom,sexe);
            if (verif_nom_sexe!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_nom_sexe);
            }
        }
        else if (ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_sexe_date=tmpemploye.rechercher_combinaison_sexe_date(sexe,date);
            if (verif_sexe_date!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_sexe_date);
            }
        }
        else if (ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_nom_date=tmpemploye.rechercher_combinaison_nom_date(nom,date);
            if (verif_nom_date!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_nom_date);
            }
        }

        else if (!ui->checkBoxDate->isChecked())
        {
            QSqlQueryModel *verif_mail=tmpemploye.rechercher_email(email);
            if (verif_mail!=nullptr)
            {
                ui->tableViewEmploye->setModel(verif_mail);
            }
        }
}

















void GestionRH::on_pushButtonPDF_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("Liste Des Employés.pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(fileName);

                QTextDocument doc;
                QSqlQuery q;
                q.prepare("SELECT * FROM EMPLOYE ");
                q.exec();
                QString pdf="<br><br><img src='D:/bourguiba/ESPRIT/Second Year/Projet C++/logo.png' height='42' align='left' width='42'/>  <h1 align='middle' style='color:blue;   style='display: block;margin: auto;max-width: 600px;padding:5px;width: 100%;'>LISTE DES EMPLOYES  <><br></h1>\n <br> <table  style='border: 1px solid black;background: white; border-radius:3px; border-collapse: collapse; margin: auto;  padding:5px; width: 100%; box-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);'>  <tr>  <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>ID </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>NOM </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>NUM </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'> EMAIL </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;border: 1px solid black;'>Departement </th>  </tr>";


                while ( q.next()) {

                    pdf= pdf+ " <br> <tr style='border-top: 1px solid #C1C3D1; border-bottom-: 1px solid #C1C3D1; color:#666B85;padding-bottom:5px; font-size:16px; font-weight:normal; text-shadow: 0 1px 1px rgba(256, 256, 256, 0.1);'> <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+ q.value(0).toString()+"</td>  <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'> " + q.value(1).toString() +"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>" +q.value(2).toString() +"  "" " "</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(3).toString()+"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(6).toString()+" "  " " "</td> </td>" ;

                }
                doc.setHtml(pdf);
                doc.setPageSize(printer.pageRect().size()); // t5abbi numero l page
                doc.print(&printer);
}

void GestionRH::on_pushButtonPDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("Liste Des Employés.pdf"); }

                    QPrinter printer(QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setPaperSize(QPrinter::A4);
                    printer.setOutputFileName(fileName);

                    QTextDocument doc;
                    QSqlQuery q;
                    q.prepare("SELECT * FROM EMPLOYE ");
                    q.exec();
                    QString pdf="<br><br><img src='C:/Users/Seif/Desktop/logo.png' height='42' align='left' width='42'/>  <h1 align='middle' style='color:blue;   style='display: block;margin: auto;max-width: 600px;padding:5px;width: 100%;'>LISTE DES EMPLOYES  <><br></h1>\n <br> <table  style='border: 1px solid black;background: white; border-radius:3px; border-collapse: collapse; margin: auto;  padding:5px; width: 100%; box-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);'>  <tr>  <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>ID </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>NOM </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>NUM </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'> EMAIL </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;border: 1px solid black;'>Departement </th>  </tr>";


                    while ( q.next()) {

                        pdf= pdf+ " <br> <tr style='border-top: 1px solid #C1C3D1; border-bottom-: 1px solid #C1C3D1; color:#666B85;padding-bottom:5px; font-size:16px; font-weight:normal; text-shadow: 0 1px 1px rgba(256, 256, 256, 0.1);'> <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+ q.value(0).toString()+"</td>  <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'> " + q.value(1).toString() +"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>" +q.value(2).toString() +"  "" " "</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(3).toString()+"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(6).toString()+" "  " " "</td> </td>" ;

                    }
                    doc.setHtml(pdf);
                    doc.setPageSize(printer.pageRect().size()); // t5abbi numero l page
                    doc.print(&printer);
}

void GestionRH::on_pushButtonTrier_clicked()
{
    if (ui->checkBoxNom->isChecked() && !ui->checkBoxSexe->isChecked() && !ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("nom",ui->comboBoxOrdre->currentText()));
           else if (!ui->checkBoxNom->isChecked() && ui->checkBoxSexe->isChecked() && !ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("sexe",ui->comboBoxOrdre->currentText()));
           else if (!ui->checkBoxNom->isChecked() && !ui->checkBoxSexe->isChecked() && ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("date_naissance",ui->comboBoxOrdre->currentText()));
           else if (ui->checkBoxNom->isChecked() && ui->checkBoxSexe->isChecked() && !ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("nom, sexe",ui->comboBoxOrdre->currentText()));
           else if (ui->checkBoxNom->isChecked() && !ui->checkBoxSexe->isChecked() && ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("nom, date_naissance",ui->comboBoxOrdre->currentText()));
           else if (!ui->checkBoxNom->isChecked() && ui->checkBoxSexe->isChecked() && ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("sexe, date_naissance",ui->comboBoxOrdre->currentText()));
           else if (ui->checkBoxNom->isChecked() && ui->checkBoxSexe->isChecked() && ui->checkBoxDate->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("nom, sexe, date_naissance",ui->comboBoxOrdre->currentText()));
           else if (ui->checkBoxNom->isChecked())
               ui->tableViewEmploye->setModel(tmpemploye.trier("cin",ui->comboBoxOrdre->currentText()));
           //else if (ui->checkBoxMail->isChecked())
             //  ui->tableViewEmploye->setModel(tmpemploye.trier("mail",ui->comboBoxOrdre->currentText()));

}
void GestionRH::on_ajouter_clicked()
{
    conge tmpconge;
        if(ui->lineEditNumConge->text()!=""){
        QString id=ui->lineEditNumConge->text();
        QString nom=ui->lineEditType->text();
        QString dated=ui->dateEditDebut->date().toString();
        QString datef=ui->dateEditFin->date().toString();
        QString type=ui->comboBoxType->currentText();

        conge conge(id, nom, dated, datef, type);
        conge.ajouter();
        QSqlQueryModel * modell = tmpconge.afficher();
        ui->tableViewConge->setModel( modell);
        QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
           mm->setDynamicSortFilter(true);
           mm->setSourceModel(modell);
           ui->tableViewConge->setModel(mm);
           ui->tableViewConge->setSortingEnabled(true);
        foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
            widget->clear();
        }
    }
    else{
                QMessageBox::warning(this,"Erreur lors de l'ajout","Veuillez verifier tous les champs");
            }
}


void GestionRH::on_pushButtonEdit_clicked()
{
    conge tmpconge;

    if (ui->pushButtonEdit->isChecked())
            {
                ui->pushButtonEdit->setDisabled(true);
                ui->pushButtonEdit->setText("Modifiable");
                QSqlTableModel *tableModel= new QSqlTableModel();
                tableModel->setTable("CONGE");
                tableModel->select();
                ui->tableViewConge->setModel(tableModel);
            }
            else
            {
                ui->pushButtonEdit->setText("Modifier");
                QSqlQueryModel * modell = tmpconge.afficher();
               ui->tableViewConge->setModel( modell);
               QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
                   mm->setDynamicSortFilter(true);
                   mm->setSourceModel(modell);
                   ui->tableViewConge->setModel(mm);
                   ui->tableViewConge->setSortingEnabled(true);

            }
    ui->pushButtonEdit->setChecked(false);

}

void GestionRH::on_pushButtonSuppr_clicked()
{
    conge tmpconge;


    QItemSelectionModel *select = ui->tableViewConge->selectionModel();
        QString idemploye =select->selectedRows(0).value(0).data().toString();
        if(tmpconge.supprimer(idemploye))
            {
               QSqlQueryModel * modell = tmpconge.afficher();
               ui->tableViewConge->setModel( modell);
               QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
               mm->setDynamicSortFilter(true);
               mm->setSourceModel(modell);
               ui->tableViewConge->setModel(mm);
               ui->tableViewConge->setSortingEnabled(true);
            }
}





void GestionRH::on_pushButtonStatistiques_clicked()
{
    {
        conge tmpconge;
        QString id=ui->lineEdit_recherche_table->text();
        QString nomemploye=ui->lineEdit_recherche_table->text();
        QString type=ui->lineEdit_recherche_table->text();
        if (ui->checkBoxTypeConge->isChecked() && ui->checkBoxNomEmploye->isChecked() && ui->checkBoxNumConge->isChecked())
            {

                QSqlQueryModel *verif_combinaison=tmpconge.rechercher_combinaison_all(id,nomemploye,type);
                if (verif_combinaison!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_combinaison);
                }

            }
        else if (ui->checkBoxTypeConge->isChecked() && !ui->checkBoxNomEmploye->isChecked() && !ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_type=tmpconge.rechercher_type(type);
                if (verif_type!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_type);
                }
            }
            else if (!ui->checkBoxTypeConge->isChecked() && !ui->checkBoxNomEmploye->isChecked() && ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_id=tmpconge.recherche(id);
                if (verif_id!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_id);
                }
            }
            else if (!ui->checkBoxTypeConge->isChecked() && ui->checkBoxNomEmploye->isChecked() && !ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_nomemploye=tmpconge.rechercher_nomemploye(nomemploye);
                if (verif_nomemploye!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_nomemploye);
                }
            }
            else if (ui->checkBoxTypeConge->isChecked() && ui->checkBoxNomEmploye->isChecked() && !ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_nom_type=tmpconge.rechercher_combinaison_nom_type(nomemploye,type);
                if (verif_nom_type!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_nom_type);
                }
            }
            else if (!ui->checkBoxTypeConge->isChecked() && ui->checkBoxNomEmploye->isChecked() && ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_id_nom=tmpconge.rechercher_combinaison_id_nom(id,nomemploye);
                if (verif_id_nom!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_id_nom);
                }
            }
            else if (ui->checkBoxTypeConge->isChecked() && !ui->checkBoxSexe->isChecked() && ui->checkBoxNumConge->isChecked())
            {
                QSqlQueryModel *verif_type_id=tmpconge.rechercher_combinaison_id_type(id,type);
                if (verif_type_id!=nullptr)
                {
                    ui->tableViewConge->setModel(verif_type_id);
                }
            }
    }

}


void GestionRH::on_clock_clicked()
{
    DigitalClock * clock = new   DigitalClock();
        clock->show();
}

void GestionRH::on_clock_2_clicked()
{
    audio =new AudioPlayer();
    audio ->show();
}
