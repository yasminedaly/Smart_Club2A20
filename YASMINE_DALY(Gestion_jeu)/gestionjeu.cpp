#include "gestionjeu.h"
#include "ui_gestionjeu.h"
#include "joueur.h"
#include "partie.h"
#include "game.h"
#include "smtp.h"
#include "exportexcelobject.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QIntValidator>
#include <QSqlQuery>
#include <QPainter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QTimer>
#include <QDateTime>
#include <QtMultimedia/QSound>
#include "qcustomplot.h"
#include <QMediaPlayer>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>



Game *game=nullptr;



Gestionjeu::Gestionjeu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gestionjeu)
{

    qDebug() << "DEBUG TRACE" << Q_FUNC_INFO<<"@ line #"<< __LINE__;
    qDebug() << "DEBUG TRACE" << Q_FUNC_INFO<<"@ line #"<< __LINE__;
    qDebug() << "DEBUG TRACE" << Q_FUNC_INFO<<"@ line #"<< __LINE__;
    ui->setupUi(this);


    //arduino

    /*int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).*/
    ui->id_j->setValidator (new QIntValidator(0, 9999, this));
    ui->tel_j->setValidator (new QIntValidator(100000000, 99999999, this));
    ui->classement_j->setValidator (new QIntValidator(0, 9999, this));
    ui->tab_afficher_joueur->setModel(J.afficher_joueur());
    ui->tab_afficher_partie->setModel(P.afficher_partie());
    QTimer *timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    QDate dateTime=QDate::currentDate();
    QString datetimetext=dateTime.toString();
    ui->DateTime->setText(datetimetext);


    QMediaPlayer * music =new QMediaPlayer;
     music->setMedia(QUrl("C:/Users/ASUS/Desktop/Mesetudes2A/semestre2/projet/Joueurs_Parties/Sons/welcome.mp3")) ;

     music->play();

    //customPlot = new QCustomPlot(this);



    animation= new QPropertyAnimation(ui->ajouter_joueur,"geometry");
    animation->setDuration(5000);
    animation->setEndValue(QRect(10,510,131,41));
    animation->start();
    animation= new QPropertyAnimation(ui->modifier_joueur,"geometry");
    animation->setDuration(5000);
    animation->setEndValue(QRect(140,510,131,41));
    animation->start();
    animation= new QPropertyAnimation(ui->supprimer_joueur,"geometry");
    animation->setDuration(5000);
    animation->setEndValue(QRect(270,510,131,41));
    animation->start();
}

void Gestionjeu::showTime()
{
    QTime time=QTime::currentTime();

    QString time_text=time.toString("hh : mm : ss");
    if ((time.second() % 2) == 0)
    {
        time_text[3]= ' ';
        time_text[8]= ' ';
    }
    ui->Digital_clock->setText(time_text);
}

Gestionjeu::~Gestionjeu()
{
    delete ui;
}

void change(QLabel * label, const QString & text, int ms_keep = 7000, int ms_after = 0)
{
    //QString originaltext = label->text();
    QTimer::singleShot(ms_after, [=](){
        label->setText(text);
        QTimer::singleShot(ms_keep, [=](){
            label->setText("");
        });
    });
}

void Gestionjeu::on_ajouter_joueur_clicked()
{
    int id_joueur=ui->id_j->text().toInt();
    QString nom_joueur=ui->nom_j->text();
    QString prenom_joueur=ui->prenom_j->text();
    QString ville_joueur=ui->ville_j->text();
    QDate date= ui->dn_j->date();
    QString dn_joueur= date.toString("dd/MM/yy");
    QString email_joueur=ui->email_j->text();
    int tel_joueur=ui->tel_j->text().toInt();
    int classement_elo=ui->classement_j->text().toInt();

    Joueur J(id_joueur,nom_joueur,prenom_joueur,ville_joueur,dn_joueur,email_joueur,tel_joueur,classement_elo);


       // fileNameImage="";

    if(J.veriftel(J.gettel_joueur())==false)
    {
        change(ui->wrongphone_j, "<font color='red'>Le numéro de téléphone doit comporter exactement 8 chiffres</font>",7000, 0);
    }
    if(J.verifierid_aj(J.getid_joueur())==false)
    {
// ui->wrongid_j->setText("<font color='red'>Vérifiez l'id</font>");
        change(ui->wrongid_j, "<font color='red'>L'id du joueur doit etre unique</font>",7000, 0);
    }
    if(J.verifvidestring(J.getnom_joueur())==false)
    {
        change(ui->wrongnom_j, "<font color='red'>Le champ nom est vide</font>",7000, 0);
    }

    if(J.verifvidestring(J.getprenom_joueur())==false)
    {
        change(ui->wrongprenom_j, "<font color='red'>Le champ prénom est vide</font>",7000, 0);
    }
    if(J.verifvidestring(J.getville_joueur())==false)
    {
        change(ui->wrongville_j, "<font color='red'>Le champ ville est vide</font>",7000, 0);
    }
    if(J.verifvidestring(J.getdn_joueur())==false)
    {
        change(ui->wrongdate_j, "<font color='red'>Le champ ville est vide</font>",7000, 0);
    }
    if(J.verifvidestring(J.getville_joueur())==false)
    {
        change(ui->wrongville_j, "<font color='red'>Le champ ville est vide</font>",7000, 0);
    }
    if(J.verifvidestring(J.getemail_joueur())==false)
    {
        change(ui->wrongmail_j, "<font color='red'>Le champ email est vide</font>",7000, 0);
    }
    if(J.verifint(J.getclassement_elo())==false)
    {
        change(ui->wrongclass_elo, "<font color='red'>Le champ classement élo est vide</font>",7000, 0);
    }
    if( J.verifierid_aj(J.getid_joueur())==true && J.verifvidestring(J.getnom_joueur())==true && J.verifvidestring(J.getprenom_joueur())==true &&
            J.verifvidestring(J.getville_joueur())==true && J.verifvidestring(J.getdn_joueur())==true && J.verifvidestring(J.getemail_joueur())==true &&
            J.veriftel(J.gettel_joueur())==true && J.verifint(J.getclassement_elo())==true)
       {
        J.AjoutImage(fileNameImage);
        bool test=J.ajouter_joueur();


        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_joueur->setModel(J.afficher_joueur());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }


}





void Gestionjeu::on_ajouter_photo_j_clicked()
{
    QString fileName=QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("Document files ((*.jpg;*.jpeg));;All files (*.*)"),0 );
    QPixmap pixmap;
    if (QFile::exists(fileName))
    {
        fileNameImage=fileName;
        pixmap=fileName;
        ui->photo_j->setPixmap(pixmap);

    }
}



void Gestionjeu::on_supprimer_joueur_clicked()
{

    Joueur J1;
    J1.setid_joueur(ui->id_j->text().toInt());
    bool test = J1.verifierid(J1.getid_joueur());
    if(test)
    {
        J1.supprimer_joueur(J1.getid_joueur());
        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Suppression effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_afficher_joueur->setModel(J.afficher_joueur());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
    }
}


void Gestionjeu::on_tab_afficher_joueur_activated(const QModelIndex &index)
{
    QString val=ui->tab_afficher_joueur->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * from joueurs where id_joueur='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_j->setText(qry.value(0).toString());
            ui->nom_j->setText(qry.value(1).toString());
            ui->prenom_j->setText(qry.value(2).toString());
            ui->ville_j->setText(qry.value(3).toString());
            ui->dn_j->setDate(qry.value(4).toDate());
            ui->email_j->setText(qry.value(5).toString());
            ui->tel_j->setText(qry.value(6).toString());
            ui->classement_j->setText(qry.value(7).toString());
            array = qry.value(8).toByteArray();
            QBuffer buffer(&array);
            image=(array);
            QPixmap outPixmap = QPixmap();
            outPixmap.loadFromData( image );
            ui->photo_j->setPixmap(outPixmap) ;
            //or nom_joueur='"+val+"' or prenom_joueur='"+val+"' or ville_joueur='"+val+"' or dn_joueur='"+val+"'  or email_joueur='"+val+"' or tel_joueur='"+val+"' or classement_elo='"+val+"' "



        }
    }

}

void Gestionjeu::on_modifier_joueur_clicked()
{


    int id_joueur=ui->id_j->text().toInt();
    QString nom_joueur=ui->nom_j->text();
    QString prenom_joueur=ui->prenom_j->text();
    QString ville_joueur=ui->ville_j->text();
    QDate date= ui->dn_j->date();
    QString dn_joueur= date.toString("dd/MM/yy");
    QString email_joueur=ui->email_j->text();
    int tel_joueur=ui->tel_j->text().toInt();
    int classement_elo=ui->classement_j->text().toInt();

    Joueur J(id_joueur,nom_joueur,prenom_joueur,ville_joueur,dn_joueur,email_joueur,tel_joueur,classement_elo);

    if( J.verifint(J.getid_joueur())==true && J.verifvidestring(J.getnom_joueur())==true && J.verifvidestring(J.getprenom_joueur())==true &&
            J.verifvidestring(J.getville_joueur())==true && J.verifvidestring(J.getdn_joueur())==true && J.verifvidestring(J.getemail_joueur())==true &&
            J.verifint(J.gettel_joueur())==true && J.verifint(J.getclassement_elo())==true)
       {
        J.AjoutImage(fileNameImage);
        bool test=J.modifier_joueur();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_joueur->setModel(J.afficher_joueur());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Modification non effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }

}

void Gestionjeu::on_ajouter_partie_clicked()
{   //int idn;




    int id_partie=ui->id_p->text().toInt();
    QString cadence=ui->cadence->text();
    int id_noir=ui->id_n->text().toInt();
    int id_blanc=ui->id_b->text().toInt();
    QDateTime date1=ui->debut_p->dateTime();
    QString debut_partie= date1.toString("dd/MM/yy");
    QDateTime date2=ui->fin_p->dateTime();
    QString fin_partie= date2.toString("dd/MM/yy");
    QString gagnant_partie=ui->gagnant_p->text();
    int num_table=ui->table_p->text().toInt();
    QString com_partie=ui->com_p->text();

    Partie P(id_partie,cadence,id_noir,id_blanc,debut_partie,fin_partie,gagnant_partie,num_table,com_partie);


    if(P.verifierid_aj(P.getid_partie())==false)
    {
        change(ui->wrongid_p, "<font color='red'>L'id d'une partie doit etre unique</font>",7000, 0);
    }

    if(P.verifvidestring(P.getcadence())==false)
    {
        change(ui->wrongcadence, "<font color='red'>Le champ nom est vide</font>",7000, 0);
    }

    if(P.verifint(P.getid_noir())==false)
    {
        change(ui->wrongj_noir, "<font color='red'>Il faut saisir un joueur pour les pièces noires</font>",7000, 0);
    }
    if(P.verifint(P.getid_blanc())==false)
    {
        change(ui->wrongj_blanc, "<font color='red'>Il faut saisir un joueur pour les pièces blanches</font>",7000, 0);
    }

    if(P.verifint(P.getnum_table())==false)
    {
        change(ui->wrongnum_table, "<font color='red'>Il faut préciser le numéro de la table</font>",7000, 0);
    }

    if(P.verifvidestring(P.getcom_partie())==false)
    {
        change(ui->wrongcommentaire, "<font color='red'>Le champ commentaire est vide</font>",7000, 0);
    }
    if( P.verifierid_aj(P.getid_partie())==true && P.verifvidestring(P.getcadence())==true && P.verifint(P.getid_noir())==true &&
            P.verifint(P.getid_blanc())==true && P.verifvidestring(P.getdebut_partie())==true && P.verifvidestring(P.getfin_partie())==true &&
            P.verifvidestring(P.getgagnant_partie())==true && P.verifint(P.getnum_table())==true && P.verifvidestring(P.getcom_partie())==true )
       {
        bool test=P.ajouter_partie();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_partie->setModel(P.afficher_partie());


            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("Tous les champs sont obligatoires\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void Gestionjeu::on_tab_afficher_partie_activated(const QModelIndex &index)
{
   QString val=ui->tab_afficher_partie->model()->data(index).toString();
   QSqlQuery qry;
    qry.prepare("SELECT * from parties where id_partie='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_p->setText(qry.value(0).toString());
            ui->cadence->setText(qry.value(1).toString());
            ui->id_n->setText(qry.value(2).toString());
            ui->id_b->setText(qry.value(3).toString());
            ui->debut_p->setDateTime(qry.value(4).toDateTime());
            ui->fin_p->setDateTime(qry.value(5).toDateTime());
            ui->gagnant_p->setText(qry.value(6).toString());
            ui->table_p->setText(qry.value(7).toString());
            ui->com_p->setText(qry.value(8).toString());




        }
    }
}

void Gestionjeu::on_supprimer_partie_clicked()
{
    Partie P;
    P.setid_partie(ui->id_p->text().toInt());
    bool test = P.verifierid(P.getid_partie());
    if(test)
    {
        P.supprimer_partie(P.getid_partie());
        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_afficher_partie->setModel(P.afficher_partie());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void Gestionjeu::on_modifier_partie_clicked()
{
    int id_partie=ui->id_p->text().toInt();
    QString cadence=ui->cadence->text();
    int id_noir=ui->id_n->text().toInt();
    int id_blanc=ui->id_b->text().toInt();
    QDateTime date1=ui->debut_p->dateTime();
    QString debut_partie= date1.toString("dd/MM/yy");
    QDateTime date2=ui->fin_p->dateTime();
    QString fin_partie= date2.toString("dd/MM/yy");
    QString gagnant_partie=ui->gagnant_p->text();
    int num_table=ui->table_p->text().toInt();
    QString com_partie=ui->com_p->text();

    Partie P(id_partie,cadence,id_noir,id_blanc,debut_partie,fin_partie,gagnant_partie,num_table,com_partie);

    if( P.verifint(P.getid_partie())==true && P.verifvidestring(P.getcadence())==true && P.verifint(P.getid_noir())==true &&
            P.verifint(P.getid_blanc())==true && P.verifvidestring(P.getdebut_partie())==true && P.verifvidestring(P.getfin_partie())==true &&
            P.verifvidestring(P.getgagnant_partie())==true && P.verifint(P.getnum_table())==true && P.verifvidestring(P.getcom_partie())==true )
       {
        bool test=P.modifier_partie();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_partie->setModel(P.afficher_partie());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Modification non effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("Tous les champs sont obligatoires\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void Gestionjeu::on_chercher_joueur_clicked()
{
    int choix;
        choix=ui->chercher_j->currentIndex();
        QString linechercher=ui->le_chercher_joueur->text();
        ui->tab_afficher_joueur->setModel(J.chercher_joueur(choix,linechercher));
}

void Gestionjeu::on_chercher_partie_clicked()
{
    int choix;
        choix=ui->chercher_p->currentIndex();
        QString linechercher=ui->le_chercher_partie->text();
        ui->tab_afficher_partie->setModel(P.chercher_partie(choix,linechercher));
}

void Gestionjeu::on_trier_joueur_clicked()
{
    int choix;
       choix=ui->trier_j->currentIndex();
       ui->tab_afficher_joueur->setModel(J.trier_joueur(choix));
}

void Gestionjeu::on_trier_partie_clicked()
{
    int choix;
       choix=ui->trier_p->currentIndex();
       ui->tab_afficher_partie->setModel(P.trier_partie(choix));
}

void Gestionjeu::on_imprimer_partie_clicked()
{





    QString strStream;
     QTextStream out(&strStream);
                     const int rowCount = ui->tab_afficher_partie->model()->rowCount();
                     const int columnCount = ui->tab_afficher_partie->model()->columnCount();
                     QString TT = QDate::currentDate().toString("yyyy/MM/dd");

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                             "<img src='C:/Users/ASUS/Desktop/Mesetudes2A/semestre2/projet/Joueurs_Parties/Images/logo.png' width='100' height='100'>\n"

                         "<center> <H1>Liste des parties "+TT+" </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#FF2E01> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tab_afficher_partie->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tab_afficher_partie->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tab_afficher_partie->isColumnHidden(column)) {
                                 QString data = ui->tab_afficher_partie->model()->data(ui->tab_afficher_partie->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));


                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n";
out << "<tr>\n"
"<center><img src='C:/Users/ASUS/Desktop/Mesetudes2A/semestre2/projet/Joueurs_Parties/Images/pic.jpg' width='300' height='150'></center>\n"
                         "</body>\n"
                         "</html>\n";

                     QTextDocument *document = new QTextDocument();
                     document->setHtml(strStream);
                     QPrinter printer;

                     QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                     if (dialog->exec() == QDialog::Accepted) {
                         document->print(&printer);
                     }

                     delete document;
}

void Gestionjeu::on_excel_joueur_clicked()
{



    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tab_afficher_joueur);

        //colums to export
        obj.addField(0, "Id", "char(20)");
        obj.addField(1, "Nom", "char(20)");
        obj.addField(2, "Prénom", "char(20)");
        obj.addField(3, "Ville", "char(20)");
        obj.addField(4, "Date_de_naissance", "char(50)");
        obj.addField(5, "Email", "char(250)");
        obj.addField(6, "Téléphone", "char(20)");
        obj.addField(7, "Classement_élo", "char(20)");





        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }

}


void Gestionjeu::on_envoyer_mail_released()
{
    Smtp *s=new Smtp("partiesjeuechec@gmail.com","gestionjeu123","smtp.gmail.com",465);
    s->sendMail("partiesjeuechec@gmail.com",ui->destinataire_mail->text(),ui->objet_mail->text(),ui->text_mail->text());
    QMessageBox::information(nullptr,QObject::tr("Ok"),
                         QObject::tr("Mail envoyé\n"
                                       "Click cancel to exit."),QMessageBox::Cancel);
}

void Gestionjeu::on_afficher_tout_joueurs_clicked()
{
    ui->tab_afficher_joueur->setModel(J.afficher_joueur());
}


void Gestionjeu::on_afficher_tout_parties_clicked()
{
    ui->tab_afficher_partie->setModel(P.afficher_partie());
}

/*
  void Gestionjeu::on_ajouter_image_clicked()
{
    QString fileName=QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("Document files (*.doc *.rtf);;All files (*.*)"),0 );
    QPixmap pixmap;
    if (QFile::exists(fileName))
    {
        fileNameImage=fileName;
        pixmap=fileName;
        ui->label_photo->setPixmap(pixmap);
    }
}
*/

void Gestionjeu::on_stat_joueur_clicked()
{
    double man=0;
    double gaf=0;
    double tun=0;
    double ari=0;


    QSqlQuery q;
        q.prepare("SELECT * FROM joueurs WHERE upper(ville_joueur) = 'MANOUBA' ");
        q.exec();
          while (q.next())
        {
        man++;
        }

          q.prepare("SELECT * FROM joueurs WHERE upper(ville_joueur) = 'GAFSA' ");
          q.exec();
            while (q.next())
          {
          gaf++;
          }
            q.prepare("SELECT * FROM joueurs WHERE upper(ville_joueur) = 'TUNIS' ");
            q.exec();
              while (q.next())
            {
            tun++;
            }
              q.prepare("SELECT * FROM joueurs WHERE upper(ville_joueur) = 'ARIANA' ");
              q.exec();
                while (q.next())
              {
              ari++;
              }

    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->gplot->setBackground(QBrush(gradient));

    // create empty bar chart objects:

    QCPBars *fossil = new QCPBars(ui->gplot->xAxis, ui->gplot->yAxis);
    fossil->setAntialiased(false);


    fossil->setStackingGap(2);
    // set names and colors:

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 ;
    labels << "Manouba" << "Gafsa" << "Tunis" << "Ariana";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->gplot->xAxis->setTicker(textTicker);
    ui->gplot->xAxis->setTickLabelRotation(60);
    ui->gplot->xAxis->setSubTicks(false);
    ui->gplot->xAxis->setTickLength(0, 4);
    ui->gplot->xAxis->setRange(0, 13);
    ui->gplot->xAxis->setBasePen(QPen(Qt::white));
    ui->gplot->xAxis->setTickPen(QPen(Qt::white));
    ui->gplot->xAxis->grid()->setVisible(true);
    ui->gplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->gplot->xAxis->setTickLabelColor(Qt::white);
    ui->gplot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->gplot->yAxis->setRange(0, 10);
    ui->gplot->yAxis->setPadding(5); // a bit more space to the left border
    ui->gplot->yAxis->setLabel("Nombre de joueurs");
    ui->gplot->yAxis->setBasePen(QPen(Qt::white));
    ui->gplot->yAxis->setTickPen(QPen(Qt::white));
    ui->gplot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->gplot->yAxis->grid()->setSubGridVisible(true);
    ui->gplot->yAxis->setTickLabelColor(Qt::white);
    ui->gplot->yAxis->setLabelColor(Qt::white);
    ui->gplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->gplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData;

    fossilData  << man << gaf << tun << ari ;
    fossil->setData(ticks, fossilData);

    //ui->gplot->legend->setVisible(true);
    ui->gplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->gplot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->gplot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->gplot->legend->setFont(legendFont);
    ui->gplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void Gestionjeu::on_notes_clicked()
{
    notepad = new Notepad();
    notepad->show();

}




void Gestionjeu::on_prendre_photo_clicked()
{
    camera = new Camera();
    camera->show();
}

void Gestionjeu::on_qrcode_clicked()
{

    qrcode = new QRplusplus();
    qrcode->show();
}

void Gestionjeu::on_lancer_partie_clicked()
{
    game= new Game();
    game->show();
    game->displayMainMenu();

}


void Gestionjeu::update_label()
{
     /*  data=A.read_from_arduino();

    if(data=="1")

        ui->nbr_perso->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->nbr_perso->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON*/
}

void Gestionjeu::on_autoriser_acces_clicked()
{
    //  A.write_to_arduino("1"); //envoyer 1 à arduino
}

void Gestionjeu::on_refuser_acces_clicked()
{
     // A.write_to_arduino("0"); //envoyer 1 à arduino
}

void Gestionjeu::on_score_clicked()
{
    const Qt::WindowFlags flags(Qt::Window | Qt::WindowStaysOnTopHint);
    controls.setWindowFlags(flags);
    controls.show();



}
