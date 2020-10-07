#pragma once
#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartGlobal>
#include <QChartView>
#include <QSplineSeries>
#include <QtSql>
#include <QMessageBox>
#include <map>

struct chartValues{
    QString title;
    QSplineSeries *splineSeries = new QSplineSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    QSqlQuery query;
};

class Chart
{
public:
    Chart();
    void getSeries(struct chartValues chartvalues);
    void makeChart(struct chartValues chartvalues);
    void refreshCharts(struct chartValues chartvalues);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    chartValues tempreture;
    chartValues humidity;
private:
    int i;
    double lowestValue, highestValue;
};

#endif // CHART_H
