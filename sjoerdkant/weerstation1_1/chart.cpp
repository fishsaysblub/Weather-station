#include "chart.h"

Chart::Chart()
{
    this->connectDatabase();

    //set the values necessery to make chart
    this->tempreture.title = "tempreture";
    this->tempreture.query.exec("select doubleTemperatuur from temperatuur");
    this->humidity.title = "humidity";
    this->humidity.query.exec("select doubleHumidity from humidity");

    //start making charts
    makeChart(this->tempreture);
    makeChart(this->humidity);
}

void Chart::makeChart(struct chartValues chartvalues)
{
    this->makeSeries(chartvalues);

    //set chart settings
    chartvalues.chart->addSeries(chartvalues.splineSeries);
    chartvalues.chart->legend()->hide();
    chartvalues.chart->createDefaultAxes();
    chartvalues.chart->axes(Qt::Vertical).first()->setRange(Yvalue_lowest, Yvalue_highest);
    chartvalues.chart->axes(Qt::Horizontal).first()->setRange(0, Xvalue);
    chartvalues.chart->setTitle(chartvalues.title);

    //set chart visual look
    chartvalues.chartView->setRenderHint(QPainter::Antialiasing);
    chartvalues.chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}


void Chart::makeSeries(struct chartValues chartvalues)
{
    Yvalue_lowest = 0;
    Yvalue_highest = 0;
    Xvalue=0;

    //get values from database
    while(chartvalues.query.next()){
        double Yvalue = chartvalues.query.value(0).toDouble();
        chartvalues.splineSeries->append(Xvalue, Yvalue);
        Xvalue++;

        if(Yvalue < Yvalue_lowest){
            Yvalue_lowest = Yvalue;
        }else if(Yvalue > Yvalue_highest){
            Yvalue_highest = Yvalue;
        }
    }
}

void Chart::connectDatabase()
{
    bool retry = true;
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("weatherstation");
    db.setUserName("root");
    db.setPassword("root");

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
    delete tempreture.splineSeries;
    delete tempreture.chart;
    delete tempreture.chartView;

    delete humidity.splineSeries;
    delete humidity.chart;
    delete humidity.chartView;
}
