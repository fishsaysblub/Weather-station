#pragma once
#ifndef CHART_H
#define CHART_H

#include "chartValues.h"

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartGlobal>
#include <QChartView>
#include <QSplineSeries>
#include <QtSql>
#include <QMessageBox>
#include <map>

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
