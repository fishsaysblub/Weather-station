#pragma once
#ifndef CHART_H
#define CHART_H

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
     * \brief getSeries
     *
     * A public member to  get the series from the database for the chart.
     * \param chartvalues the struct of the chart
     * \sa db() and chartValues()
     */
    void getSeries(chartValues chartvalues);

    /*!
     * \brief makeChart
     *
     * A public member to set all the variables of the chart.
     * \param chartvalues the struct of the chart
     * \sa chartValues(), Xvalue(), Yvalue_lowest() and Yvalue_highest()
     */
    void makeChart(chartValues chartvalues);

    /*!
     * \brief connectDatabase
     *
     * A public member to open a connction with the database.
     * \sa db()
     */
    void connectDatabase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  /*!< The database of type mysql. */

    chartValues tempreture; /*!< A \sa chartValues() struct named tempreture. */
    chartValues humidity;   /*!< A \sa chartValues() struct named humidity. */

private:
    int Xvalue;             /*!< A int containing the X value of a chart. */
    double Yvalue_lowest;   /*!< A double containing the lowest Y value of a chart. */
    double Yvalue_highest;  /*!< A double containing the highest Y value of a chart. */

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
