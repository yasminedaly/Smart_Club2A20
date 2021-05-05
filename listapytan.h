#ifndef LISTAPYTAN_H
#define LISTAPYTAN_H
#include <pytanie.h>
#include <QList>
#include <QFile>

class ListaPytan
{
public:
    ListaPytan();
    QList <Pytanie> lista;
    ///Max liczba pytan
    int maxPytan;

};

#endif // LISTAPYTAN_H
