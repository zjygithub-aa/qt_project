/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     窗口 背景
 @FileName :    widget_assist_backdrop.h
 @Version :     1.0
************************************************/








#ifndef WIDGET_ASSIST_BACKDROP_H
#define WIDGET_ASSIST_BACKDROP_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>


class Widget_Assist_Backdrop : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Assist_Backdrop(QWidget *parent = nullptr);
public:
    // 设置颜色
    void set_color(QColor color);
// 绘图事件
protected:
    
    void paintEvent(QPaintEvent *event);
    
protected:
    
    QColor color;
signals:
    
};

#endif // WIDGET_ASSIST_BACKDROP_H

