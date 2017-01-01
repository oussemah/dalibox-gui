/*
 * Desc: A custom GPIO handler class that supports input pin status update without "direct" polling
 * Author: Oussema Harbi <oussema.harbi@altran.com>
 */

#include "qgpiohandler.h"
#include <QFile>
#include <QTextStream>

#include <QDebug>

#define GPIO_EXPORT_FILE_PATH   "/sys/class/gpio/export"
#define GPIO_UNEXPORT_FILE_PATH "/sys/class/gpio/unexport"
#define GPIO_DIR_FILE_PATH      "/sys/class/gpio/gpio%ID_HERE%/direction"
#define GPIO_VAL_FILE_PATH      "/sys/class/gpio/gpio%ID_HERE%/value"
#define GPIO_EDGE_FILE_PATH     "/sys/class/gpio/gpio%ID_HERE%/edge"

QGPIOHandler::QGPIOHandler(QObject *parent) : QObject(parent)
{
    m_watcher = new QFileSystemWatcher;

    connect (m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(pinValueUpdated(QString)));
}


QGPIOHandler::~QGPIOHandler(void)
{
    delete m_watcher;
}

int QGPIOHandler::setPinDirection(int pin, int direction)
{
    QString dir_file_path =QString(GPIO_DIR_FILE_PATH);
    dir_file_path.replace("%ID_HERE%", QString::number(pin));


    QFile file(dir_file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       qDebug() << QString("Error in direction setup of pin ").append(QString::number(pin));
        return -1;
    }

    QTextStream out(&file);
    if (direction == QGPIOHandler::DIRECTION_INPUT)
    {
        out << "in";
        QString val_file_path = GPIO_VAL_FILE_PATH;
        val_file_path.replace("%ID_HERE%", QString::number(pin));
        m_watcher->addPath(val_file_path);
        QString edge_file_path = GPIO_EDGE_FILE_PATH;
        edge_file_path.replace("%ID_HERE%", QString::number(pin));
        QFile file_edge(edge_file_path);
        if (!file_edge.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << QString("Error while enabling interrupts on input pin ").append(QString::number(pin));
            //We choose to continue working without supporting interrupts in case there is an error here !
        } else {
            QTextStream edge(&file_edge);
            edge << "both";
            file_edge.close();
        }

    } else if (direction == QGPIOHandler::DIRECTION_OUTPUT) {
        out << "out";
    } else {
        qDebug() << QString("Unrecognized pin direction value ").append(QString::number(direction));
        file.close();
        return -1;
    }

    file.close();
    return 0;
}

int QGPIOHandler::setPinValue(int pin, int value)
{
    QString val_file_path = GPIO_VAL_FILE_PATH;
    val_file_path.replace("%ID_HERE%", QString::number(pin));

    QFile file(val_file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QString("Error in value setup of pin ").append(QString::number(pin));
        return -1;
    }

    QTextStream out(&file);
    if (value == QGPIOHandler::VALUE_HIGH)
    {
        out << "1";
    } else if (value == QGPIOHandler::VALUE_LOW) {
        out << "0";
    } else {
        qDebug() << QString("Unrecognized pin value ").append(QString::number(value));
        file.close();
        return -1;
    }

    file.close();
    return 0;
}

int QGPIOHandler::readPinValue(int pin)
{
    QString val_file_path = GPIO_VAL_FILE_PATH;
    val_file_path.replace("%ID_HERE%", QString::number(pin));

    QFile file(val_file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QString("Error while reading value of pin ").append(QString::number(pin));
        return -1;
    }

    QTextStream in(&file);
    QString value;
    in >> value;
    if (value.compare("1") == 0)
    {
        file.close();
        return QGPIOHandler::VALUE_HIGH;
    } else if (value.compare("0") == 0) {
        file.close();
        return QGPIOHandler::VALUE_LOW;
    } else {
       qDebug() << QString("Unrecognized pin value ").append(value);
        file.close();
        return -1;
    }
}

int QGPIOHandler::reservePin(int pin)
{
    QFile file(GPIO_EXPORT_FILE_PATH);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QString("Error while reserving pin ").append(QString::number(pin));
        return -1;
    }

    QTextStream out(&file);
    out << pin;
    file.close();
    return 0;
}

int QGPIOHandler::freePin(int pin)
{
    QFile file(GPIO_UNEXPORT_FILE_PATH);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QString("Error while freeing pin ").append(QString::number(pin));
        return -1;
    }

    QTextStream out(&file);
    out << pin;
    file.close();
    return 0;
}

void QGPIOHandler::pinValueUpdated(const QString &path)
{
    QString copy = path;
    int pin;

    QString pinID = copy.remove("/sys/class/gpio/pio").remove("/value");
    if (pinID.at(0) == 'A')
    {
        pin = pinID.remove("A").toInt();
    } else if (pinID.at(0) == 'B')
    {
        pin = 32 + pinID.remove("B").toInt();
    } else if (pinID.at(0) == 'C')
    {
        pin = 64 + pinID.remove("C").toInt();
    } else if (pinID.at(0) == 'D')
    {
        pin = 96 + pinID.remove("D").toInt();
    } else if (pinID.at(0) == 'E')
    {
        pin = 128 + pinID.remove("E").toInt();
    }

    emit newPinValueReady(pin);
}
