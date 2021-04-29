#ifndef ENVOYERMAIL_H
#define ENVOYERMAIL_H
#include <QString>
#include <QDialog>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QtCore/QCoreApplication>
#include <QDialog>

namespace Ui {
class EnvoyerMail;
}

class EnvoyerMail : public QDialog
{
    Q_OBJECT

public:
    explicit EnvoyerMail(QWidget *parent = nullptr);
    ~EnvoyerMail();
private slots:
    void sendMail();
    void mailSent(QString);
    void browse();
   // void on_sendBtn_clicked();

private:
    Ui::EnvoyerMail *ui;
    QStringList files;
};

#endif // ENVOYERMAIL_H
