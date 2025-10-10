/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     功能窗口 工业控制
 @FileName :    widget_assist_control_industrial.h
 @Version :     1.0
************************************************/


#ifndef WIDGET_FUNCE_CONTROL_INDUSTRIAL_H
#define WIDGET_FUNCE_CONTROL_INDUSTRIAL_H

#include <QWidget>

namespace Ui {
class Widget_funcE_Control_industrial;
}

class Widget_funcE_Control_industrial : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget_funcE_Control_industrial(QWidget *parent = nullptr);
    ~Widget_funcE_Control_industrial();
    
private:
    Ui::Widget_funcE_Control_industrial *ui;
};

#endif // WIDGET_FUNCE_CONTROL_INDUSTRIAL_H
