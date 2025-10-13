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
