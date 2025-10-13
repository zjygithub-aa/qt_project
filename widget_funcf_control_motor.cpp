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
