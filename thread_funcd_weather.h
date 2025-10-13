#ifndef THREAD_FUNCD_WEATHER_H
#define THREAD_FUNCD_WEATHER_H

#include <QWidget>
#include <QThread>

class Thread_funcD_Weather : public QThread
{
    Q_OBJECT
public:
    explicit Thread_funcD_Weather(QWidget *parent = nullptr);
    
signals:
    
};

#endif // THREAD_FUNCD_WEATHER_H
