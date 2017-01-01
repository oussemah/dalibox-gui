#include <QVBoxLayout>
#include <QTextStream>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setStyleSheet("QMainWindow {background: url(:/images/background.png) }");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setFixedSize(800,480);

    centralWidget = new QWidget(this);
    centralWidget->setBaseSize(800,480);
    central_frame = new InfoFrame(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(central_frame);
    centralWidget->setLayout(layout);
    
    this->setCentralWidget(centralWidget);

    centralWidget->show();

}

MainWindow::~MainWindow()
{
    delete centralWidget;
}
