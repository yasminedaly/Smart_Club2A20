#ifndef CALENDAR_G_FOURNISSEUR_H
#define CALENDAR_G_FOURNISSEUR_H
#include <QDate>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextBrowser;
QT_END_NAMESPACE

class Calendar_G_fournisseur: public QMainWindow
{
    Q_OBJECT
public:
    Calendar_G_fournisseur();

public slots:
    void setFontSize(int size);
    void setMonth(int month);
    void setYear(QDate date);

private:
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;
};

#endif // CALENDAR_G_FOURNISSEUR_H
