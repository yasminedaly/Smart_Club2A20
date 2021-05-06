#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
#include <QDebug>
#include "abonnes.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString user() const ;
 //QString userID;
 private slots:
    void on_pushButton_submit_clicked();


private:
    Ui::MainWindow *ui;
    QByteArray data;
    QString id;
     int e;
     Abonnes *abonnes ;
};
#endif // MAINWINDOW_H
