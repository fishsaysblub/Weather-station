#pragma once
#ifndef CHARTVALUES_H
#define CHARTVALUES_H

#include <QtCharts>
#include <QtSql>

/*! \struct chartValues
 * \brief The chartValues struct
 *
 *  struct with all the values to present one chart
 */

struct chartValues{
    QString title;                                      /*!< The title of the chart */
    QSplineSeries *splineSeries = new QSplineSeries();  /*!< The line of the chart */
    QChart *chart = new QChart();                       /*!< The chart itself*/
    QChartView *chartView = new QChartView(chart);      /*!< The visual aspects of the chart */
    QSqlQuery query;                                    /*!< The query to get the data from the database for the chart */
};

#endif // CHARTVALUES_H
