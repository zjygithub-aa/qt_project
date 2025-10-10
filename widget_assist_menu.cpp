/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     窗口 菜单
 @FileName :    widget_assist_menu.cpp
 @Version :     1.0
************************************************/


#include "widget_assist_menu.h"

Widget_Assist_Menu::Widget_Assist_Menu(QWidget *parent) : QWidget(parent)
{
    
}

void Widget_Assist_Menu::paintEvent(QPaintEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 背景为浅蓝色
    QPainter painter(this);
    
    // 设置画笔  #E4EEFF QColor(228 , 238 , 255)  1
    QPen pen;
    pen.setColor(QColor(0 , 153 , 255));
    pen.setWidth(1);
    
    // 设置画刷
    QBrush Brush;
    Brush.setColor(QColor(0 , 153 , 255));
    Brush.setStyle(Qt::SolidPattern);
    
    // 设定画笔 画刷
    painter.setPen(pen);
    painter.setBrush(Brush);
    
    // 绘制图形
    painter.drawRoundedRect(this->rect() , 15 , 15);
}
