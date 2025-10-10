/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     自定义控件 关闭按钮
 @FileName :    button_main_close.cpp
 @Version :     1.0
************************************************/

#include "button_main_close.h"

Button_Main_Close::Button_Main_Close(QWidget *parent) : Button_Cust_Base(parent)
{
    this->setFixedSize(15 , 15);
    this->setScaledContents(true);
    this->setPixmap(QPixmap(":/关闭按钮_蓝色"));
}

/************************************** 自定义按钮 **************************************/


// 进入事件
void Button_Main_Close::enterEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 切换图片
    this->setPixmap(QPixmap(":/关闭按钮_红色"));

}
// 离开事件
void Button_Main_Close::leaveEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 切换图片
    this->setPixmap(QPixmap(":/关闭按钮_蓝色"));
}
// 按下事件
void Button_Main_Close::mousePressEvent(QMouseEvent *event)
{
    // 左右按钮判定
    Qt::MouseButton button = event->button();
    
    // 左键
    if(button == Qt::LeftButton)
    {
        // 切换图片
        this->setPixmap(QPixmap(":/关闭按钮_灰色"));
    }
    // 右健
    else if(button == Qt::RightButton)
    {
        
    }
    // 中键
    else if(button == Qt::MidButton)
    {
        
    }
}
// 释放事件
void Button_Main_Close::mouseReleaseEvent(QMouseEvent *event)
{
    // 左右按钮判定
    Qt::MouseButton button = event->button();
    
    // 获取鼠标的当前位置
    QPoint mousePos = event->globalPos();  // 全局坐标
    
    // 获取控件在窗口中的位置
    QRect widgetRect = this->rect();
    
    // 判断鼠标是否在控件内部
    if (widgetRect.contains(this->mapFromGlobal(mousePos))) {
        // 如果鼠标仍在控件内部 ， 执行退出操作
        if (button == Qt::LeftButton) {
            // 切换图片
            this->setPixmap(QPixmap(":/关闭按钮_红色"));

            // 执行退出操作
            exit(0);
        }
    }
    // 右健
    else if(button == Qt::RightButton)
    {
        
    }
    // 中键
    else if(button == Qt::MidButton)
    {
        
    }
}


/************************************** 自定义按钮 **************************************/
