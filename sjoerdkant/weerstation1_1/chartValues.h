#pragma once
#ifndef CHARTVALUES_H
#define CHARTVALUES_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartGlobal>
#include <QChartView>
#include <QSplineSeries>
#include <QtSql>

struct chartValues{
    QString title;
    QSplineSeries *splineSeries = new QSplineSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    QSqlQuery query;
};

#endif // CHARTVALUES_H
