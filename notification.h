#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>

class notification
{

public:
    notification();
    void Alerte_Ajout(int id, int i);
    void Alerte_Modifier(int id,int i);
    void Alerte_Supprimer(int id,int i);
};


#endif // NOTIFICATION_H
