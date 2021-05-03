// ---------- NOTEPAD.H ----------

#ifndef NOTEPAD_H
#define NOTEPAD_H

// Provides the main application window on which the user interface
// is built by adding widgets
#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

// Use the standard UI namespace which is tied to the .ui file
namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    // Each QObject executes on a thread
    Q_OBJECT

public:

    // Declare a constructor and by passing 0 we state this widget
    // has no parent
    explicit Notepad(QWidget *parent = 0);

    // Declare a destructor which will free resources
    ~Notepad();

private slots:


    void on_actionCr_er_un_nouveau_fichier_triggered();

    void on_actionOuvrir_un_fichier_triggered();

    void on_actionEnregistrer_triggered();

    void on_actionEnregister_sous_triggered();

    void on_actionCouper_triggered();

    void on_actionCopier_triggered();

    void on_actionColler_triggered();

    void on_actionRefaire_triggered();

    void on_actionAnnuler_triggered();

private:

    // Point to the ui class
    Ui::Notepad *ui;

    // A Qt character string that will hold text entered by the user
    QString currentFile = "";
};

#endif // NOTEPAD_H

// ---------- END NOTEPAD.H ----------
