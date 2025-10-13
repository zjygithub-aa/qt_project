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
