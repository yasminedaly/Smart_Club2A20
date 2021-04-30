#ifndef CALENDAR_G_FOURNISSEURS_H
#define CALENDAR_G_FOURNISSEURS_H


class Calendar_G_Fournisseurs
{
public:
    Calendar_G_Fournisseurs();

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

#endif // CALENDAR_G_FOURNISSEURS_H
