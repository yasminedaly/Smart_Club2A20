#include "notification.h"

notification::notification()
{

}
void notification::Alerte_Ajout(int id,int i)
{

    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon();

    notifyIcon->setIcon(QIcon("C:/Users/DeLL/Desktop/icon.png"));

       notifyIcon->show();

       if (i==0)
       {

       notifyIcon->showMessage("Evenement","On peut pas ajouter cet evenement",QSystemTrayIcon::Warning,1500);
       }
       else if (i==1)
       {
         notifyIcon->showMessage("Evenement","Un nouveau evenement avec un CIN N°"+res+" a été ajouté",QSystemTrayIcon::Information,1500);
       }

}

void notification::Alerte_Modifier(int id,int i)
{

    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon();

    notifyIcon->setIcon(QIcon("C:/Users/DeLL/Desktop/icon.png"));

       notifyIcon->show();
       notifyIcon->showMessage("Bonjour","Hello, world!"); // On affiche une infobulle

       if (i==0)
       {

       notifyIcon->showMessage("Evenement","On peut pas ajouter cet evenement",QSystemTrayIcon::Warning,1500);
       }
       else if (i==1)
       {
         notifyIcon->showMessage("Evenement","Un nouveau evenement avec un CIN N°"+res+" a été ajouté",QSystemTrayIcon::Information,1500);
       }

}
void notification::Alerte_Supprimer(int id, int i)
{

    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon();

    notifyIcon->setIcon(QIcon("C:/Users/DeLL/Desktop/icon.png"));

       notifyIcon->show();
       notifyIcon->showMessage("Bonjour","Hello, world!"); // On affiche une infobulle

       if (i==0)
       {

       notifyIcon->showMessage("Evenement","On peut pas ajouter cet evenement",QSystemTrayIcon::Warning,1500);
       }
       else if (i==1)
       {
         notifyIcon->showMessage("Evenement","Un nouveau evenement avec un CIN N°"+res+" a été ajouté",QSystemTrayIcon::Information,1500);
       }

}
