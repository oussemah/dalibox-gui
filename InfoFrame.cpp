#include "InfoFrame.h"
#include "ui_InfoFrame.h"

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <QNetworkInterface>

static const QString led_icons[]    = { ":images/led_off.png", ":images/led_on.png"};

#define OFF 0
#define ON 1

InfoFrame::InfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InfoFrame)
{
    //Setup GPIO
    m_gpio_handler = new QGPIOHandler;

    m_input_pin = 40;
    m_gpio_handler->reservePin(m_input_pin);
    m_gpio_handler->setPinDirection(m_input_pin, QGPIOHandler::DIRECTION_INPUT);

    switch_status = OFF;

    setFixedHeight(400);
    ui->setupUi(this);

    connect (m_gpio_handler, SIGNAL(newPinValueReady(int)), this, SLOT(updatePinValue(int)));

    //Display the public IP of the DaliBox
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    for(int nIter=0; nIter<list.count(); nIter++)
    {
        //if(list[nIter].flags() & QNetworkInterface::IsPointToPoint)
         if (list[nIter].addressEntries().size() > 0 && list[nIter].addressEntries()[0].ip().protocol() == QAbstractSocket::IPv4Protocol )
         ui->ipAddress->setText(list[nIter].addressEntries()[0].ip().toString());
    }

    show();
}

InfoFrame::~InfoFrame()
{
    m_gpio_handler->freePin(m_input_pin);
    delete ui;
}


void InfoFrame::updatePinValue(int pin){
    int new_value = m_gpio_handler->readPinValue(pin);
        ui->label->setPixmap(QPixmap(led_icons[new_value]));
}

//Method to be called usin DBus
void InfoFrame::updateVariableValue(int value)
{
    ui->value->setText(QString::number(value));
}
