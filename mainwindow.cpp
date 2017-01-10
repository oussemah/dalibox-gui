#include <QVBoxLayout>
#include <QProcess>

#include "mainwindow.h"
#include "InfoFrameDBusAdaptor.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setStyleSheet("QMainWindow {background: url(:/images/background.png) }");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setFixedSize(800,480);

    centralWidget = new QWidget(this);
    centralWidget->setBaseSize(800,480);
#if 0
    central_frame = new InfoFrame(centralWidget);
#else
    central_frame = new QCustomPlot(centralWidget);

    QCustomPlot *customPlot = central_frame;

    central_frame->addGraph(); // blue line
      central_frame->graph(0)->setPen(QPen(QColor(40, 110, 255)));
      central_frame->addGraph(); // red line
      central_frame->graph(1)->setPen(QPen(QColor(255, 110, 40)));

      QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
      timeTicker->setTimeFormat("%h:%m:%s");
      central_frame->xAxis->setTicker(timeTicker);
      central_frame->axisRect()->setupFullAxesBox();
      central_frame->yAxis->setRange(-400, 400);

      // make left and bottom axes transfer their ranges to right and top axes:
      connect(central_frame->xAxis, SIGNAL(rangeChanged(QCPRange)), central_frame->xAxis2, SLOT(setRange(QCPRange)));
      connect(central_frame->yAxis, SIGNAL(rangeChanged(QCPRange)), central_frame->yAxis2, SLOT(setRange(QCPRange)));

      // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
      connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
      dataTimer.start(0); // Interval 0 means to refresh as fast as possible

#endif

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

void MainWindow::realtimeDataSlot(int voltage1, int voltage 2)
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    central_frame->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843) * 400);
    central_frame->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364) * 400);
    // rescale value (vertical) axis to fit the current data:
    central_frame->graph(0)->rescaleValueAxis();
    central_frame->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  central_frame->xAxis->setRange(key, 8, Qt::AlignRight);
  central_frame->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    /*statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(central_frame->graph(0)->data()->size()+central_frame->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;*/
  }
}
