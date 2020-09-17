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

    makeChart("tempreture", tempretureSeries, tempretureChart, tempretureChartview);
    makeChart("Humidity", HumiditySeries, HumidityChart, HumidityChartview);

    ui->gridLayout_3->addWidget(tempretureChartview, 1, 0);
    ui->gridLayout_3->addWidget(HumidityChartview, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeChart(const QString title, QSplineSeries *series, QChart *chart, QChartView *chartView){
    MainWindow::getSeries(series, 0);

    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-10, 30);
    chart->axes(Qt::Horizontal).first()->setRange(0, 8);
    chart->setTitle(title);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}

void MainWindow::getSeries(QSplineSeries *series, int h){
    for(i = 0; i <7; i++){
        int k = (i^5)*2+h;
        series->append(i+1,k);
    }
}
