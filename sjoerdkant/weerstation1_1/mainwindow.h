#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getTSeries(QSplineSeries *series, int h);

    void makeChart(const QString title, QSplineSeries *series, QChart *chart, QChartView *chartView);

private:
    int i;

    QSplineSeries *tempretureSeries = new QSplineSeries();
    QChart *tempretureChart = new QChart();
    QChartView *tempretureChartview = new QChartView(tempretureChart);

    QSplineSeries *airPressureSeries = new QSplineSeries();
    QChart *airPressureChart = new QChart();
    QChartView *airPressureChartview = new QChartView(airPressureChart);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
