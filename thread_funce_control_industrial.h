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
