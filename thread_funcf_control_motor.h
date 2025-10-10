/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  电机控制
 @FileName :    thread_funca_control_motor.h
 @Version :     1.0
************************************************/







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
