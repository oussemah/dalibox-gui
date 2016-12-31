#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "InfoFrame.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;

    QFrame *central_frame;

};

#endif // MAINWINDOW_H
