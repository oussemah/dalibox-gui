#include "InfoFrame.h"
#include "ui_InfoFrame.h"

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <QNetworkInterface>
#include <QDebug>

#include <QTimer>
#include <QPropertyAnimation>

static const QString led_icons[]    = { ":images/led_off.png", ":images/led_on.png"};

#define OFF 0
#define ON 1

InfoFrame::InfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InfoFrame)
{
    ui->setupUi(this);
    qDebug() << "Setting up GPIO\n";
    //Setup GPIO
    m_gpio_handler = new QGPIOHandler;

    m_input_pin = 40;
    m_gpio_handler->reservePin(m_input_pin);
    m_gpio_handler->setPinDirection(m_input_pin, QGPIOHandler::DIRECTION_INPUT);

    connect (m_gpio_handler, SIGNAL(newPinValueReady(int)), this, SLOT(updatePinValue(int)));

    qDebug() << "Fetching IP address\n";
    //Display the public IP of the DaliBox
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    for(int nIter=0; nIter<list.count(); nIter++)
    {
         if(list[nIter].flags() & QNetworkInterface::IsPointToPoint)
         	if (list[nIter].addressEntries().size() > 0 && list[nIter].addressEntries()[0].ip().protocol() == QAbstractSocket::IPv4Protocol )
                ui->ipAddress_2->setText(list[nIter].addressEntries()[0].ip().toString());
    }

    ui->logo_dalibox->setGeometry(QRect(0,0,0,0));
    ui->ipAddress_2->setGeometry(QRect(300,500,200,40));
    show();

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    this->setSizeIncrement(4,4);
    QPropertyAnimation *m_animation = new QPropertyAnimation(ui->logo, "geometry");
    m_animation->setDirection(QPropertyAnimation::Forward);
    m_animation->setDuration(1000);
    m_animation->setStartValue(QRect(110,80,550,200));
    m_animation->setEndValue(QRect(70,30,200,90));
    QPropertyAnimation *m_animation_dalibox = new QPropertyAnimation(ui->logo_dalibox, "geometry");
    m_animation_dalibox->setDirection(QPropertyAnimation::Forward);
    m_animation_dalibox->setDuration(1000);
    m_animation_dalibox->setStartValue(QRect(660,170,0,35));
    m_animation_dalibox->setEndValue(QRect(160,120,500,160));
    m_animation->start();
    connect(m_animation_dalibox, SIGNAL(finished()), this, SLOT(showIp()));
    m_animation_dalibox->start();

}

InfoFrame::~InfoFrame()
{
    m_gpio_handler->freePin(m_input_pin);
    delete ui;
}


void InfoFrame::updatePinValue(int pin){
    int new_value = m_gpio_handler->readPinValue(pin);
      // ui->label->setPixmap(QPixmap(led_icons[new_value]));
}

//Method to be called usin DBus
void InfoFrame::updateVariableValue(int value)
{
   // ui->value->setText(QString::number(value));
}

void InfoFrame::showIp()
{
    QPropertyAnimation *m_animation_ip = new QPropertyAnimation(ui->ipAddress_2, "geometry");
    m_animation_ip->setDirection(QPropertyAnimation::Forward);
    m_animation_ip->setDuration(1000);
    m_animation_ip->setStartValue(QRect(300,500,200,40));
    m_animation_ip->setEndValue(QRect(300,350,200,40));
    m_animation_ip->start();
}
