#ifndef BUTTON_MAIN_CLOSE_H
#define BUTTON_MAIN_CLOSE_H

#include "button_cust_base.h"

// 自定义控件 便签按钮 关闭按钮

class Button_Main_Close : public Button_Cust_Base
{
    Q_OBJECT
public:
    explicit Button_Main_Close(QWidget *parent = nullptr);
    
protected:
    
    // 进入事件
    void enterEvent(QEvent *event);
    
    // 离开事件
    void leaveEvent(QEvent *event);
    
    // 按下事件
    void mousePressEvent(QMouseEvent *event);
    
    // 释放事件
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    
    
};

#endif // BUTTON_MAIN_CLOSE_H
