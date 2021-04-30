#include "note.h"
#include "ui_note.h"

note::note(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::note)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

note::~note()
{
    delete ui;
}

void note::on_actionNew_File_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void note::on_actionOpen_File_triggered()
{
    QString filename =QFileDialog::getOpenFileName(this,"Open the File");
    QFile file(filename);
    currentFile=filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot Open File: "+ file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void note::on_actionSave_as_triggered()
{
    QString filename= QFileDialog::getSaveFileName(this,"Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot Save File: "+ file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.close();

}

void note::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer,this);
    if(pDialog.exec() ==QDialog::Rejected){
        QMessageBox::warning(this, "warning","Cannot Access Printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void note::on_actionExit_triggered()
{
    QApplication::quit();
}

void note::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void note::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void note::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void note::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void note::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
