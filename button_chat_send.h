/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     自定义控件 - 发送按钮
 @FileName :    button_chat_base.h
 @Version :     1.0
************************************************/



#ifndef BUTTON_CHAT_SEND_H
#define BUTTON_CHAT_SEND_H

#include "button_cust_base.h"


class Button_Chat_Send : public Button_Cust_Base
{
    Q_OBJECT
public:
    explicit Button_Chat_Send(QWidget *parent = nullptr);
    
protected:
    // 绘图事件
    void paintEvent(QPaintEvent *event);
    
    // 按下事件
    void mousePressEvent(QMouseEvent *event);
    
    // 释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    

    
signals:
    
    
};

#endif // BUTTON_CHAT_SEND_H
