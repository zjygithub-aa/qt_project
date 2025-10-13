#ifndef THREAD_FUNCF_CONTROL_MOTOR_H
#define THREAD_FUNCF_CONTROL_MOTOR_H

#include <QWidget>
#include <QThread>

class Thread_funcF_Control_motor : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcF_Control_motor(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCF_CONTROL_MOTOR_H
