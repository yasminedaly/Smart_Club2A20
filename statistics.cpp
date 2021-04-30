#include "statistics.h"
#include "ui_statistics.h"

statistics::statistics(QWidget *parent) :
    QMainWindow(parent)
  ,ui(new Ui::statistics)
{
    ui->setupUi(this);

                QPieSeries *series=new QPieSeries();

              series->append("Payé",Fac.Statistiques_Factures_O());
              series->append("Non payé",Fac.Statistiques_Factures_N());


              QPieSlice *slice1=series->slices().at(0);
              slice1->setExploded();
              slice1->setLabelVisible();


              QPieSlice *slice2 = series->slices().at(1);
              slice2->setExploded();
              slice2->setLabelVisible();



              QChart *chart =new QChart();
              chart->addSeries(series);
              chart->setTitle("Paiement des factures ");
              chart->setAnimationOptions(QChart::AllAnimations);
              QChartView *chartview=new QChartView(chart);
              this->setCentralWidget(chartview);
}

statistics::~statistics()
{
    delete ui;
}
