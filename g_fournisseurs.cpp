#include "g_fournisseurs.h"
#include "ui_g_fournisseurs.h"
#include "connection.h"
#include "fournisseur_fidele.h"
#include "statistics.h"



#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QDate>
#include <QtMultimedia/QMediaPlayer>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QFile>
#include <QPrintDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QSystemTrayIcon>
#include <QAbstractSocket>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QTimer>
#include <QDateTime>






G_Fournisseurs::G_Fournisseurs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::G_Fournisseurs)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/lenovo/Desktop/BACK.jpg");
    ui->label_PIC6->setPixmap(pix);
    ui->label_PIC7->setPixmap(pix);
    ui->label_PIC8->setPixmap(pix);


    animation= new QPropertyAnimation(ui->excel_g_fournisseurs,"geometry");
    animation->setDuration(10000);
    animation->setStartValue(ui->excel_g_fournisseurs->geometry());
    animation->setEndValue(QRect(870,190,93,28));
    animation->start();

    animation2= new QPropertyAnimation(ui->pdf_g_fournisseur,"geometry");
    animation2->setDuration(10000);
    animation2->setStartValue(ui->pdf_g_fournisseur->geometry());
    animation2->setEndValue(QRect(610,350,93,28));
    animation2->start();

    animation3= new QPropertyAnimation(ui->statistiques_factures,"geometry");
    animation3->setDuration(10000);
    animation3->setStartValue(ui->statistiques_factures->geometry());
    animation3->setEndValue(QRect(610,410,141,28));
    animation3->start();


    animation4= new QPropertyAnimation(ui->imprimer,"geometry");
    animation4->setDuration(10000);
    animation4->setStartValue(ui->imprimer->geometry());
    animation4->setEndValue(QRect(610,480,93,28));
    animation4->start();

    notif= new QSystemTrayIcon(this) ;

    if(Fatmp.Alerte2()==true)
    {
        notif->setIcon(QIcon(":/ressources_img/icon_non_payment.png"));
        notif->setVisible(true);
        notif->showMessage(tr("Alerte ! Veuillez vérifiez !  "),QString(tr("%1 factures non payées!")).arg(Fatmp.Statistiques_Factures_N())) ;
    }


    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));

    fail=new QMediaPlayer();
    fail->setMedia(QUrl("qrc:/sounds/fail.wav"));

    success=new QMediaPlayer();
    success->setMedia(QUrl("qrc:/sounds/successfully.wav"));


    timer= new QTimer(this) ;
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(1000);


    ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
    ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
    ui->tableView_Produit_G_fournisseurs->setModel(Ptmp.afficher_Produit());
    ui->alerte->setModel(Fatmp.Alerte());
    ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());


    ui->lineEdit_idfournisseur_facture->addItems(Fotmp.listeFournisseurs());
    ui->ID_produit_facture->addItems(Ptmp.listeProduits());

    ui->total_factures_calcul->setText(QString::number(Fatmp.Calcul_Total()));


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret)
    {
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
    break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
    break;
    case(-1):qDebug() << "arduino is not available";
     }


}


void G_Fournisseurs::display_id_fournisseur()
{
    ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
    QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
}

void G_Fournisseurs::display_nom_fournisseur()
{
    ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
    QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
}

void G_Fournisseurs::display_adresse_fournisseur()
{
    ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
    QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
}

void G_Fournisseurs::display_mail_fournisseur()
{
    ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
    QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
}

void G_Fournisseurs::display_telephone_fournisseur()
{
    ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
    QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
}


G_Fournisseurs::~G_Fournisseurs()
{
    delete ui;
}

void G_Fournisseurs::myfunction()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString time_text = time.toString("hh : mm : ss");
    QString date_text = date.toString("dd/MM/yyyy");
    if((time.second())%2 == 0)
    {
        time_text[3]= ' ' ;
        time_text[8]= ' ' ;
    }
    ui->label_date_time_->setText(time_text);
    ui->date_time_label->setText(date_text);

}

void G_Fournisseurs::on_ajouter_fournisseur__clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();


    int ID_Fournisseur =ui->lineEdit_IDFournisseur->text().toInt();
    QString Nom_Fournisseur=ui->lineEdit_NomFournisseur->text();
    QString Adresse_Fournisseur= ui->lineEdit_Adressefournisseur->text() ;
    QString Telephone_Fournisseur=ui->lineEdit_telfournisseur->text();
    QString Email_Fournisseur= ui->lineEdit_emailfournisseur->text();

    QString id_fou = QString::number(ID_Fournisseur);


    bool valid = false;
    if ( Email_Fournisseur.contains("@gmail.com") )
    {
        valid = true;
    }



    Fournisseurs Fo(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);



     if ( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==false )
    {
        fail->play();

        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_id_fournisseur->setText("Enter an ID");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }
        else
        {
            ui->label_erreur_id_fournisseur->setText("Entrez un ID");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }


    }

     if ( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==true )
    {

        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_id_fournisseur->setText("");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }
        else
        {
            ui->label_erreur_id_fournisseur->setText("");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }


    }
     if ( Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==false )
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_nom_fournisseur->setText("Enter a Name");
            ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
        }
        else
        {
            ui->label_erreur_nom_fournisseur->setText("Entrez un Nom ");
            ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
        }


    }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==true )
    {

         if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_nom_fournisseur->setText("");
            ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
        }
        else
        {
            ui->label_erreur_nom_fournisseur->setText("");
            ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
        }


    }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==false )
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_adresse_fournisseur->setText("Enter an Adress");
            ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
        }
        else
        {
            ui->label_erreur_adresse_fournisseur->setText("Entrez une adresse ");
            ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
        }

    }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==true )
    {
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_adresse_fournisseur->setText("");
            ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
        }
        else
        {
            ui->label_erreur_adresse_fournisseur->setText("");
            ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
        }

    }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==false)
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_telephone_fournisseur->setText("Enter a Phone Number");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
        else
        {
            ui->label_erreur_telephone_fournisseur->setText("Entrez un numéro de téléphone ");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
    }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==true)
    {
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_telephone_fournisseur->setText("");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
        else
        {
            ui->label_erreur_telephone_fournisseur->setText("");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
    }

     if ( Fo.Get_Telephone_Fournisseur().length() != 8)
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_telephone_fournisseur->setText("Phone Number must be with 8");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
        else
        {
            ui->label_erreur_telephone_fournisseur->setText("un numéro de téléphone doit contenir 8 chiffres");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
    }

     if ( Fo.Get_Telephone_Fournisseur().length() == 8)
    {
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_telephone_fournisseur->setText("");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
        else
        {
            ui->label_erreur_telephone_fournisseur->setText("");
            ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
        }
    }


     if (Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==false)
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_email_fournisseur->setText("Enter an Email adress");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
        else
        {
            ui->label_erreur_email_fournisseur->setText("Entrez une adresse mail");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
    }

     if (Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==true)
    {
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_email_fournisseur->setText("");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
        else
        {
            ui->label_erreur_email_fournisseur->setText("");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
    }

     if ( valid == false)
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_email_fournisseur->setText("Enter a valid Email adress");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
        else
        {
            ui->label_erreur_email_fournisseur->setText("Entrez une adresse mail valide ");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
    }

     if ( valid == true)
    {
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_email_fournisseur->setText("");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
        else
        {
            ui->label_erreur_email_fournisseur->setText("");
            ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
        }
    }


     if( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==true && valid == true )
    {
        bool test=Fo.ajouter_Fournisseur();
        int nb =0;
        Fournisseur_Fidele Fourni(Fo.Get_ID_Fournisseur() , nb) ;
        Fourni.ajouter_Fournisseur_Fidele();

    if(test)
    {
        success->play();

        FF.modifier_Fournisseur_Fidele(Fo.Get_ID_Fournisseur());

        ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
        ui->lineEdit_idfournisseur_facture->clear();
        ui->lineEdit_idfournisseur_facture->addItems(Fotmp.listeFournisseurs());
        ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());


        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/add_fournisseur_icon.png"));
            msgBox.setText("fournisseur added ");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/add_fournisseur_icon.png"));
            msgBox.setText("Le fournisseur a été ajouté avec succés ");
            msgBox.exec();
        }


                ui->lineEdit_IDFournisseur->clear();
                ui->lineEdit_NomFournisseur->clear();
                ui->lineEdit_Adressefournisseur->clear() ;
                ui->lineEdit_telfournisseur->clear();
                ui->lineEdit_emailfournisseur->clear();
    }
    else
    {
        fail->play();
        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            QMessageBox::critical(nullptr, QObject::tr("Error ! "),
            QObject::tr("Problem when adding .\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout ! "),
            QObject::tr("Ajout non effectué.\n" " Appuyé sur cancel pour quitter ."), QMessageBox::Cancel);
        }

    }
    }

}

void G_Fournisseurs::on_supprimer_fournisseur__clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
        click->play();

        Fournisseurs Fou ;
        Fou.Set_ID_Fournisseur(ui->lineEdit_IDFournisseur->text().toInt());
        bool testing=Fou.Verifier_ID(Fou.Get_ID_Fournisseur()) ;
        if(testing)
        {

           QMessageBox::StandardButton reply = QMessageBox::question(this,
           "Suppression en cours ", "Etes vous sur de supprimer ! ",
           QMessageBox::Yes | QMessageBox::No);
          if(reply == QMessageBox::Yes)
            {
              success->play();

              Fou.supprimer_Fournisseur(Fou.Get_ID_Fournisseur());

              Fournisseur_Fidele Fourni ;
              Fourni.supprimer_Fournisseur_Fidele(Fou.Get_ID_Fournisseur());


              ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
              ui->lineEdit_idfournisseur_facture->clear();
              ui->lineEdit_idfournisseur_facture->addItems(Fotmp.listeFournisseurs());
              ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());


              if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
              {
                  QMessageBox msgBox;
                  msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/fournisseur_suppression.png"));
                  msgBox.setText("fournisseur deleted  ");
                  msgBox.exec();
              }
              else
              {
                  QMessageBox msgBox;
                  msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/fournisseur_suppression.png"));
                  msgBox.setText("Le fournisseur a été supprimé avec succés ");
                  msgBox.exec();
              }




              ui->lineEdit_IDFournisseur->clear();
              ui->lineEdit_NomFournisseur->clear();
              ui->lineEdit_Adressefournisseur->clear() ;
              ui->lineEdit_telfournisseur->clear();
              ui->lineEdit_emailfournisseur->clear();
           }
          else
           {
              if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
              {
                  QMessageBox::information(nullptr, QObject::tr("delete "),
                  QObject::tr("deletion performed .\n" "Click Cancel to exit."), QMessageBox::Cancel);
              }
              else
              {
                  QMessageBox::information(nullptr, QObject::tr("Suppression avec succés"),
                  QObject::tr("Suppression non effectuée .\n" "Appuyé sur cancel pour quitter."), QMessageBox::Cancel);
              }


           }
        }
        else
        {
            fail->play();

            QMessageBox::critical(nullptr, QObject::tr("OK"),
            QObject::tr("Vérifiez l'ID .\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void G_Fournisseurs::on_modifier_fournisseur__clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();


    int ID_Fournisseur =ui->lineEdit_IDFournisseur->text().toInt();
    QString Nom_Fournisseur=ui->lineEdit_NomFournisseur->text();
    QString Adresse_Fournisseur= ui->lineEdit_Adressefournisseur->text() ;
    QString Telephone_Fournisseur=ui->lineEdit_telfournisseur->text();
    QString Email_Fournisseur= ui->lineEdit_emailfournisseur->text();

    QString id_fou = QString::number(ID_Fournisseur);


    bool valid = false ;

    if ( Email_Fournisseur.contains("@gmail.com") )
    {
        valid = true;
    }


    Fournisseurs Fo(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);



     if (Fo.Verifier_ID(Fo.Get_ID_Fournisseur())==false)
    {
        fail->play();

        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_id_fournisseur->setText("ID already exist");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }
        else
        {
            ui->label_erreur_id_fournisseur->setText("ID existe déja");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }

    }

     if (Fo.Verifier_ID(Fo.Get_ID_Fournisseur())==true)
    {

        if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
        {
            ui->label_erreur_id_fournisseur->setText("");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }
        else
        {
            ui->label_erreur_id_fournisseur->setText("");
            ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
            QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
        }

    }

     if ( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_id_fournisseur->setText("Enter an ID");
                ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
            }
            else
            {
                ui->label_erreur_id_fournisseur->setText("Entrez un ID");
                ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
            }


        }

     if ( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==true )
        {

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_id_fournisseur->setText("");
                ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
            }
            else
            {
                ui->label_erreur_id_fournisseur->setText("");
                ui->label_erreur_id_fournisseur->setVisible(!ui->label_erreur_id_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_id_fournisseur()));
            }


        }


     if ( Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==false )
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_nom_fournisseur->setText("Enter a Name");
                ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
            }
            else
            {
                ui->label_erreur_nom_fournisseur->setText("Entrez un Nom ");
                ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
            }


        }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==true )
        {
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_nom_fournisseur->setText("");
                ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
            }
            else
            {
                ui->label_erreur_nom_fournisseur->setText("");
                ui->label_erreur_nom_fournisseur->setVisible(!ui->label_erreur_nom_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_nom_fournisseur()));
            }


        }
     if ( Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==false )
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_adresse_fournisseur->setText("Enter an Adress");
                ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
            }
            else
            {
                ui->label_erreur_adresse_fournisseur->setText("Entrez une adresse ");
                ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
            }

        }

      if ( Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==true )
         {
             if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
             {
                 ui->label_erreur_adresse_fournisseur->setText("");
                 ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
                 QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
             }
             else
             {
                 ui->label_erreur_adresse_fournisseur->setText("");
                 ui->label_erreur_adresse_fournisseur->setVisible(!ui->label_erreur_adresse_fournisseur->isVisible());
                 QTimer::singleShot(500,this,SLOT(display_adresse_fournisseur()));
             }

         }

     if ( Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==false)
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_telephone_fournisseur->setText("Enter a Phone Number");
                ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
            }
            else
            {
                ui->label_erreur_telephone_fournisseur->setText("Entrez un numéro de téléphone ");
                ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
            }
        }

      if ( Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==true)
              {
                  if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
                  {
                      ui->label_erreur_telephone_fournisseur->setText("");
                      ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                      QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
                  }
                  else
                  {
                      ui->label_erreur_telephone_fournisseur->setText("");
                      ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                      QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
                  }
              }

        if ( Fo.Get_Telephone_Fournisseur().length() != 8)
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_telephone_fournisseur->setText("Phone Number must be with 8");
                ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
            }
            else
            {
                ui->label_erreur_telephone_fournisseur->setText("un numéro de téléphone doit contenir 8 chiffres");
                ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
            }
        }

        if ( Fo.Get_Telephone_Fournisseur().length() == 8)
                {
                    if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
                    {
                        ui->label_erreur_telephone_fournisseur->setText("");
                        ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                        QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
                    }
                    else
                    {
                        ui->label_erreur_telephone_fournisseur->setText("");
                        ui->label_erreur_telephone_fournisseur->setVisible(!ui->label_erreur_telephone_fournisseur->isVisible());
                        QTimer::singleShot(500,this,SLOT(display_telephone_fournisseur()));
                    }
                }


     if (Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==false)
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_email_fournisseur->setText("Enter an Email adress");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
            else
            {
                ui->label_erreur_email_fournisseur->setText("Entrez une adresse mail");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
        }

     if (Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==true)
        {
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_email_fournisseur->setText("");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
            else
            {
                ui->label_erreur_email_fournisseur->setText("");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
        }

         if ( valid == false)
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_email_fournisseur->setText("Enter a valid Email adress");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
            else
            {
                ui->label_erreur_email_fournisseur->setText("Entrez une adresse mail valide ");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
        }

         if ( valid == true)
        {
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                ui->label_erreur_email_fournisseur->setText("");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
            else
            {
                ui->label_erreur_email_fournisseur->setText("");
                ui->label_erreur_email_fournisseur->setVisible(!ui->label_erreur_email_fournisseur->isVisible());
                QTimer::singleShot(500,this,SLOT(display_mail_fournisseur()));
            }
        }

     if( Fo.Verifier_INT(Fo.Get_ID_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Nom_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Adresse_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Telephone_Fournisseur())==true && Fo.Verifier_QString_Vide(Fo.Get_Email_Fournisseur())==true && valid ==true)
    {
        success->play();

        bool test=Fo.modifier_Fournisseur(ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur);

    if(test)
    {
        FF.modifier_Fournisseur_Fidele(Fo.Get_ID_Fournisseur());

        ui->tableView_Fournisseur->setModel(Fotmp.afficher_Fournisseur());
        ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());


        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/update_successful_fournisseur.png"));
        msgBox.setText("Le fournisseur a été modifié avec succés ");
        msgBox.exec();


        ui->lineEdit_IDFournisseur->clear();
        ui->lineEdit_NomFournisseur->clear();
        ui->lineEdit_Adressefournisseur->clear() ;
        ui->lineEdit_telfournisseur->clear();
        ui->lineEdit_emailfournisseur->clear();

    }
    else
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Probléme avec la modification"),
        QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}

void G_Fournisseurs::on_pushButton_ajouterfacture_clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
        click->play();

        ui->alerte->setModel(Fatmp.Alerte());

        int ID_Facture =ui->lineEdit_Id_facture->text().toInt();
        int ID_Fournisseur_Facture=ui->lineEdit_idfournisseur_facture->currentText().toInt();
        float Total_Facture =ui->lineEdit_total_facture->text().toFloat();
        int Nom_Produit_Facture=ui->ID_produit_facture->currentText().toInt();
        QDate date= ui->dateEdit_facture->date();
        QString Date_Facture= date.toString("dd/MM/yyyy");
        QString Etat_Facture= ui->lineEdit_Etatfacture->currentText();
        int Quantite_Facture= ui->lineEdit_quantite_facture->text().toInt();

        QString sDate = QDateTime::currentDateTime().toString("dd/MM/yyyy");
        QDate curdate = QDate::currentDate();

        bool pk_fac = true ;

        bool fk_fourni = true ;

        bool fk_prod = true ;

        bool valid = false;

         if((Etat_Facture == "non") || (Etat_Facture == "oui"))
        {
            valid = true;
        }

        bool testdate = false;
         if( curdate < date)
         {
            testdate = true;
         }

        QString id_fac = QString::number(ID_Facture);


        QString id_fourni = QString::number(ID_Fournisseur_Facture);
        QString id_prod = QString::number(Nom_Produit_Facture);

        Factures Fa( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,Nom_Produit_Facture, Date_Facture, Etat_Facture, Quantite_Facture);

        if( Fa.PK_Check(id_fac) != 0 )
        {
            pk_fac= false ;
        }


        if( Fa.FK_Fournisseurs_Check(id_fourni) == 0 )
        {
            fk_fourni = false ;
        }
        if( Fa.FK_Produits_Check(id_prod) == 0 )
        {
            fk_prod = false ;
        }


        if ( (Fa.Verifier_INT(Fa.Get_ID_Facture())==false ) || (pk_fac == false))
        {
            fail->play();
            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with ID"),
                QObject::tr("Check the ID .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID "),
                QObject::tr("Vérifiez l'ID saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }

        }
        else if ( Fa.Verifier_INT(Fa.Get_ID_Fournisseur_Facture())==false || (fk_fourni==false ))
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with ID of Provider"),
                QObject::tr("Check the ID of provider .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID du Fournisseur "),
                QObject::tr("Vérifiez l'ID du Fournisseur saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }


        }

        else if ( Fa.Verifier_INT(Fa.Get_Total_Facture())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Total price "),
                QObject::tr("Check the Total price .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec le total "),
                QObject::tr("Vérifiez le total saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }

        }

        else if ( ( Fa.Verifier_INT(Fa.Get_ID_Produit_Facture())==false ) || (fk_prod==false ) )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Product"),
                QObject::tr("Check the Product .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec le produit "),
                QObject::tr("Vérifiez le produit saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if ( (Fa.Verifier_QString_Vide(Fa.Get_Etat_Facture())==false ) || (valid == false) )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with State"),
                QObject::tr("Check the State .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ETAT "),
                QObject::tr("Vérifiez l'ETAT saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if ( Fa.Verifier_INT(Fa.Get_Quantite_Facture())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Quantity"),
                QObject::tr("Check the Quantity .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec la quantite "),
                QObject::tr("Vérifiez la quantite saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }
        else if(testdate==false)
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Date"),
                QObject::tr("Check the Date .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec la date "),
                QObject::tr("Vérifiez la date saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if( Fa.Verifier_INT(Fa.Get_ID_Facture())== true && Fa.Verifier_INT(Fa.Get_ID_Fournisseur_Facture())==true && Fa.Verifier_INT(Fa.Get_Total_Facture())==true && Fa.Verifier_INT(Fa.Get_ID_Produit_Facture())==true && Fa.Verifier_QString_Vide(Fa.Get_Etat_Facture())== true  && Fa.Verifier_INT(Fa.Get_Quantite_Facture())== true && testdate==true )
        {
            bool test=Fa.ajouter_Facture();



        if(test)
        {
            success->play();
            Fournisseur_Fidele Fourni ;
            Fourni.modifier_Fournisseur_Fidele(Fa.Get_ID_Fournisseur_Facture());
            ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
            ui->alerte->setModel(Fatmp.Alerte());
            ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());
            ui->total_factures_calcul->setText(QString::number(Fatmp.Calcul_Total()));


            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/add_file_icon.png"));
            msgBox.setText("La facture a été ajoutée avec succés ");
            msgBox.exec();


                    ui->lineEdit_Id_facture->clear();
                    ui->lineEdit_total_facture->clear();
                    ui->dateEdit_facture->clear();
                    ui->lineEdit_quantite_facture->clear();

        }
        else
        {
            fail->play();

            QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
            QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }


        }
}



void G_Fournisseurs::on_tableView_Fournisseur_activated(const QModelIndex &index)
{
    QString id=ui->tableView_Fournisseur->model()->data(index).toString();
    QSqlQuery qry;
     qry.prepare("SELECT * from fournisseurs where ID_Fournisseur='"+id+"' ");
     if(qry.exec())
     {
         while(qry.next())
         {
             ui->lineEdit_IDFournisseur->setText(qry.value(0).toString());
             ui->lineEdit_NomFournisseur->setText(qry.value(1).toString());
             ui->lineEdit_Adressefournisseur->setText(qry.value(2).toString());
             ui->lineEdit_telfournisseur->setText(qry.value(3).toString());
             ui->lineEdit_emailfournisseur->setText(qry.value(4).toString());
         }
     }
}



void G_Fournisseurs::on_supprimer_facture_clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
        click->play();


        Factures Fact ;
        Fact.Set_ID_Facture(ui->lineEdit_Id_facture->text().toInt());
        bool testing=Fact.Verifier_ID(Fact.Get_ID_Facture()) ;
        if(testing)
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this,
         "Suppression en cours ", "Etes vous sur de supprimer ! ",
         QMessageBox::Yes | QMessageBox::No);
          if(reply == QMessageBox::Yes)
           {
            success->play();

            Fact.supprimer_Facture(Fact.Get_ID_Facture());

            Fournisseur_Fidele Fourni ;
            Fourni.modifier_Fournisseur_Fidele_decrement(Fact.Get_ID_Fournisseur_Facture());
            ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
            ui->alerte->setModel(Fatmp.Alerte());
            ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());
            ui->total_factures_calcul->setText(QString::number(Fatmp.Calcul_Total()));

            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/file_delete_icon.png"));
            msgBox.setText("La facture a été supprimée avec succés ");
            msgBox.exec();

            ui->lineEdit_Id_facture->clear();
            ui->lineEdit_total_facture->clear();
            ui->dateEdit_facture->clear();
            ui->lineEdit_quantite_facture->clear();
        }
          else
           {
           QMessageBox::information(nullptr, QObject::tr("Suppression"),
           QObject::tr("Suppression non effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);

           }
       }
        else
        {
            fail->play();

            QMessageBox::critical(nullptr, QObject::tr("Attention ! "),
            QObject::tr("Vérifiez l'ID .\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void G_Fournisseurs::on_tableView_Facture_activated(const QModelIndex &index)
{
    QString id=ui->tableView_Facture->model()->data(index).toString();
    QSqlQuery qry;
     qry.prepare("SELECT * from factures where ID_Facture='"+id+"' ");
     if(qry.exec())
     {
         while(qry.next())
         {
             ui->lineEdit_Id_facture->setText(qry.value(0).toString());
             ui->lineEdit_idfournisseur_facture->setCurrentText(qry.value(1).toString());
             ui->lineEdit_total_facture->setText(qry.value(2).toString());
             ui->ID_produit_facture->setCurrentText(qry.value(3).toString());
             ui->dateEdit_facture->setDate(qry.value(4).toDate());
             ui->lineEdit_Etatfacture->setCurrentText(qry.value(5).toString());
             ui->lineEdit_quantite_facture->setText(qry.value(6).toString());
         }
     }
}


void G_Fournisseurs::on_modifier_facture_clicked() // produit
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    int ID_Produit =ui->lineEdit_idproduit->text().toInt();
    QString Nom_Produit=ui->lineEdit_nomproduit->text();
    int Quantite_Produit =ui->lineEdit_quantiteproduit->text().toInt();
    float Prix_Produit=ui->lineEdit_prixproduit->text().toFloat();


    bool pk_prod = true ;
    QString id_prod = QString::number(ID_Produit);

    Produits P(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit);
    if( P.PK_Check(id_prod) == 0 )
            {
                pk_prod= false ;
            }

    if ( P.Verifier_Int(P.Get_ID_Produit())==false || pk_prod == false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID "),
        QObject::tr("Vérifiez l'ID saisi .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ( P.Verifier_QString_Vide(P.Get_Nom_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec le NOM "),
        QObject::tr("Vérifiez le NOM saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if ( P.Verifier_Int(P.Get_Quantite_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec la QUANTITE "),
        QObject::tr("Vérifiez la QUANTITE saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if ( P.Verifier_Int(P.Get_Prix_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec le PRIX  "),
        QObject::tr("Vérifiez le PRIX saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if( P.Verifier_Int(P.Get_ID_Produit())==true && P.Verifier_QString_Vide(P.Get_Nom_Produit())==true && P.Verifier_Int(P.Get_Quantite_Produit())==true && P.Verifier_Int(P.Get_Prix_Produit())== true )
    {
        bool test=P.modifier_Produit(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit );

    if(test)
    {
        success->play();

        ui->tableView_Produit_G_fournisseurs->setModel(Ptmp.afficher_Produit());

        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/update_icon_produit.png"));
        msgBox.setText("Le produit a été modifié avec succés ");
        msgBox.exec();

        ui->lineEdit_idproduit->clear();
        ui->lineEdit_nomproduit->clear();
        ui->lineEdit_quantiteproduit->clear();
        ui->lineEdit_prixproduit->clear();
    }
    else
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Probléme avec la modification"),
        QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}

void G_Fournisseurs::on_supprimer_facture_2_clicked() // supprimer produit
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    Produits P ;
    P.Set_iD_Produit(ui->lineEdit_idproduit->text().toInt());
    bool testing=P.Verifier_ID(P.Get_ID_Produit()) ;
    if(testing)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
     "Suppression en cours ", "Etes vous sur de supprimer ! ",
     QMessageBox::Yes | QMessageBox::No);
      if(reply == QMessageBox::Yes)
       {
        success->play();

        P.supprimer_Produit(P.Get_ID_Produit());
        ui->ID_produit_facture->clear();
        ui->ID_produit_facture->addItems(Ptmp.listeProduits());
        ui->tableView_Produit_G_fournisseurs->setModel(Ptmp.afficher_Produit());
        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/delete_produit.png"));
        msgBox.setText("Le produit a été supprimé avec succés ");
        msgBox.exec();

        ui->lineEdit_idproduit->clear();
        ui->lineEdit_nomproduit->clear();
        ui->lineEdit_quantiteproduit->clear();
        ui->lineEdit_prixproduit->clear();
    }
      else
       {
       QMessageBox::information(nullptr, QObject::tr("Suppression"),
       QObject::tr("Suppression non effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);

       }
    }
    else
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("OK"),
        QObject::tr("Vérifiez l'ID .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void G_Fournisseurs::on_imprimer_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();


    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView_Facture->model()->rowCount();
                  const int columnCount = ui->tableView_Facture->model()->columnCount();
                  QString TT = QDate::currentDate().toString("dd/MM/yyyy");
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title> Factures LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#F4B8B8 link=#5000A0>\n"
                      "<h1 style=\"text-align: center;\"><strong> ******LISTE DES Factures ****** </strong></h1>"
                      "<img style=\"float: right;\" src='C:/Users/lenovo/Desktop/G_Fournisseurs/logo.png' height='42' width='120'/>"
                      "<h4 style=\"text-align: left; font-size: 10px;\"><strong> "+TT+"</strong></h4>"
                      "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#d6e5ff>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView_Facture->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView_Facture->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView_Facture->isColumnHidden(column)) {
                              QString data =ui->tableView_Facture->model()->data(ui->tableView_Facture->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
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

                  success->play();
}

void G_Fournisseurs::on_recherche_produit_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    Produits P;
        QString text;
        if (ui->id_produit->isChecked()==true)
    {
    text=ui->recherche_produits_2->text();
         if(text == "")
         {
             ui->tableView_Produit_G_fournisseurs->setModel(P.afficher_Produit());
             QMessageBox::information(nullptr, QObject::tr("Recherche des produits"),QObject::tr("Aucun id saisi .\n"
             "Click OK to exit."), QMessageBox::Ok);
         }
         else
         {
             ui->tableView_Produit_G_fournisseurs->setModel(P.Recherche_ID(text));
         }
        }
         if(ui->nom_produit->isChecked()==true)
        {
            text=ui->recherche_produits_2->text();
                 if(text == "")
                 {
                     ui->tableView_Produit_G_fournisseurs->setModel(P.afficher_Produit());
                     QMessageBox::information(nullptr, QObject::tr("Recherche des produits"),QObject::tr("Aucun nom saisi .\n"
                     "Click OK to exit."), QMessageBox::Ok);
                 }
                 else
                 {
                     ui->tableView_Produit_G_fournisseurs->setModel(P.Recherche_Nom(text));
                 }

        }
         else if     (ui->Quantite_produit->isChecked()==true)
         {

             text=ui->recherche_produits_2->text();
                  if(text == "")
                  {
                      ui->tableView_Produit_G_fournisseurs->setModel(P.afficher_Produit());
                      QMessageBox::information(nullptr, QObject::tr("Recherche des produits"),QObject::tr("Aucune quantite saisie .\n"
                      "Click OK to exit."), QMessageBox::Ok);
                  }
                  else
                  {
                      ui->tableView_Produit_G_fournisseurs->setModel(P.Recherche_Quantite(text));
                  }
         }
         else if     (ui->prix_Produit->isChecked()==true)
         {

             text=ui->recherche_produits_2->text();
                  if(text == "")
                  {
                      ui->tableView_Produit_G_fournisseurs->setModel(P.afficher_Produit());
                      QMessageBox::information(nullptr, QObject::tr("Recherche des produits"),QObject::tr("Aucun prix saisi .\n"
                      "Click OK to exit."), QMessageBox::Ok);
                  }
                  else
                  {
                      ui->tableView_Produit_G_fournisseurs->setModel(P.Recherche_Prix(text));
                  }
         }
}


void G_Fournisseurs::on_statistiques_factures_clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    success->play();

    statistics *s= new statistics();
    s->show();
}
void G_Fournisseurs::on_chercher_produitss_clicked()
{
    QString ID_Produit =ui->lineEdit_idproduit->text();
    QSqlQuery query;
    query.first();
    query.prepare("SELECT * from produits where ID_Produit='"+ID_Produit+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_idproduit->setText(query.value(0).toString());
            ui->lineEdit_nomproduit->setText(query.value(1).toString());
            ui->lineEdit_quantiteproduit->setText(query.value(2).toString());
            ui->lineEdit_prixproduit->setText(query.value(3).toString());
        }
    }

    else
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Chercher Produit!"),
                              QObject::tr("Erreur!.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void G_Fournisseurs::on_chercherboutonfacture_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();


    QString ID_Facture =ui->lineEdit_Id_facture->text();
    QSqlQuery query;
    query.first();
    query.prepare("SELECT * from factures where ID_Facture='"+ID_Facture+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_Id_facture->setText(query.value(0).toString());
            ui->lineEdit_idfournisseur_facture->setCurrentText(query.value(1).toString());
            ui->lineEdit_total_facture->setText(query.value(2).toString());
            ui->ID_produit_facture->setCurrentText(query.value(3).toString());
            ui->dateEdit_facture->setDate(query.value(4).toDate());
            ui->lineEdit_Etatfacture->setCurrentText(query.value(5).toString());
            ui->lineEdit_quantite_facture->setText(query.value(6).toString());
        }
    }

    else
    {
        fail->play();
        QMessageBox::critical(nullptr, QObject::tr("Chercher facture!"),
                              QObject::tr("Erreur!.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void G_Fournisseurs::on_chercher_fournisseur__clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    QString ID_Fournisseur =ui->lineEdit_IDFournisseur->text();
    QSqlQuery query;
    query.first();
    query.prepare("SELECT * from fournisseurs where ID_Fournisseur='"+ID_Fournisseur+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_IDFournisseur->setText(query.value(0).toString());
            ui->lineEdit_NomFournisseur->setText(query.value(1).toString());
            ui->lineEdit_Adressefournisseur->setText(query.value(2).toString());
            ui->lineEdit_telfournisseur->setText(query.value(3).toString());
            ui->lineEdit_emailfournisseur->setText(query.value(4).toString());
        }
    }

    else
    {
        fail->play();
        QMessageBox::critical(nullptr, QObject::tr("Chercher fournisseur!"),
                              QObject::tr("Erreur!.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void G_Fournisseurs::on_recherche_produits_textChanged()
{
    ui->tableView_Produit_G_fournisseurs->setModel(Ptmp.Recherche_ID(ui->recherche_produits->text()));
}


void G_Fournisseurs::on_verifier_etat_clicked()
{
    QString id=ui->lineEdit_Id_facture->text();
    QString Etat_Facture= ui->lineEdit_Etatfacture->currentText();

        if (id=="")
        {
            QMessageBox::information(nullptr, QObject::tr("Selectionner une facture "),
                        QObject::tr("Selectionner une facture \n"), QMessageBox::Ok);
        }
        else if(Etat_Facture=="oui")
        {
            A.write_to_arduino(("1"));
        }
        else if(Etat_Facture=="non")
        {
            A.write_to_arduino(("0"));
        }

}

void G_Fournisseurs::on_calendar_button_fournisseur_clicked()
{
    Calendar_G_fournisseurs= new Calendar_G_fournisseur() ;
    Calendar_G_fournisseurs->show();
}

void G_Fournisseurs::on_calcul_fournisseurs_clicked()
{
    calculator_G_Fourniss = new calculator_G_Fournisseurs() ;
    calculator_G_Fourniss->show();
}

void G_Fournisseurs::on_puzzle_G_fournisseurs_clicked()
{
    Puzzle_G_fournisseurs = new Puzzle_Main_Window_G_fournisseurs() ;
    Puzzle_G_fournisseurs->show();
}

void G_Fournisseurs::on_paint_g_fournisseurs_clicked()
{
    paint_fournisseurs = new Paint_G_fournisseurs() ;
    paint_fournisseurs->show();
}

void G_Fournisseurs::on_modifier_facture_fournisseurs_clicked()
{

    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
        click->play();

        ui->alerte->setModel(Fatmp.Alerte());

        int ID_Facture =ui->lineEdit_Id_facture->text().toInt();
        int ID_Fournisseur_Facture=ui->lineEdit_idfournisseur_facture->currentText().toInt();
        float Total_Facture =ui->lineEdit_total_facture->text().toFloat();
        int ID_Produit_Facture=ui->ID_produit_facture->currentText().toInt();
        QDate date= ui->dateEdit_facture->date();
        QString Date_Facture= date.toString("dd/MM/yyyy");
        QString Etat_Facture= ui->lineEdit_Etatfacture->currentText();
        int Quantite_Facture= ui->lineEdit_quantite_facture->text().toInt();

        bool pk_fac = true ;
        bool fk_fourni = true ;
        bool fk_prod = true ;
        QString id_fourni = QString::number(ID_Fournisseur_Facture);
        QString id_prod = QString::number(ID_Produit_Facture);

        QString sDate = QDateTime::currentDateTime().toString("dd/MM/yyyy");
        QDate curdate = QDate::currentDate();


        QString id_fac = QString::number(ID_Facture);
        Factures Fa( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,ID_Produit_Facture, Date_Facture, Etat_Facture, Quantite_Facture);
        if( Fa.PK_Check(id_fac) == 0 )
            {
                pk_fac= false ;
            }
        if( Fa.FK_Fournisseurs_Check(id_fourni) == 0 )
        {
            fk_fourni = false ;
        }
        if( Fa.FK_Produits_Check(id_prod) == 0 )
        {
            fk_prod = false ;
        }

        bool testdate = false;
                 if( curdate < date)
                 {
                    testdate = true;
                 }


        if ( Fa.Verifier_INT(Fa.Get_ID_Facture())==false || pk_fac == false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with ID"),
                QObject::tr("Check the ID .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID "),
                QObject::tr("Vérifiez l'ID saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }
        else if ( Fa.Verifier_INT(Fa.Get_ID_Fournisseur_Facture())==false  || fk_fourni == false)
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with ID of Provider"),
                QObject::tr("Check the ID of provider .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID du Fournisseur "),
                QObject::tr("Vérifiez l'ID du Fournisseur saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }


        }

        else if(testdate==false)
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Date"),
                QObject::tr("Check the Date .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec la date "),
                QObject::tr("Vérifiez la date saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if ( Fa.Verifier_INT(Fa.Get_Total_Facture())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Total price "),
                QObject::tr("Check the Total price .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec le total "),
                QObject::tr("Vérifiez le total saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }

        }

        else if ( Fa.Verifier_INT(Fa.Get_ID_Produit_Facture())==false || fk_prod == false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Product"),
                QObject::tr("Check the Product .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec le produit "),
                QObject::tr("Vérifiez le produit saisi .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if ( Fa.Verifier_QString_Vide(Fa.Get_Etat_Facture())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with State"),
                QObject::tr("Check the State .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ETAT "),
                QObject::tr("Vérifiez l'ETAT saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if ( Fa.Verifier_INT(Fa.Get_Quantite_Facture())==false )
        {
            fail->play();

            if(ui->trad_ENG_G_Fournisseur->isChecked()==true)
            {
                QMessageBox::critical(nullptr, QObject::tr("Problem with Quantity"),
                QObject::tr("Check the Quantity .\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Un probléme avec la quantite "),
                QObject::tr("Vérifiez la quantite saisie .\n" "Appuyé sur Cancel pour quitter."), QMessageBox::Cancel);
            }
        }

        else if( Fa.Verifier_INT(Fa.Get_ID_Facture())== true && Fa.Verifier_INT(Fa.Get_ID_Fournisseur_Facture())==true && Fa.Verifier_INT(Fa.Get_Total_Facture())==true && Fa.Verifier_INT(Fa.Get_ID_Produit_Facture())==true && Fa.Verifier_QString_Vide(Fa.Get_Etat_Facture())== true  && Fa.Verifier_INT(Fa.Get_Quantite_Facture())== true && testdate == true )
        {
            bool test=Fa.modifier_Facture( ID_Facture, ID_Fournisseur_Facture, Total_Facture ,ID_Produit_Facture, Date_Facture, Etat_Facture, Quantite_Facture);

        if(test)
        {
            success->play();
            FF.modifier_Fournisseur_Fidele(Fa.Get_ID_Fournisseur_Facture());
            ui->tableView_Facture->setModel(Fatmp.afficher_Facture());
            ui->alerte->setModel(Fatmp.Alerte());
            ui->tableView_2->setModel(FF.afficher_Fournisseur_Fidele());
            ui->total_factures_calcul->setText(QString::number(Fatmp.Calcul_Total()));


            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/update_icon_facture.png"));
            msgBox.setText("La facture a été modifiée avec succés ");
            msgBox.exec();

            ui->lineEdit_Id_facture->clear();
            ui->lineEdit_total_facture->clear();
            ui->dateEdit_facture->clear();
            ui->lineEdit_quantite_facture->clear();
        }
        else
        {
            fail->play();

            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Modification non effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        }


}

void G_Fournisseurs::on_ajouter_produit_fournisseur_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    int ID_Produit =ui->lineEdit_idproduit->text().toInt();
    QString Nom_Produit=ui->lineEdit_nomproduit->text();
    int Quantite_Produit =ui->lineEdit_quantiteproduit->text().toInt();
    float Prix_Produit=ui->lineEdit_prixproduit->text().toFloat();

    bool pk_prod = true ;
    QString id_prod = QString::number(ID_Produit);
    Produits P(ID_Produit , Nom_Produit , Quantite_Produit , Prix_Produit);
    if( P.PK_Check(id_prod) != 0 )
        {
            pk_prod= false ;
        }

    if ( P.Verifier_Int(P.Get_ID_Produit())==false || pk_prod == false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Un probléme avec l'ID "),
        QObject::tr("Vérifiez l'ID saisi .\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ( P.Verifier_QString_Vide(P.Get_Nom_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec le NOM "),
        QObject::tr("Vérifiez le NOM saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if ( P.Verifier_Int(P.Get_Quantite_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec la QUANTITE "),
        QObject::tr("Vérifiez la QUANTITE saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if ( P.Verifier_Int(P.Get_Prix_Produit())==false )
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr(" Un probléme avec le PRIX  "),
        QObject::tr("Vérifiez le PRIX saisi.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if( P.Verifier_Int(P.Get_ID_Produit())==true && P.Verifier_QString_Vide(P.Get_Nom_Produit())==true && P.Verifier_Int(P.Get_Quantite_Produit())==true && P.Verifier_Int(P.Get_Prix_Produit())== true )
    {
        bool test=P.ajouter_Produit();

    if(test)
    {
        success->play();

        ui->tableView_Produit_G_fournisseurs->setModel(Ptmp.afficher_Produit());

        ui->ID_produit_facture->clear();
        ui->ID_produit_facture->addItems(Ptmp.listeProduits());

        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap("C:/Users/lenovo/Desktop/G_Fournisseurs/G_Fournisseurs_Images_/update_icon_produit.png"));
        msgBox.setText("Le produit a été ajouté avec succés ");
        msgBox.exec();

                ui->lineEdit_idproduit->clear();
                ui->lineEdit_nomproduit->clear();
                ui->lineEdit_quantiteproduit->clear();
                ui->lineEdit_prixproduit->clear();
    }
    else
    {
        fail->play();

        QMessageBox::critical(nullptr, QObject::tr("Erreur ! "),
        QObject::tr("Ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}



void G_Fournisseurs::on_notepad_g_fournisseur_clicked()
{
    notepad= new Notepad(this) ;
    notepad->show();
}

void G_Fournisseurs::on_excel_g_fournisseurs_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tableView_Fournisseur);


            obj.addField(0, "ID_Fournisseur", "char(20)");
            obj.addField(1, "Nom_Fournisseur", "char(20)");
            obj.addField(2, "Adresse_Fournisseur", "char(20)");
            obj.addField(3, "Telephone_Fournisseur", "char(20)");
            obj.addField(4, "Email_Fournisseur", "char(20)");


            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                success->play();
                QMessageBox::information(this, tr("Exportation réussie!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }
}

void G_Fournisseurs::on_tableView_Produit_G_fournisseurs_activated(const QModelIndex &index)
{
    QString id=ui->tableView_Produit_G_fournisseurs->model()->data(index).toString();
    QSqlQuery qry;
     qry.prepare("SELECT * from produits where ID_Produit='"+id+"' ");
     if(qry.exec())
     {
         while(qry.next())
         {
             ui->lineEdit_idproduit->setText(qry.value(0).toString());
             ui->lineEdit_nomproduit->setText(qry.value(1).toString());
             ui->lineEdit_quantiteproduit->setText(qry.value(2).toString());
             ui->lineEdit_prixproduit->setText(qry.value(3).toString());
         }
     }
}


void G_Fournisseurs::on_recherche_tab_facture_textChanged()
{
    ui->tableView_Facture->setModel(Fatmp.Recherche(ui->recherche_tab_facture->text()));
}

void G_Fournisseurs::on_recherche_tab_fournisseurs_textChanged()
{
    ui->tableView_Fournisseur->setModel(Fotmp.Recherche(ui->recherche_tab_fournisseurs->text()));
}

void G_Fournisseurs::on_comboBox_factures_fournisseurs_activated(const QString &arg1)
{
    ui->tableView_Facture->setModel(Fatmp.Trier(arg1));

}

void G_Fournisseurs::on_comboBox_g_fournisseurs_activated(const QString &arg1)
{
    ui->tableView_Fournisseur->setModel(Fotmp.Trier(arg1));

}

void G_Fournisseurs::on_pdf_g_fournisseur_clicked()
{
    click->setMedia(QUrl("qrc:/sounds/click.mp3"));
    click->play();

    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView_Facture->model()->rowCount();
                  const int columnCount = ui->tableView_Facture->model()->columnCount();
                  QString TT = QDate::currentDate().toString("dd/MM/yyyy");
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title> Factures LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#F4B8B8 link=#5000A0>\n"
                      "<h1 style=\"text-align: center;\"><strong> ******LISTE DES Factures ****** </strong></h1>"
                      "<img style=\"float: right;\" src='C:/Users/lenovo/Desktop/G_Fournisseurs/logo.png' height='42' width='120'/>"
                      "<h4 style=\"text-align: left; font-size: 10px;\"><strong> "+TT+"</strong></h4>"
                      "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                        "</br> </br>";


                  // headers
                  out << "<thead><tr bgcolor=#d6e5ff>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView_Facture->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView_Facture->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView_Facture->isColumnHidden(column)) {
                              QString data =ui->tableView_Facture->model()->data(ui->tableView_Facture->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";


                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size());
                    doc.print(&printer);

                    success->play();
}
