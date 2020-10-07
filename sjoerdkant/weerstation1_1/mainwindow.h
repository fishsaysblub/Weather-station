#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QAbstractAxis>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Chart chart;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
