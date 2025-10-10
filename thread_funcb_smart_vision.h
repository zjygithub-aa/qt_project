/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  智能识别
 @FileName :    thread_funca_smart_vision.h
 @Version :     1.0
************************************************/







#ifndef THREAD_FUNCB_SMART_VISION_H
#define THREAD_FUNCB_SMART_VISION_H

#include <QWidget>
#include <QThread>

class Thread_funcB_Smart_vision : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcB_Smart_vision(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCB_SMART_VISION_H
