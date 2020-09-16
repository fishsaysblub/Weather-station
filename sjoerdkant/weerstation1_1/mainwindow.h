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

    void getTampreture(QSplineSeries *series, int h);
    void getAirPresure(QSplineSeries *series);

    void update();

private slots:
    void on_textEdit_cursorPositionChanged();

    void on_textEdit_2_cursorPositionChanged();

private:
    int i;
    QChart *airPressureChart = new QChart();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
