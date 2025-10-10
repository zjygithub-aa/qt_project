/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     功能窗口 工业控制
 @FileName :    widget_funce_control_industrial.cpp
 @Version :     1.0
************************************************/


#include "widget_funce_control_industrial.h"
#include "ui_widget_funce_control_industrial.h"

Widget_funcE_Control_industrial::Widget_funcE_Control_industrial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_funcE_Control_industrial)
{
    ui->setupUi(this);
}

Widget_funcE_Control_industrial::~Widget_funcE_Control_industrial()
{
    delete ui;
}
