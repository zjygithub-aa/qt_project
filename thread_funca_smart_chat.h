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
