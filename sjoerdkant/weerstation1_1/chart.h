#pragma once
#ifndef CHART_H
#define CHART_H

#include "chartValues.h"

class Chart
{
public:
    Chart();
    void makeSeries(chartValues chartvalues);
    void makeChart(chartValues chartvalues);
    void connectDatabase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    chartValues tempreture;
    chartValues humidity;

private:
    int Xvalue;
    double Yvalue_lowest;
    double Yvalue_highest;

public:
    virtual ~Chart();
};

#endif // CHART_H
