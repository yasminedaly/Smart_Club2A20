#include "notepad.h"
#include "ui_notepad.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrinter>
#include <QPrintDialog>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this-> setCentralWidget((ui->textEdit));
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void Notepad::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
      QFile file(file_name);
      file_path_ = file_name;
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","file not open");
          return;
        }
      QTextStream in(&file);
      QString text = in.readAll();
      ui->textEdit->setText(text);
      file.close();
}

void Notepad::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
      QFile file(file_name);
      file_path_ = file_name;
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","file not open");
          return;
        }
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText();
      out << text;
      file.flush();
      file.close();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionAbout_Notepad_triggered()
{
    QString about_text;
      about_text  = "Auther : somebody\n";
      about_text += "Date   : 12/05/2016\n";
      about_text += "(C) Notepad  (R)\n";

      QMessageBox::about(this,"About Notepad",about_text);
}

void Notepad::on_actionFont_2_triggered()
{
    bool ok;
      QFont font = QFontDialog::getFont(&ok, this);
      if (ok)
        {
          ui->textEdit->setFont(font);
        } else return;
}

void Notepad::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
      if(color.isValid()) {
          ui->textEdit->setTextColor(color);
        }
}

void Notepad::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
      if(color.isValid())
        {
          ui->textEdit->setTextBackgroundColor(color);
        }
}

void Notepad::on_actionBackground_Color_Edit_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
      if(color.isValid())
        {
          ui->textEdit->setPalette(QPalette(color));
        }
}

void Notepad::on_actionPrint_triggered()
{
      QPrinter printer;
      printer.setPrinterName("desierd printer name");
      QPrintDialog dialog(&printer,this);
      if(dialog.exec() == QDialog::Rejected) return;
      ui->textEdit->print(&printer);
}
