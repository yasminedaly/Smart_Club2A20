#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMainWindow>
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
#include "factures.h"

QT_CHARTS_USE_NAMESPACE namespace Ui {
class statistics;
}

class statistics : public QMainWindow
{
    Q_OBJECT

public:
    explicit statistics(QWidget *parent = nullptr);
    ~statistics();

private:
    Ui::statistics *ui;
    Factures Fac;
};

#endif // STATISTICS_H
