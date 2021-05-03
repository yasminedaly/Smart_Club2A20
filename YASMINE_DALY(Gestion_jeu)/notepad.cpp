// ---------- NOTEPAD.CPP ----------

#include "notepad.h"
#include "ui_notepad.h"

// The Notepad constructor
Notepad::Notepad(QWidget *parent) :

    // Call the QMainWindow constructor
    QMainWindow(parent),

    // Create the UI class and assign it to the ui member
    ui(new Ui::Notepad)
{
    // Setup the UI
    ui->setupUi(this);

    // Have the textedit widget take up the whole window
    this->setCentralWidget(ui->textEdit);
}

// Destructor that deletes the UI
Notepad::~Notepad()
{
    delete ui;
}

// We can type in commands on our menubar which will then appear in
// the Action Editor.
// Right click the Action -> Go to slot -> Triggered -> Add code for the event

// With Qt objects communicate in a different way from other frameworks

// Most frameworks handle an event by creating a function that processes
// events by calling other functions when an event occurs

// With Qt widgets issue a Signal when an event occurs and specific
// Slots (functions) are called in response to the signal

// ----- ADDING ICONS TO TOOLBAR & MENU -----

// 1. Add Resource Folder : Right Click Project -> Add New ->
// Qt -> Qt Resource File -> Name : Resources Path: Folder

// 2. Add Icons to Resource Folder : Select resource file ->
// Add Prefix -> /imgs -> Add Files -> Select icons

// 3. Add Icons to File Menu : Right click item in Action Editor ->
// Choose Resource -> Select Icon -> Click to show image

// 4. Add items to the toolbar by dragging from the Action
// Editor to the toolbar

// ----- END ADDING ICONS TO TOOLBAR & MENU -----

void Notepad::on_actionCr_er_un_nouveau_fichier_triggered()
{
    // Global referencing the current file that we are clearing
        currentFile.clear();

        // Clear the textEdit widget buffer
        ui->textEdit->setText(QString());
}



void Notepad::on_actionOuvrir_un_fichier_triggered()
{
    // Opens a dialog that allows you to select a file to open
       QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

       // An object for reading and writing files
       QFile file(fileName);

       // Store the currentFile name
       currentFile = fileName;

       // Try to open the file as a read only file if possible or display a
       // warning dialog box
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
}
       // Set the title for the window to the file name
          setWindowTitle(fileName);

          // Interface for reading text
          QTextStream in(&file);

          // Copy text in the string
          QString text = in.readAll();

          // Put the text in the textEdit widget
          ui->textEdit->setText(text);

          // Close the file
          file.close();
      }
void Notepad::on_actionEnregistrer_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        currentFile = fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
}

void Notepad::on_actionEnregister_sous_triggered()
{
    // Opens a dialog for saving a file
        QString fileName = QFileDialog::getSaveFileName(this, "Save as");

        // An object for reading and writing files
        QFile file(fileName);

        // Try to open a file with write only options
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }

        // Store the currentFile name
        currentFile = fileName;

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for writing text
        QTextStream out(&file);

        // Copy text in the textEdit widget and convert to plain text
        QString text = ui->textEdit->toPlainText();

        // Output to file
        out << text;

        // Close the file
        file.close();
}

void Notepad::on_actionCouper_triggered()
{
     ui->textEdit->cut();
}


void Notepad::on_actionCopier_triggered()
{
     ui->textEdit->copy();
}

void Notepad::on_actionColler_triggered()
{
     ui->textEdit->paste();
}

void Notepad::on_actionRefaire_triggered()
{
     ui->textEdit->redo();
}

void Notepad::on_actionAnnuler_triggered()
{
     ui->textEdit->undo();
}
