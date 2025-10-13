#include "button_home_Start.h"

Button_home_start::Button_home_start(QWidget *parent) : Button_Cust_Base(parent)
{
    // 设定大小
    this->setFixedSize(40 , 40);
    // 启动自适应
    this->setScaledContents(true);
    // 初始化图片
    this->setPixmap(QPixmap(":/状态按钮_关"));
    // 初始化状态
    this->start = false;
}

void Button_home_start::mousePressEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 当按钮按下 则切换状态
    if(this->start == true)
    {
        // 切换状态
        this->start = false;
        // 切换图片
        this->setPixmap(QPixmap(":/状态按钮_关"));
    }
    else
    {
        // 切换状态
        this->start = true;
        // 切换图片
        this->setPixmap(QPixmap(":/状态按钮_开"));
    }
    
    // 发送信号
    emit signals_start(start);
}

void Button_home_start::set_start(bool start)
{
    // 当按钮按下 则切换状态
    if(start == false)
    {
        // 切换状态
        this->start = start;
        // 切换图片
        this->setPixmap(QPixmap(":/状态按钮_关"));
    }
    else
    {
        // 切换状态
        this->start = start;
        // 切换图片
        this->setPixmap(QPixmap(":/状态按钮_开"));
    }
}

