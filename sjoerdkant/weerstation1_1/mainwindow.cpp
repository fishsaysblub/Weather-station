#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WeatherStation");

    //add charts to ui
    ui->gridLayout_3->addWidget(this->chart.tempreture.chartView, 1, 0);
    ui->gridLayout_3->addWidget(this->chart.humidity.chartView, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
