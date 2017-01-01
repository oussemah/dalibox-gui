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

private slots:
    void updatePinValue(int pin);
    void updateVariableValue(int value);

private:
    Ui::InfoFrame *ui;

    QGPIOHandler *m_gpio_handler;
    int m_input_pin;
};

#endif // InfoFrame_H
