#ifndef STATS_H
#define STATS_H

#include <QMainWindow>


#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>

#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGridLayout>

#include"evenement.h"
#include "ticket.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class stats;
}

class stats : public QMainWindow
{
    Q_OBJECT

public:
    explicit stats(QWidget *parent = nullptr);
    ~stats();

private:
    Ui::stats *ui;
    Evenement evt;
    Ticket tkt;
};

#endif // STATS_H
