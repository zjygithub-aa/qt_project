/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     窗口 背景
 @FileName :    widget_assist_backdrop.cpp
 @Version :     1.0
************************************************/



#include "widget_assist_backdrop.h"

Widget_Assist_Backdrop::Widget_Assist_Backdrop(QWidget *parent) : QWidget(parent)
{
    // 设定默认颜色
    color = QColor (204, 235, 255);
}

void Widget_Assist_Backdrop::set_color(QColor color)
{
    this->color = color;
}


void Widget_Assist_Backdrop::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    // 创建 QPainter 对象
    QPainter painter(this);
    
    // 启用抗锯齿效果，使绘制更加平滑
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔颜色和宽度
    QPen pen;
    pen.setColor(this->color);  // 设置边框颜色为黑色
    pen.setWidth(0);  // 设置边框宽度
    painter.setPen(pen);
    
    // 设置画刷颜色
    QBrush brush;
    brush.setColor(this->color);  // 设置填充颜色为浅蓝色
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    
    // 获取控件的矩形区域
    QRect rect = this->rect();
    
    // 绘制圆角矩形，rect 是控件的区域，设置圆角半径为 15
    painter.drawRoundedRect(rect, 15, 15);
}
