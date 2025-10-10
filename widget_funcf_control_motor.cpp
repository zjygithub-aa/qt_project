/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     功能窗口 电机控制
 @FileName :    widget_funcf_control_motor.cpp
 @Version :     1.0
************************************************/

#include "widget_funcf_control_motor.h"
#include "ui_widget_funcf_control_motor.h"

Widget_funcF_Control_motor::Widget_funcF_Control_motor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_funcF_Control_motor)
{
    ui->setupUi(this);
}

Widget_funcF_Control_motor::~Widget_funcF_Control_motor()
{
    delete ui;
}
