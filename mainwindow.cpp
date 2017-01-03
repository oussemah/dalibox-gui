#include <QVBoxLayout>
#include <QProcess>

#include "mainwindow.h"
#include "InfoFrameDBusAdaptor.h"

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

    new InfoFrameDBusAdaptor((InfoFrame*)central_frame);

    /* Print the current DBus session address */
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    qDebug() << QString("Using DBus ID : ").append(env.value("DBUS_SESSION_BUS_ADDRESS", "None"));

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/DaliBoxGUI", (InfoFrame*)central_frame);
    connection.registerService("org.DaliBox.GUIInterface");

    centralWidget->show();
}

MainWindow::~MainWindow()
{
    delete centralWidget;
}
