/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     窗口 菜单
 @FileName :    widget_assist_menu.h
 @Version :     1.0
************************************************/








#ifndef WIDGET_ASSIST_MENU_H
#define WIDGET_ASSIST_MENU_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>

class Widget_Assist_Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Assist_Menu(QWidget *parent = nullptr);
    
protected:
    void paintEvent(QPaintEvent *event);
    
signals:
    
};

#endif // WIDGET_ASSIST_MENU_H
