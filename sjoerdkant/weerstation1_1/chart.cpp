#include <QTimer>
#include "chart.h"

Chart::Chart()
{
    this->connectDatabase();

    //set the values of temperature chart
    this->temperature.title = "Temperature";
    this->temperature.query.exec("select Temperature from reading");
    this->temperature.axisY->setTitleText("°c");

    //set the values of humidity chart
    this->humidity.title = "Humidity";
    this->humidity.query.exec("select Humidity from reading");
    this->humidity.axisY->setTitleText("%");

    //set the values of light chart
    this->light.title = "Light";
    this->light.query.exec("select light from reading");
    this->light.axisY->setTitleText("lux");

    //start making charts
    makeChart(this->temperature);
    makeChart(this->humidity);
    makeChart(this->light);
}

void Chart::makeChart(chartValues chartvalues)
{
    this->updateSeries(chartvalues, 60);

    //set chart settings
    chartvalues.chart->legend()->hide();
    chartvalues.chart->setTitle(chartvalues.title);

    //set chart visual look
    chartvalues.chartView->setRenderHint(QPainter::Antialiasing);
    chartvalues.chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);

    //set X axis name
    chartvalues.axisX->setTitleText("Past Hours");

    //add axis to the chart
    chartvalues.chart->addAxis(chartvalues.axisX, Qt::AlignBottom);
    chartvalues.chart->addAxis(chartvalues.axisY, Qt::AlignLeft);
}

void Chart::updateSeries(chartValues chartvalues, int aantalMinutes)
{
    //prepare chart and series for update
    chartvalues.chart->removeSeries(chartvalues.splineSeries);
    chartvalues.splineSeries->clear();

    //set variabels
    double Yvalue = 0;
    chart_Yvalue_lowest = 100;
    chart_Yvalue_highest = -100;

    //get values from database
    chartvalues.query.last();
    for(int i=0; i>-aantalMinutes; i--){
        //if database has a value on this position
        if(chartvalues.query.previous()){
            Yvalue = chartvalues.query.value(0).toDouble();
            chartvalues.splineSeries->append(i, Yvalue);

            //chack if th Y value is the lowest or highest
            if(Yvalue < chart_Yvalue_lowest){
                chart_Yvalue_lowest = Yvalue;
            }else if(Yvalue > chart_Yvalue_highest){
                chart_Yvalue_highest = Yvalue;
            }
        //if database has no value on this position flatline
        }else{
            chartvalues.splineSeries->append(i, Yvalue);
        }
    }
    //add series to chart
    chartvalues.chart->addSeries(chartvalues.splineSeries);

    //calculate 5% offset for Y axis
    int offset = chart_Yvalue_highest * 0.05;
    if(chart_Yvalue_highest < 0){
        offset = chart_Yvalue_lowest * -0.05;
    }

    //set range of axis
    chartvalues.axisX->setRange(-aantalMinutes/60, 0);
    chartvalues.axisY->setRange(chart_Yvalue_lowest  - offset, chart_Yvalue_highest + offset);

    //attach Y axis to the series so the line is in the middle
    chartvalues.splineSeries->attachAxis(chartvalues.axisY);
}

QDateTime Chart::lastUpdated()
{
    //get datetime of last uploeded data in the database
    QSqlQuery query;
    query.exec("select UploadTime from reading");
    query.last();

    return query.value(0).toDateTime();
}

void Chart::connectDatabase()
{
    //set variables to connect with database
    bool retry = true;
    db.setHostName("databases.aii.avans.nl");
    db.setPort(3306);
    db.setDatabaseName("ljgastel_db2");
    db.setUserName("ljgastel");
    db.setPassword("Ab12345");

    //make connection with database
    while(retry == true){
        if(db.open()){
            retry = false;
        }else {
            //notification no connection with database
            QMessageBox noConnection;
            noConnection.setText("no connection with database possible");
            noConnection.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
            noConnection.setDefaultButton(QMessageBox::Retry);
            int buttonPressed = noConnection.exec();

            switch(buttonPressed){
            case QMessageBox::Close:
                retry = false;
                break;
            case QMessageBox::Retry:
                retry = true;
                break;
            default:
                retry = false;
                break;
            }
        }
    }
}

Chart::~Chart()
{
    delete temperature.splineSeries;
    delete temperature.chart;
    delete temperature.chartView;
    delete temperature.axisX;
    delete temperature.axisY;

    delete humidity.splineSeries;
    delete humidity.chart;
    delete humidity.chartView;
    delete temperature.axisX;
    delete temperature.axisY;

    delete light.splineSeries;
    delete light.chart;
    delete light.chartView;
    delete temperature.axisX;
    delete temperature.axisY;

    db.close();
}
