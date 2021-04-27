#ifndef GLOWNE_H
#define GLOWNE_H
#include <listapytan.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class glowne; }
QT_END_NAMESPACE

class glowne : public QMainWindow
{
    Q_OBJECT

public:
    glowne(QWidget *parent = nullptr);
    ~glowne();
    ///Lista pytan
    ListaPytan lista;

private slots:

    void on_lineEdit_editingFinished();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonNowaGra_clicked();

    void on_lineEdit_returnPressed();


private:
    Ui::glowne *ui;
};
#endif // GLOWNE_H
