/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  智能家居
 @FileName :    thread_funca_smart_home.h
 @Version :     1.0
************************************************/







#ifndef THREAD_FUNCC_SMART_HOME_H
#define THREAD_FUNCC_SMART_HOME_H

#include <QWidget>
#include <QThread>

class Thread_funcC_Smart_Home : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcC_Smart_Home(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCC_SMART_HOME_H
