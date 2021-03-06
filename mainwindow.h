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
    void ShowReadings();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;

    QFrame      *infoFrame;
    QCustomPlot *central_frame;
    QTimer dataTimer;

};

#endif // MAINWINDOW_H
