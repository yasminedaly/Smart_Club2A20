#include "statistics.h"
#include "ui_statistics.h"

statistics::statistics(QWidget *parent) :
    QMainWindow(parent)
  ,ui(new Ui::statistics)
{
    ui->setupUi(this);


}

statistics::~statistics()
{
    delete ui;
}
