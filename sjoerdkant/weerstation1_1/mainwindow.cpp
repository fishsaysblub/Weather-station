#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QAbstractAxis>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WeatherStation");

    //tempreture
    QSplineSeries *tempretureSeries = new QSplineSeries();
    MainWindow::getTampreture(tempretureSeries, 3);

    QChart *tempretureChart = new QChart();
    tempretureChart->addSeries(tempretureSeries);
    tempretureChart->legend()->hide();
    tempretureChart->createDefaultAxes();
    tempretureChart->axes(Qt::Vertical).first()->setRange(-10, 30);
    tempretureChart->setTitle("Tampreture");

    QChartView *tempretureChartview = new QChartView(tempretureChart);
    tempretureChartview->setRenderHint(QPainter::Antialiasing);
    tempretureChartview->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    ui->gridLayout_3->addWidget(tempretureChartview, 1, 0);

    //airPressure
    QSplineSeries *airPressureSeries = new QSplineSeries();

    MainWindow::getAirPresure(airPressureSeries);


    airPressureChart->legend()->hide();
    airPressureChart->addSeries(airPressureSeries);
    airPressureChart->createDefaultAxes();
    airPressureChart->axes(Qt::Vertical).first()->setRange(0, 50);
    airPressureChart->setTitle("AirPressure");

    QChartView *airPressureChartview = new QChartView(airPressureChart);
    airPressureChartview->setRenderHint(QPainter::Antialiasing);
    airPressureChartview->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    ui->gridLayout_3->addWidget(airPressureChartview, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getTampreture(QSplineSeries *series, int h){
    for(i = 0; i <11; i++){
        int k = (i^5)*2+h;
        series->append(i,k);
    }
}

void MainWindow::getAirPresure(QSplineSeries *series){
    for(i = 0; i <11; i++){
        int k = (i^5)*2+5;
        series->append(i,k);
    }
}

void MainWindow::on_textEdit_cursorPositionChanged()
{

}

void MainWindow::on_textEdit_2_cursorPositionChanged()
{

}
