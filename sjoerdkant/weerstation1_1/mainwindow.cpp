#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WeatherStation");

    //add charts to ui
    ui->gridLayout_tempreture->addWidget(this->chart.chart_temperature.chartView);
    ui->gridLayout_humidity->addWidget(this->chart.chart_humidity.chartView);
    ui->gridLayout_Light->addWidget(this->chart.chart_light.chartView);

    //update label_last_updated
    ui->label_last_updated->setText(QVariant(chart.lastUpdated()).toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    //update charts
    chart.updateSeries(chart.chart_temperature, position * 60);
    chart.updateSeries(chart.chart_humidity,   position * 60);
    chart.updateSeries(chart.chart_light,      position * 60);

    //update labels
    ui->label_hours->setText(QStringLiteral("last %1 hours").arg(position));
    ui->label_last_updated->setText(QVariant(chart.lastUpdated()).toString());
}
