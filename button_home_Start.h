#ifndef BUTTON_HOME_H
#define BUTTON_HOME_H

#include <QWidget>
#include <button_cust_base.h>

class Button_home_start : public Button_Cust_Base
{
    Q_OBJECT
public:
    explicit Button_home_start(QWidget *parent = nullptr);
    
    
    //    // 按下事件
    void mousePressEvent(QMouseEvent *event);
    
    void set_start(bool start);
    
protected:

    int start = false;
    
signals:
    void signals_start(bool start);
};

#endif // BUTTON_HOME_H
