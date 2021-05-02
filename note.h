#ifndef NOTE_H
#define NOTE_H

#include<QMainWindow>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QPrinter>
#include<QPrintDialog>

namespace Ui {
class note;
}

class note: public QMainWindow
{
    Q_OBJECT

public:
    note(QWidget *parent = nullptr);
    ~note();

private slots:
    void on_actionNew_File_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::note *ui;
    QString currentFile="";
};

#endif // NOTE_H
