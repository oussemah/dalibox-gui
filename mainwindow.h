#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "InfoFrame.h"
#include "qcustomplot.h"
#include "QTimer"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void realtimeDataSlot();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;

    QCustomPlot *central_frame;
    QTimer dataTimer;

};

#endif // MAINWINDOW_H
