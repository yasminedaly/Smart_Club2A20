#include "stats.h"
#include "ui_stats.h"

stats::stats(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);

   /* QBarSet *set1=new QBarSet("Nombre des Tickets");


    set1->append(tkt.calculeTicket(1));
    QBarSeries *series=new QBarSeries();
    series->append(set1);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques des employes");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories=evt.listeEvents();

    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartview=new QChartView(chart);

    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);
    this->setLayout(mainLayout);*/


    QPieSeries *series=new QPieSeries();
    QStringList l=evt.listeEvents();
   for (int i = 0; i < l.size(); ++i){

       series->append("Evenement num :"+l[i] ,tkt.calculeTicket(l[i].toInt()));
   }


    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartview=new QChartView(chart);

    this->setCentralWidget(chartview);

}

stats::~stats()
{
    delete ui;
}
