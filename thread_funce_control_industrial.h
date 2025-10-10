/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  工业控制
 @FileName :    thread_funca_control_industrial.h
 @Version :     1.0
************************************************/







#ifndef THREAD_FUNCE_CONTROL_INDUSTRIAL_H
#define THREAD_FUNCE_CONTROL_INDUSTRIAL_H

#include <QWidget>
#include <QThread>

class Thread_funcE_Control_industrial : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcE_Control_industrial(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCE_CONTROL_INDUSTRIAL_H
