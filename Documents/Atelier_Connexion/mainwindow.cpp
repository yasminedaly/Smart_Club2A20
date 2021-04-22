#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "evenement.h"
#include <QSqlQuery>
#include <QIntValidator>
#include "ticket.h"
#include "stats.h"
#include <QString>
#include <QWidget>
#include <QPainter>
#include <QPdfWriter>
#include <QApplication>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QUrl>
#include <QDebug>
#include <QTextBrowser>
#include <QFileDialog>
#include <QTextBlock>
#include <cstdlib>
#include <QDate>
#include<iostream>
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include <QtPrintSupport/QPrintDialog>
#include <QDesktopServices>
#include "tableprinter.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include<QDebug>
#include<QValidator>
#include "accueil.h"
#include <QPropertyAnimation>



//PDF
class PrintBorder : public PagePrepare {
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter) { // print a border on each page
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
     ui->tableView_2->setModel(Etmpp.afficher());
     QIntValidator * intvalid=new QIntValidator(1,99999999);
     ui->le_id->setValidator(intvalid);
     ui->le_id_2->setValidator(intvalid);
     ui->le_prix->setValidator(intvalid);
     ui->le_nb->setValidator(intvalid);
     ui->le_num->setValidator(intvalid);

     ui->le_id_4->clear();
     ui->le_id_4->addItems(Etmp.listeEvents());

     //animation button pdf
     // Создадим группу анимации
     animationGroup = new QSequentialAnimationGroup(this);

     // Создадим анимацию свойства передвижения слева-сверху направо-сверху
     QPropertyAnimation* leftTopToRightTop = new QPropertyAnimation(ui->PDF, "geometry");
     leftTopToRightTop->setDuration(1000); // Длительность анимации
     leftTopToRightTop->setStartValue(ui->PDF->geometry()); // Стартовая позиция и геометрия анимации
     leftTopToRightTop->setEndValue(ui->PDF->geometry().translated(100, 0)); // Конечная позиция и геометрия анимации
     animationGroup->addAnimation(leftTopToRightTop); // Добавим анимацию в группу

     // Справа-сверху вниз-справа
     QPropertyAnimation* rightTopToRightBottom = new QPropertyAnimation(ui->PDF, "geometry");
     rightTopToRightBottom->setDuration(1000);
     rightTopToRightBottom->setStartValue(leftTopToRightTop->endValue());
     rightTopToRightBottom->setEndValue(leftTopToRightTop->endValue().toRect().translated(0, 100));
     animationGroup->addAnimation(rightTopToRightBottom);

     // Снизу-справа налево-вниз
     QPropertyAnimation* rightBottomToLeftBottom = new QPropertyAnimation(ui->PDF, "geometry");
     rightBottomToLeftBottom->setDuration(1000);
     rightBottomToLeftBottom->setStartValue(rightTopToRightBottom->endValue());
     rightBottomToLeftBottom->setEndValue(rightTopToRightBottom->endValue().toRect().translated(-100, 0));
     animationGroup->addAnimation(rightBottomToLeftBottom);

     // Слева-снизу наверх-слева
     QPropertyAnimation* leftBottomToLeftTop = new QPropertyAnimation(ui->PDF, "geometry");
     leftBottomToLeftTop->setDuration(1000);
     leftBottomToLeftTop->setStartValue(rightBottomToLeftBottom->endValue());
     leftBottomToLeftTop->setEndValue(rightBottomToLeftBottom->endValue().toRect().translated(0, -100));
     animationGroup->addAnimation(leftBottomToLeftTop);

     // Подключаем нажатие кнопки к слоту обработчику кнопки
     connect(ui->PDF, &QPushButton::clicked, this, &MainWindow::on_PDF_clicked);

     // fekher
    /* animation = new QPropertyAnimation (ui ->tabevenement,"geometry" );
                    // animation = new QPropertyAnimation (ui ->text_2,"geometry" );
                     animation->setDuration(10000) ;
                     animation->setStartValue(ui->label_12->geometry());
                     animation->setEndValue(QRect(1,20,30,40)) ;
                     animation->start() ;

                     // animation2 = new QPropertyAnimation (ui ->text,"geometry" );
                         animation2 = new QPropertyAnimation (ui ->tabevenement,"geometry" );
                         animation2->setDuration(10000) ;
                         animation2->setStartValue(ui->label_11->geometry());
                         animation2->setEndValue(QRect(1,20,30,40)) ;
                         animation2->start() ;
                          ui->tableView->setModel(Etmp.afficher());
                        // ui->tableView->setModel(tmpc.afficher_client());*/




// STATISTIQUE
     statrefresh();



}

//

MainWindow::~MainWindow()
{
    delete ui;
}


// AJOUT EVENT // CURRENTDATE

void MainWindow::on_ajouter_2_clicked()
{
QSound::play(":/new/prefix1/sond/Click button.wav");
    int id=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString adresse=ui->le_adresse->text();
     int num=ui->le_num->text().toInt();
     int nb=ui->le_nb->text().toInt();
     QDate date=ui->le_date->date();
     if(date>=QDate().currentDate()){
         Evenement E(id,nom,adresse,num,nb,date) ;

          bool test=E.ajouter();

          if (test)

          {
              ui->tableView->setModel(Etmp.afficher());
              trayIcon = new QSystemTrayIcon(this);
              trayIcon->setVisible(true);
              trayIcon->setIcon(QIcon("C:/Users/DeLL/Desktop/iconn.jpg"));
                   trayIcon->setToolTip("Ajouter" "\n"
                                   "Ajouter avec sucées");
              trayIcon->show();

              /* Also connect clicking on the icon to the signal processor of this press
               * */
              connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                      this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

             n.Alerte_Ajout(id,1);

      }
          else
              n.Alerte_Ajout(id,0);
     }
     else{
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
                     QObject::tr("Date n'est pas valide.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }

     ui->le_id_4->clear();
     ui->le_id_4->addItems(Etmp.listeEvents());



    }

// SUPPRISSION EVENT

void MainWindow::on_supp_event_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    int id=ui->le_id->text().toInt();
    bool test=Etmp.supprimer(id);

    if (test)

    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    }
// MODIFIER EVENT

void MainWindow::on_ajouter_3_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    int id=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString adresse=ui->le_adresse->text();
     int num=ui->le_num->text().toInt();
     int nb=ui->le_nb->text().toInt();
     QDate date=ui->le_date->date();

   Evenement E (id,nom,adresse,num,nb,date) ;

    bool test=E.modifier(id,nom,adresse,num,nb,date);
    if (test)

    {
        ui->le_adresse->setText("");
        ui->le_nom->setText("");
        ui->le_nb->setText("");
        ui->le_num->setText("");
        ui->le_date->setDate(QDate(2021,01,01));
        ui->le_id->setText("");
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Modification effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    ui->le_id_4->clear();
    ui->le_id_4->addItems(Etmp.listeEvents());



}
//RECHERCHE EVENT
void MainWindow::on_rechercher_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    //click->play();


            QString text;

            text=ui->le_nom_2->text();

            if(text == "")

            {

                ui->tableView->setModel(Etmp.afficher());

            }

            else

            {



                ui->tableView->setModel(Etmp.recherche(text));

            }
}
//TRIE EVENT
void MainWindow::on_trie_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    ui->tableView->setModel( Etmp.afficher_trie());
}

// PDF
void MainWindow::on_PDF_clicked()
{

    animationGroup->start();
 QSound::play(":/new/prefix1/sond/Click button.wav");
 // QSound::play(":/new/prefix1/sond/632.wav");

    QString strStream;
               QTextStream out(&strStream);
               const int rowCount = ui->tableView->model()->rowCount();
               const int columnCount =ui->tableView->model()->columnCount();

               out <<  "<html>\n"
                       "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                       <<  QString("<title>%1</title>\n").arg("eleve")
                       <<  "</head>\n"
                       "<body bgcolor=#F4B8B8 link=#5000A0>\n"
                          // "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='20' height='20'>\n"
                           "<img src='C:/Users/DeLL/Desktop/logooo.png' width='100' height='100'>\n"
                           "<h1>   Liste des evenements </h1>"
                            "<h1>  </h1>"

                           "<table border=1 cellspacing=0 cellpadding=2>\n";


               // headers
                   out << "<thead><tr bgcolor=#f0f0f0>";
                   for (int column = 0; column < columnCount; column++)
                       if (!ui->tableView->isColumnHidden(column))
                           out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                   out << "</tr></thead>\n";
                   // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++) {
                              if (!ui->tableView->isColumnHidden(column)) {
                                  QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

                      QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                      if (dialog->exec() == QDialog::Accepted) {
                          document->print(&printer);
                   }
}



void MainWindow::print(QPrinter *printer)
{
    QPainter painter;
        if(!painter.begin(printer)) {
            qWarning() << "can't start printer";
            return;
        }
        // print table
        TablePrinter tablePrinter(&painter, printer);
        QVector<int> columnStretch = QVector<int>() << 10 << 15 << 20  <<25;
        if(!tablePrinter.printTable(ui->tableView->model(), columnStretch)) {
            qDebug() << tablePrinter.lastError();
        }
        // print second table
        painter.translate(0, 100);
        if(!tablePrinter.printTable(ui->tableView->model(), columnStretch)) {
            qDebug() << tablePrinter.lastError();
        }
        painter.end();
}

                     // AJOUT Ticket

void MainWindow::on_ajouter_clicked()
{
QSound::play(":/new/prefix1/sond/Click button.wav");
    int id_ticket=ui->le_id_2->text().toInt();

    int id_evenement=ui->le_id_4->currentText().toInt();

     QString type_acheteur=ui->le_type_1->currentText();
     QString type=ui->le_type_2->currentText();
     int prix=ui->le_prix->text().toInt();

   Ticket T(id_ticket,id_evenement,type_acheteur,type,prix,QDate().currentDate()) ;

    bool test=T.ajouter();

    QStringList l=Etmp.listeEvents();
   for (int i = 0; i < l.size(); ++i){

       int cc=Etmpp.calculeTicket(l[i].toInt());
   }

    if (test)

    {
        ui->tableView_2->setModel(Etmpp.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->le_adresse->setText("");
        ui->le_nom->setText("");
        ui->le_nb->setText("");
        ui->le_num->setText("");
        ui->le_date->setDate(QDate(2020,01,01));
        ui->le_id->setText("");


}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
// SUPP TICKET

void MainWindow::on_supp_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");

    int id_ticket=ui->le_id_2->text().toInt();
    bool test=Etmpp.supprimer(id_ticket);

    if (test)

    {
        ui->tableView_2->setModel(Etmpp.afficher());
       // ui->statistiques->setLayout(mainLayout);

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

// RECHERCHE TICKET
void MainWindow::on_recherche_Ticket_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
            QString text;

            text=ui->le_type_3->text();

            if(text == "")

            {

                ui->tableView_2->setModel(Etmpp.afficher());
            }

            else

            {



                ui->tableView_2->setModel(Etmpp.recherche(text));

            }
}



// MODIFIER TICKET

void MainWindow::on_Modifier_Ticket_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    int id_ticket=ui->le_id_2->text().toInt();
    int id_evenement=ui->le_id_4->currentText().toInt();
     QString type_acheteur=ui->le_type_1->currentText();
     QString type=ui->le_type_2->currentText();
     int prix=ui->le_prix->text().toInt();


   Ticket T(id_ticket,id_evenement,type_acheteur,type,prix,QDate().currentDate()) ;

       bool test=T.modifier_Ticket (id_ticket,id_evenement,type_acheteur,type,prix,QDate().currentDate()) ;
       QStringList l=Etmp.listeEvents();
      for (int i = 0; i < l.size(); ++i){

          int cc=Etmpp.calculeTicket(l[i].toInt());
      }

       // cc=true;
        //cc=Etmpp.calculeTicket(l[i].toInt()));


       if(test)
       {
           //ui->le_id_4->setText("");
          // ui->le_type_1->setText("");
           //ui->le_type_2->setText("");
           ui->le_prix->setText("");
           ui->tableView_2->setModel(Etmpp.afficher());
           QMessageBox::information(nullptr, QObject::tr("OK"),
           QObject::tr("Modification effectuée .\n" "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
           QObject::tr("Modification non effectuée.\n" "Click Cancel to exit."), QMessageBox::Cancel);
       }
}


//

void MainWindow::on_le_id_textChanged(const QString &arg1)
{
    Evenement e;
    e=e.getEvenement(ui->le_id->text().toInt());
    if(e.getid()!=0){
        qDebug()<<e.getadresse();
        ui->le_adresse->setText(e.getadresse());
        ui->le_nom->setText(e.getnom());
        ui->le_nb->setText(QString::number(e.getnb()));
        ui->le_num->setText(QString::number(e.getnum()));
        ui->le_date->setDate(e.getdate());
    }
    else{
        ui->le_adresse->setText("");
        ui->le_nom->setText("");
        ui->le_nb->setText("");
        ui->le_num->setText("");
        ui->le_date->setDate(QDate(2020,01,01));
    }

}




void MainWindow::on_le_id_2_textChanged(const QString &arg1)
{
    Ticket T;
    T=T.getTicket(ui->le_id_2->text().toInt());
    if(T.getid_ticket()!=0){
        qDebug()<<T.getid_evenement();

        ui->le_prix->setText(QString::number(T.getprix()));

    }
    else{

        ui->le_prix->setText("");
    }
}

void MainWindow::on_tabevenement_currentChanged(int index)
{QSound::play(":/new/prefix1/sond/Click button.wav");
    ui->le_id_4->clear();
    ui->le_id_4->addItems(Etmp.listeEvents());
    QStringList l1={"spectateur","joueur","abonné"};
    ui->le_type_1->clear();
    ui->le_type_1->addItems(l1);
    QStringList l2={"loge","1er rang","chaise"};
    ui->le_type_2->clear();
    ui->le_type_2->addItems(l2);

    // STAT
    statrefresh();

}

void MainWindow::on_trier_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    ui->tableView->setModel(Etmp.afficher_trie());

}

void MainWindow::on_trie_2_clicked()
{QSound::play(":/new/prefix1/sond/Click button.wav");
     ui->tableView_2->setModel(Etmpp.afficher_trie());
}

void MainWindow::sendMail()
{QSound::play(":/new/prefix1/sond/Click button.wav");
    Smtp* smtp = new Smtp("yosra.mekaoui@esprit.tn", "191JFT4305", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("yosra.mekaoui@esprit.tn", ui->email->text() , ui->objet->text(),ui->message->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::statrefresh(){
    // STATISTIQUE

         QPieSeries *series=new QPieSeries();
         QStringList l=Etmp.listeEvents();
        for (int i = 0; i < l.size(); ++i){

            series->append("Evenement num :"+l[i] ,Etmpp.calculeTicket(l[i].toInt()));
        }


         QPieSlice *slice1=series->slices().at(1);
         slice1->setExploded(true);

         QChart *chart =new QChart();
         chart->addSeries(series);
         chart->setTitle("statistiques");
         chart->setAnimationOptions(QChart::AllAnimations);

         QChartView *chartview=new QChartView(chart);

         QGridLayout *mainLayout=new QGridLayout();
         mainLayout->addWidget(chartview,0,0);
         ui->statistiques->setLayout(mainLayout);

}
void MainWindow::on_envoyer_clicked()
{
    sendMail();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    int val=ui->tableView->model()->data(index).toInt();
    qDebug()<<val;
    Evenement e;
    e=e.getEvenement(val);
    if(e.getid()!=0){
        qDebug()<<e.getadresse();
        ui->le_adresse->setText(ui->tableView->model()->data(index).toString());
        ui->le_adresse->setText(e.getadresse());
        ui->le_nom->setText(e.getnom());
        ui->le_nb->setText(QString::number(e.getnb()));
        ui->le_num->setText(QString::number(e.getnum()));
        ui->le_date->setDate(e.getdate());
    }
    else{
        ui->le_adresse->setText("");
        ui->le_nom->setText("");
        ui->le_nb->setText("");
        ui->le_num->setText("");
        ui->le_date->setDate(QDate(2020,01,01));
    }
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    Ticket T;
    T=T.getTicket(ui->tableView_2->model()->data(index).toInt());
    if(T.getid_ticket()!=0){
        qDebug()<<T.getid_evenement();

        ui->le_prix->setText(QString::number(T.getprix()));

    }
    else{

        ui->le_prix->setText("");
    }
}

void MainWindow::on_retour_clicked()
{
    MainWindow::close();
    accueil * g = new accueil();
        g->show();
}
