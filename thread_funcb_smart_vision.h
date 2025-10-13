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
