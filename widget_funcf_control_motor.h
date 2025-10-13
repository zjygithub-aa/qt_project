#ifndef WIDGET_FUNCF_CONTROL_MOTOR_H
#define WIDGET_FUNCF_CONTROL_MOTOR_H

#include <QWidget>

namespace Ui {
class Widget_funcF_Control_motor;
}

class Widget_funcF_Control_motor : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget_funcF_Control_motor(QWidget *parent = nullptr);
    ~Widget_funcF_Control_motor();
    
private:
    Ui::Widget_funcF_Control_motor *ui;
};

#endif // WIDGET_FUNCF_CONTROL_MOTOR_H
