#pragma once
#ifndef CHART_H
#define CHART_H

#include <QDateTime>
#include "chartValues.h"

/*! \class Chart
 * \brief The Chart class
 *
 * A class that contains everything needed to make a chart.
 */

class Chart
{
public:
    /*!
     * \brief Chart
     *
     * The constructor is used to make the connection with the database and to set the values of the chartvalues structs.
     * \sa db(), connectDatabase() and chartValues()
     */
    Chart();

    /*!
     * \brief updateSeries
     *
     * A public member to  get the series from the database for the chart.
     * \param chartvalues the struct of the chart
     * \sa db() and chartValues()
     */
    void updateSeries(chartValues chartvalues, int aantalMinutes);

    /*!
     * \brief makeChart
     *
     * A public member to set all the variables of the chart.
     * \param chartvalues the struct of the chart
     * \sa updateSeries(), chartValues(), Yvalue_lowest() and Yvalue_highest()
     */
    void makeChart(chartValues chartvalues);

    /*!
     * \brief connectDatabase
     *
     * A public member to open a connction with the database.
     * \sa db()
     */
    void connectDatabase();

    /*!
     * \brief lastUpdated
     *
     * A public member to display the last data update.
     */
    QDateTime lastUpdated();

public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  /*!< The database of type mysql. */

    chartValues temperature;                                /*!< A \sa chartValues() struct named temperature. */
    chartValues humidity;                                   /*!< A \sa chartValues() struct named humidity. */
    chartValues light;                                      /*!< A \sa chartValues() struct named light. */

private:
    double  chart_Yvalue_lowest;                            /*!< A double containing the lowest Y value of a chart. */
    double  chart_Yvalue_highest;                           /*!< A double containing the highest Y value of a chart. */

public:
    /*!
     * \brief ~Chart
     *
     * The destructor to delete the chartValues and close the database.
     * \sa chartValues() and db()
     */
    virtual ~Chart();
};

#endif // CHART_H
