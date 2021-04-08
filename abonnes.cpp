#include "abonnes.h"
#include "seances.h"
#include "ui_abonnes.h"
#include "sub.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include <QPixmap>
#include "exportexcelobject.h"
#include <QPainter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QFile>
#include "QFileDialog"
#include "QDesktopServices"
#include "algorithm"
#include "iostream"
#include "string"
#include <QMediaPlayer>
#include "qcustomplot.h"



Abonnes::Abonnes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Abonnes)
{

    ui->setupUi(this);
  ui->li_cin->setValidator(new QIntValidator(00000000, 99999999, this));
  ui->li_tel->setValidator(new QIntValidator(0, 99999999, this));
  ui->show_abonnes->setModel(S.afficher());
   ui->show_seances->setModel(A.afficher_S());

   animation= new QPropertyAnimation(ui->pb_Abonne,"geometry");
       animation->setDuration(5000);
       animation->setEndValue(QRect(880,320,91,41));
       animation->start();
       animation= new QPropertyAnimation(ui->modifier_Abonnes,"geometry");
       animation->setDuration(5000);
       animation->setEndValue(QRect(980,320,91,41));
       animation->start();
       animation= new QPropertyAnimation(ui->supprimer_Abonnes,"geometry");
       animation->setDuration(1500);
       animation->setEndValue(QRect(950,340,91,41));
       animation->start();

       QMediaPlayer * music =new QMediaPlayer;
            music->setMedia(QUrl("C:/Users/21650/Desktop/New folder/welcome.mp3")) ;

            music->play();

       player= new QMediaPlayer(this);

       this->setFixedSize(this->geometry().width(),this->geometry().height());

       updateList();

       connect(updater, SIGNAL(timeout()), this, SLOT(update()));

       player->setVolume(100);

       ui->listWidget->setCurrentRow(0);

       if(ui->listWidget->count() != 0){
           loadTrack();
           player->pause();
           updater->start();

       }

 }


Abonnes::~Abonnes()
{
    delete ui;
}

//add sub
void Abonnes::on_pb_Abonne_clicked()
{
    int Cin=ui->li_cin->text().toInt();
              int Num_tel=ui->li_tel->text().toInt();
              QString Nom=ui->li_nom->text();
              QString Prenom=ui->li_prenom->text();
              QString Email=ui->li_email->text();
              QDate ddn_abonnes=ui->li_date_s->date();
             QString type_abonnement=ui->li_ab->text();
             QString sexe=ui->li_sexe->text();

sub S (Cin,Email,Nom,Prenom,Num_tel,ddn_abonnes,type_abonnement,sexe);
bool test=S.ajouter();
        if(test)
            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
                ui->show_abonnes->setModel(S.afficher());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }


void Abonnes::on_pb_Seance_clicked()
{
    int ID_salle=ui->li_id->text().toInt();
    int Num_salle=ui->li_salle->text().toInt();
    int ID_employe=ui->li_id_e->text().toInt();
    int Capacite_salle=ui->li_cap->text().toInt();
    QString Titre_cours=ui->li_titre->text();
    QDate Date_seance=ui->li_date->date();
    QString Niveau_seance=ui->li_cour->text();
    seances A (ID_salle,ID_employe,Num_salle,Capacite_salle,Titre_cours,Date_seance,Niveau_seance);

    bool test=A.ajouter_S();
            if(test)
                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Ajout effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
              ui->show_seances->setModel(A.afficher_S());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Ajout non effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
}

void Abonnes::on_supprimer_Abonnes_clicked()
{
    sub S1; S1.setCin(ui->li_cin->text().toInt());
     bool test=S1.supprimer(S1.getCin());
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_abonnes->setModel(S.afficher());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
   }


void Abonnes::on_modifier_Abonnes_clicked()
    {       int Cin=ui->li_cin->text().toInt();
            int Num_tel=ui->li_tel->text().toInt();
            QString Nom=ui->li_nom->text();
            QString Prenom=ui->li_prenom->text();
            QString Email=ui->li_email->text();
            QDate ddn_abonnes=ui->li_date_s->date();
           QString type_abonnement=ui->li_ab->text();
            QString sexe=ui->li_sexe->text();



        sub S (Cin,Email,Nom,Prenom,Num_tel,ddn_abonnes,type_abonnement,sexe);

            bool test=S.modifier();
            if(test)

                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Modification effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                ui->show_abonnes->setModel(S.afficher());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification non effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
            }





void Abonnes::on_modifier_seances_clicked()
{

    int ID_salle=ui->li_id->text().toInt();
    int Num_salle=ui->li_salle->text().toInt();
    int ID_employe=ui->li_id_e->text().toInt();
    int Capacite_salle=ui->li_cap->text().toInt();
    QString Titre_cours=ui->li_titre->text();
    QDate Date_seance=ui->li_date->date();
    QString Niveau_seance=ui->li_cour->text();


     seances A (ID_salle,Num_salle,ID_employe,Capacite_salle,Titre_cours,Date_seance,Niveau_seance);

            bool test=A.modifier_S();
            if(test)

                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Modification effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                    ui->show_seances->setModel(A.afficher_S());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification non effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }

}

void Abonnes::on_supprimer_seances_clicked()
{
    seances A1; A1.setID_salle(ui->li_id->text().toInt());
     bool test=A1.supprimer_S(A1.getID_salle());
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_seances->setModel(A.afficher_S());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
}

void Abonnes::on_tri_nom_clicked()
{
     ui->show_abonnes->setModel(tmpsub.afficher_tri_nom());
}

void Abonnes::on_tri_prenom_clicked()
{
     ui->show_abonnes->setModel(tmpsub.afficher_tri_prenom());
}

void Abonnes::on_tri_ddn_clicked()
{
    ui->show_abonnes->setModel(tmpsub.afficher_tri_ddn());
}

void Abonnes::on_pb_xl_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->show_seances);

        //colums to export
        obj.addField(0, "ID_salle", "char(20)");
        obj.addField(1, "Num_salle", "char(20)");
        obj.addField(2, "ID_employe", "char(20)");
        obj.addField(3, "Capacite_salle", "char(20)");
        obj.addField(4, "Titre_cours", "char(20)");
        obj.addField(5, "Date_seance", "char(20)");
        obj.addField(6, "Niveau_seance", "char(20)");
        obj.addField(7, "sexe", "char(20)");



        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

void Abonnes::on_tri_date_clicked()
{
     ui->show_seances->setModel(tmpseances.afficher_tri_date());
}

void Abonnes::on_tri_capacite_clicked()
{
     ui->show_seances->setModel(tmpseances.afficher_tri_capacite());
}

void Abonnes::on_show_abonnes_activated(const QModelIndex &index)
{
    QString val=ui->show_abonnes->model()->data(index).toString();
    QSqlQuery qry;
       qry.prepare("SELECT * from abonnes where cin_abonnes='"+val+"' ");
       if(qry.exec())
       {
           while(qry.next())
           {


               ui->li_cin->setText(qry.value(0).toString());
               ui->li_email->setText(qry.value(1).toString());
               ui->li_nom->setText(qry.value(2).toString());
               ui->li_prenom->setText(qry.value(3).toString());
               ui->li_ab->setText(qry.value(4).toString());
               ui->li_date_s->setDate(qry.value(5).toDate());
               ui->li_tel->setText(qry.value(6).toString());
               ui->li_sexe->setText(qry.value(7).toString());
           }
       }
   }



void Abonnes::on_pushButton_clicked()
{
    QString strStream;
         QTextStream out(&strStream);
                         const int rowCount = ui->show_abonnes->model()->rowCount();
                         const int columnCount = ui->show_abonnes->model()->columnCount();
                         QString TT = QDate::currentDate().toString("yyyy/MM/dd");



                         out <<  "<html>\n"
                             "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             <<  QString("<title>%1</title>\n").arg("strTitle")
                             <<  "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\">"
                                 "<strong>                                                      "+TT+" </ strong>"


                            //     "<align='right'> " << datefich << "</align>"
                                 "<img src='C:/Users/21650/Desktop/ChessMate/logo.png' width='100' height='100'>\n"
                             "<center> <H1> Liste des abonnes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


                         // headers
                         out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->show_abonnes->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->show_abonnes->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->show_abonnes->isColumnHidden(column)) {
                                     QString data = ui->show_abonnes->model()->data(ui->show_abonnes->model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table> </center>\n"
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


void Abonnes::on_show_seances_activated(const QModelIndex &index)
{

    QString val=ui->show_seances->model()->data(index).toString();
    QSqlQuery qry;
       qry.prepare("SELECT* FROM seances where ID_salle='"+val+"' ");
       if(qry.exec())
       {
           while(qry.next())
           {


               ui->li_id->setText(qry.value(0).toString());
               ui->li_id_e->setText(qry.value(1).toString());
               ui->li_salle->setText(qry.value(2).toString());
               ui->li_cap->setText(qry.value(3).toString());
               ui->li_titre->setText(qry.value(4).toString());
               ui->li_date->setDate(qry.value(5).toDate());
               ui->li_cour->setText(qry.value(6).toString());
           }
       }

}

void Abonnes::on_recherch__clicked()
{
    int choix;
            choix=ui->cher_ab->currentIndex();
            QString linechercher=ui->cherch_ab->text();
            ui->show_seances->setModel(A.chercher_seance(choix,linechercher));
}

void Abonnes::on_SliderVolume_sliderMoved(int position)
{
    player->setVolume(position);

}

void Abonnes::on_pushButton_2_clicked()
{
    player->stop();

}

void Abonnes::on_pushButton_4_clicked()
{
    //load l file
    player->setMedia(QUrl::fromLocalFile("C:/Users/21650/Downloads/1.mp3"));
    player->play();
    qDebug() << player->errorString();

}

void Abonnes::on_add_clicked()
{   bool startUpdater = false;if(ui->listWidget->count() == 0) startUpdater = true;
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"));
    if(!files.empty())
    {
        playlist.add(files);
        updateList();
        ui->save->setChecked(false);
        if(shuffle) shufflePlaylist();
        if(startUpdater) updater->start();
    }
}

void Abonnes::on_remove_clicked()
{
    int index = getIndex();
    if(index != -1)
    {
       playlist.remove(index);
       updateList();
       ui->listWidget->setCurrentRow(index);
       ui->save->setChecked(false);
       if(shuffle) shufflePlaylist();
    }
}

void Abonnes::on_save_clicked()
{
    playlist.save();
    ui->save->setChecked(true);
}


void Abonnes::on_listWidget_doubleClicked(const QModelIndex &index)
{
    lCounter = getIndex();

    ui->play->setChecked(false);
    ui->searchBar->clear();

    loadTrack();
    player->play();
}


void Abonnes::on_play_clicked()
{
    if(ui->listWidget->count() != 0)
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
    }
   else
   {
        player->play();
        updater->start();
   }
}

void Abonnes::on_forward_clicked()
{   if(ui->listWidget->count() != 0)
    if(repeat)
    {
        repeat = !repeat;next();repeat = !repeat;
    }
    else
    {
        next();
    }
}

void Abonnes::on_back_clicked()
{   if(ui->listWidget->count() != 0)
    if(player->position() > 3000)
    {
       player->setPosition(0);
    }
    else
    {
        back();
    }
}

void Abonnes::on_volumeBar_valueChanged(int value)
{
    player->setVolume(value);
    (value != 0)?ui->mute->setChecked(false):ui->mute->setChecked(true);
}

void Abonnes::on_seekBar_sliderMoved(int position)
{
    player->setPosition(player->duration() / 1000 * position);
}

void Abonnes::on_mute_clicked()
{
    muted = !muted;
    (muted)?player->setVolume(0):player->setVolume(ui->volumeBar->value());
}


void Abonnes::on_repeat_clicked()
{
     repeat = !repeat;
}


void Abonnes::on_shuffle_clicked()
{
    shuffle = !shuffle;
    if(shuffle)
        shufflePlaylist();
}

void Abonnes::update()
{   if(!ui->seekBar->isSliderDown())
        ui->seekBar->setValue((double)player->position()/player->duration() * 1000);

    if(player->state() == QMediaPlayer::StoppedState)
    {
        next();
    }
}

void Abonnes::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist.getTracksNameList());
}

int Abonnes::getIndex()
{
    return ui->listWidget->currentIndex().row();
}

void Abonnes::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return :
    {
        lCounter = getIndex();
        if(lCounter != -1)
        {
            ui->play->setChecked(false);
            ui->searchBar->clear();

           loadTrack();
           player->play();
        }
        break;
    }
    case Qt::Key_Up :
    {
        int ind = getIndex() - 1;if(ind < 0)ind = ui->listWidget->count() - 1;
        ui->listWidget->setCurrentRow(ind);
        break;
    }
    case Qt::Key_Down :
    {
        int ind = getIndex() + 1;if(ind >= ui->listWidget->count())ind = 0;
        ui->listWidget->setCurrentRow(ind);
        break;
    }
    default :
    {
        ui->searchBar->setFocus();

        break;
    }
    }
}

void Abonnes::next()
{
    lCounter++;

    if(repeat)
    {
        lCounter--;
    }

    if(lCounter >= ui->listWidget->count())
        lCounter = 0;

    (!shuffle or repeat) ? ui->listWidget->setCurrentRow(lCounter) : ui->listWidget->setCurrentRow(shuffledPlaylist[lCounter]);

    ui->play->setChecked(false);
    ui->searchBar->clear();

    loadTrack();
    player->play();

}

void Abonnes::back()
{
     lCounter--;

     if(lCounter < 0)
        lCounter = ui->listWidget->count() - 1;


     (!shuffle) ? ui->listWidget->setCurrentRow(lCounter) : ui->listWidget->setCurrentRow(shuffledPlaylist[lCounter]);

     ui->play->setChecked(false);
     ui->searchBar->clear();

     loadTrack();
     player->play();
}

void Abonnes::shufflePlaylist()
{
    shuffledPlaylist.resize(0);

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        shuffledPlaylist.push_back(i);
    }

    random_shuffle(shuffledPlaylist.begin(), shuffledPlaylist.end());
}

void Abonnes::loadTrack()
{
     QString qstr = QString::fromStdString(playlist.tracks[getIndex()].getLocation());
     player->setMedia(QUrl::fromLocalFile(qstr));
     qstr = QString::fromStdString(playlist.tracks[getIndex()].getName());
     ui->currentSong->setText(qstr);
}

void Abonnes::on_searchBar_textChanged(const QString &arg1)
{
    if(ui->searchBar->text().toStdString() != "")
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->text().toLower().toStdString().find(arg1.toLower().toStdString()) != string::npos )
        {
            ui->listWidget->setCurrentRow(i);
            break;
        }
    }
}

void Abonnes::on_recherch_ab_clicked()
{
    int choix;
            choix=ui->cher_abb->currentIndex();
            QString linechercher=ui->cherch_abb->text();
            ui->show_abonnes->setModel(A.chercher_seance(choix,linechercher));
}

void Abonnes::on_stat_clicked()
{
    double fem=0;
    double hom=0;

    QSqlQuery q;
            q.prepare("SELECT * FROM abonnes where UPPER(sexe)='HOMME' ");
            q.exec();
              while (q.next())
            {
            hom++;
            }

              q.prepare("SELECT * FROM abonnes where UPPER(sexe)='FEMME' ");
              q.exec();
                while (q.next())
              {
              fem++;
              }

        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 300);
        gradient.setColorAt(0, QColor(80, 80, 80));
        gradient.setColorAt(0.38, QColor(95, 95, 95));
        gradient.setColorAt(1, QColor(70, 70, 70));
        ui->widget->setBackground(QBrush(gradient));

        // create empty bar chart objects:

        QCPBars *fossil = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        fossil->setAntialiased(false);


        fossil->setStackingGap(2);
        // set names and colors:

        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2 ;
        labels << "homme" << "femme" ;
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        ui->widget->xAxis->setTicker(textTicker);
        ui->widget->xAxis->setTickLabelRotation(60);
        ui->widget->xAxis->setSubTicks(false);
        ui->widget->xAxis->setTickLength(0, 4);
        ui->widget->xAxis->setRange(0, 13);
        ui->widget->xAxis->setBasePen(QPen(Qt::white));
        ui->widget->xAxis->setTickPen(QPen(Qt::white));
        ui->widget->xAxis->grid()->setVisible(true);
        ui->widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->widget->xAxis->setTickLabelColor(Qt::white);
        ui->widget->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        ui->widget->yAxis->setRange(0, 10);
        ui->widget->yAxis->setPadding(5); // a bit more space to the left border
        ui->widget->yAxis->setLabel("SEXE");
        ui->widget->yAxis->setBasePen(QPen(Qt::white));
        ui->widget->yAxis->setTickPen(QPen(Qt::white));
        ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
        ui->widget->yAxis->grid()->setSubGridVisible(true);
        ui->widget->yAxis->setTickLabelColor(Qt::white);
        ui->widget->yAxis->setLabelColor(Qt::white);
        ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:
        QVector<double> fossilData;

        fossilData  << hom << fem ;
        fossil->setData(ticks, fossilData);

        //ui->widget->legend->setVisible(true);
        ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
        ui->widget->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        ui->widget->legend->setFont(legendFont);
        ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}


