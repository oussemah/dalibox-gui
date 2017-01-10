#ifndef InfoFrame_H
#define InfoFrame_H

#include <QFrame>

#include "qgpiohandler.h"

namespace Ui {
class InfoFrame;
}

class InfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit InfoFrame(QWidget *parent = 0);
    ~InfoFrame();

public slots:
    void updatePinValue(int pin);
    void updateVariableValue(int value);
    void showIp();

private:
    Ui::InfoFrame *ui;

    QGPIOHandler *m_gpio_handler;
    int m_input_pin;

    int tmpWidth, tmpHeight;
};

#endif // InfoFrame_H
