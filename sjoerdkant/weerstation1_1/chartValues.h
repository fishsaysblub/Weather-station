#pragma once
#ifndef CHARTVALUES_H
#define CHARTVALUES_H

#include <QtCharts>
#include <QtSql>

struct chartValues{
    QString title;
    QSplineSeries *splineSeries = new QSplineSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    QSqlQuery query;
};

#endif // CHARTVALUES_H
