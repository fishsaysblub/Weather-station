#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \class MainWindow
 * \brief The MainWindow class
 *
 * A automaticly generated class to create the main window.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

private:
    Chart chart;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
