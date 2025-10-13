#ifndef BUTTON_MAIN_MENU_H
#define BUTTON_MAIN_MENU_H

#include "button_cust_base.h"

// 自定义控件 标签按钮 菜单按钮

class Button_Main_Menu : public Button_Cust_Base
{
    Q_OBJECT
public:
    explicit Button_Main_Menu(QWidget *parent = nullptr);
    
protected:
    // 绘图事件
    void paintEvent(QPaintEvent *event);
    
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

#endif // BUTTON_MAIN_MENU_H
