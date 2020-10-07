#include "chart.h"

Chart::Chart()
{
    //connection settings for database
    bool retry = true;
    this->db.setHostName("127.0.0.1");
    this->db.setPort(3306);
    this->db.setDatabaseName("weatherstation");
    this->db.setUserName("root");
    this->db.setPassword("root");

    //make connection with database
    while(retry == true){
        if(this->db.open()){
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

    //set the values necessery to make chart
    this->tempreture.title = "tempreture";
    this->tempreture.query.exec("select doubleTemperatuur from temperatuur");
    this->humidity.title = "humidity";
    this->humidity.query.exec("select doubleHumidity from humidity");

    makeChart(this->tempreture);
    makeChart(this->humidity);
}

void Chart::makeChart(struct chartValues chartvalues){
    Chart::getSeries(chartvalues);

    //set chart settings
    chartvalues.chart->addSeries(chartvalues.splineSeries);
    chartvalues.chart->legend()->hide();
    chartvalues.chart->createDefaultAxes();
    chartvalues.chart->axes(Qt::Vertical).first()->setRange(lowestValue, highestValue);
    chartvalues.chart->axes(Qt::Horizontal).first()->setRange(0, i);
    chartvalues.chart->setTitle(chartvalues.title);

    //set chart visual look
    chartvalues.chartView->setRenderHint(QPainter::Antialiasing);
    chartvalues.chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}


void Chart::getSeries(struct chartValues chartvalues){
    this->lowestValue = 0;
    this->highestValue = 0;
    i=0;

    //get values from database
    while(chartvalues.query.next()){
        double value = chartvalues.query.value(0).toDouble();
        chartvalues.splineSeries->append(i, value);
        i++;

        if(value < this->lowestValue){
            this->lowestValue = value;
        }else if(value > this->highestValue){
            this->highestValue = value;
        }
    }

}
