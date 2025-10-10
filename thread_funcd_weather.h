/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     线程  天气预报
 @FileName :    thread_funca_weather.h
 @Version :     1.0
************************************************/







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
