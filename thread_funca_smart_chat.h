/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  智能对话
 @FileName :    thread_funca_smart_chat.h
 @Version :     1.0
************************************************/







#ifndef THREAD_FUNCA_SMART_CHAT_H
#define THREAD_FUNCA_SMART_CHAT_H

#include <QWidget>
#include <QThread>

class Thread_funcA_Smart_chat : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcA_Smart_chat(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCA_SMART_CHAT_H
