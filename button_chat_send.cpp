/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     自定义控件 - 发送按钮
 @FileName :    button_chat_base.cpp
 @Version :     1.0
************************************************/


#include "button_chat_send.h"

Button_Chat_Send::Button_Chat_Send(QWidget *parent) : Button_Cust_Base(parent)
{
    
}

/************************************** 自定义按钮 **************************************/
// 绘图事件
void Button_Chat_Send::paintEvent(QPaintEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    
    // 绘制文字
    QPainter painter(this);
    
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
    
    // 设置画笔  
    QPen pen;
    
    // 设置画刷
    QBrush Brush;
    
    // 设定背景颜色
    QColor back_color(0 , 153 , 255);
    
    /***************************** 鼠标事件 *****************************/
    switch (this->Mode_Code) {
        case Mode_Press:        // 鼠标按下
            back_color = QColor(130, 205, 255);
        break;
        
        case Mode_Release:      // 鼠标释放
            back_color = QColor(0 , 153 , 255);
        break;
        
    }
    // 设定画笔参数
    painter.setPen(pen);
    pen.setColor(back_color);
    pen.setWidth(0);
    
    // 设置画刷参数
    Brush.setColor(back_color);
    Brush.setStyle(Qt::SolidPattern);
    
    // 设定画笔 画刷
    painter.setPen(pen);
    painter.setBrush(Brush);
    
    // 绘制边框 先绘制一个圆角矩形
    QRect rect = this->rect();
    painter.drawRoundedRect( rect , 8 , 8);
    
    /***************************** 绘制文本 图像 *****************************/
    // 设置画笔颜色
    pen.setColor(Qt::white);
    
    // 设定画笔
    painter.setPen(pen);
    
    // 设定字体
    painter.setFont(QFont("隶书" , 13));
    painter.drawText( (this->width() / 2) - 17 , (this->height() / 2) + 7 , "发送");
    
    
}

// 按下事件
void Button_Chat_Send::mousePressEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    // 设定状态码
    this->Mode_Code = Mode_Press;
    
    // 更新图像
    this->update();
    
}


// 释放事件
void Button_Chat_Send::mouseReleaseEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 设定状态码
    this->Mode_Code = Mode_Release;
    
    // 发送信号
    emit signals_click();
    
    // 更新图像
    this->update();
}


