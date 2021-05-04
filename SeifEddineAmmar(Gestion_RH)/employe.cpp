#include "employe.h"

employe::employe(){}
bool employe::ajouter(){
    QSqlQuery query;
        query.prepare("INSERT INTO EMPLOYE (ID, NOM, NUM, MAIL,DATEAD,SEXE,DEPARTEMENT,SALAIRE) VALUES (:ID, :NOM, :NUM, :MAIL, :DATEAD, :SEXE, :DEPARTEMENT, :SALAIRE)");
        query.bindValue(":ID", id);
        query.bindValue(":NOM", nom);
        query.bindValue(":NUM", num);
        query.bindValue(":MAIL", mail);
        query.bindValue(":DATEAD", datead);
        query.bindValue(":SEXE", sexe);
        query.bindValue(":DEPARTEMENT", departement);
        query.bindValue(":SALAIRE", salaire);
        return query.exec();
}
QSqlQueryModel *employe::afficher(){
    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NUM"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEAD"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("SEXE"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("DEPARTEMENT"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("SALAIRE"));
        return model;
}
bool employe::supprimer(QString idemploye){
    QSqlQuery qry;
        qry.prepare("Delete from EMPLOYE where ID = :ID");
        qry.bindValue(":ID",idemploye);
        return qry.exec();
}
QSqlQueryModel *employe::recherche(QString num)
{

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("SELECT * FROM EMPLOYE WHERE ID LIKE'"+num+"%'");
    return model;
}

QSqlQueryModel *employe::trier(QString crit,QString ordre)
{
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("SELECT * FROM EMPLOYE ORDER BY "+crit+" "+ordre);
    qry->exec();
    model->setQuery(*qry);
    return model;
}


QSqlQueryModel * employe::rechercher_sexe(QString SEXE)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EMPLOYE WHERE SEXE = :SEXE");
    qry.bindValue(":SEXE",SEXE);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


    return model;
}

QSqlQueryModel *employe::rechercher_nom(QString NOM)
{

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("SELECT * FROM EMPLOYE WHERE NOM LIKE'"+NOM+"%'");

    return model;
}

QSqlQueryModel * employe::rechercher_email(QString MAIL)
{
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery("SELECT * FROM EMPLOYE WHERE MAIL like'"+MAIL+"%'");

    return model;
}


QSqlQueryModel * employe::rechercher_date(QDate DATEAD)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EMPLOYE WHERE DATEAD = :DATEAD");
    qry.bindValue(":DATEAD",DATEAD);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);

    return model;
}

QSqlQueryModel * employe::rechercher_combinaison_all(QString NOM,QString SEXE,QDate DATEAD)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM EMPLOYE WHERE NOM=:NOM and SEXE=:SEXE and DATEAD=:DATEAD");
    qry->bindValue(":NOM",NOM);
    qry->bindValue(":SEXE",SEXE);
    qry->bindValue(":DATEAD",DATEAD);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

QSqlQueryModel * employe::rechercher_combinaison_nom_date(QString NOM, QDate DATEAD)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM EMPLOYE WHERE NOM=:NOM and DATEAD=:DATEAD");
    qry->bindValue(":NOM",NOM);
    qry->bindValue(":DATEAD",DATEAD);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

QSqlQueryModel * employe::rechercher_combinaison_sexe_date(QString SEXE, QDate DATEAD)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM EMPLOYE WHERE SEXE=:SEXE and DATEAD=:DATEAD");
    qry->bindValue(":SEXE",SEXE);
    qry->bindValue(":DATEAD",DATEAD);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

QSqlQueryModel * employe::rechercher_combinaison_nom_sexe(QString NOM, QString SEXE)
{
    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM EMPLOYE WHERE NOM=:NOM and SEXE=:SEXE");
    qry->bindValue(":NOM",NOM);
    qry->bindValue(":SEXE",SEXE);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);
    return model;
}

/*void employe::exporter(QTableView *table)
{
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                    filters, &defaultFilter);
    QFile file(fileName);
    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++)
        {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++)
        {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++)
            {
                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
    }
}*/
/*void employe::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
    QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHostEncrypted(host, port); //"smtp.gmail.com" and 465 for gmail TLS
    if (!socket->waitForConnected(timeout)) {
         qDebug() << socket->errorString();
     }
    t = new QTextStream( socket );
}*/
int employe::stati()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from employe where salaire BETWEEN '2000' AND '3000'") ;
    while(requete.next())
    {
            count++ ;
    }
return(count);
}
int employe::stati1()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from employe where :salaire BETWEEN '0' AND '2001'") ;
    while(requete.next())
    {
            count++ ;
    }
return(count);
}

int employe::stati2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from employe where :salaire BETWEEN '3001' AND '100000000000'") ;
    while(requete.next())
    {
            count++ ;
    }
    //QSqlQueryModel * model = new QSqlQueryModel();
    //model->setHeaderData(0,Qt::Vertical,QObject::tr("employe avec plus salaire "));
return(count);
}
int employe::nb_total()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from employe where :salaire BETWEEN '0' AND '100000000'") ;
    while(requete.next())

    {
            count++ ;
    }

return(count);
}
