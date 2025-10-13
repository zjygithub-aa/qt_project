#include "button_main_menu.h"

Button_Main_Menu::Button_Main_Menu(QWidget *parent) : Button_Cust_Base(parent)
{
    // 初始化标签
    this->setFixedSize(QSize(120 , 30));
    
    this->M_Image = QImage(":/未定义菜单");
    
    this->M_Text = "还未设置";
}


/************************************** 自定义按钮 **************************************/
// 绘图事件
void Button_Main_Menu::paintEvent(QPaintEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 绘制文字
    QPainter painter(this);
    
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
    
    // 设置画笔
    QPen pen;
    
    // 设置画刷
    QBrush Brush;
    
    /***************************** 鼠标事件 *****************************/
    switch (this->Mode_Code) {
        case Mode_enter:    // 鼠标进入
        {
            // 设定画笔参数
            painter.setPen(pen);
            pen.setColor(QColor(107 , 194 , 252));
            pen.setWidth(0);
            
            // 设置画刷参数
            Brush.setColor(QColor(107 , 194 , 252));
            Brush.setStyle(Qt::SolidPattern);
            
            // 设定画笔 画刷
            painter.setPen(pen);
            painter.setBrush(Brush);
            
            // 绘制边框 先绘制一个圆角矩形
            QRect rect = this->rect();
            painter.drawRoundedRect( rect , 8 , 8);
            
            // 一边不需要圆角
            rect.setX(rect.x() + rect.width() - 30);
            rect.setWidth(30);
            painter.drawRect(rect );
            
        }
        
        break;
        case Mode_leave:    // 鼠标离开
        {
            
            
        }
        break;
        case Mode_Press:    // 鼠标按下
        {
            
            // 设定画笔参数
            painter.setPen(pen);
            pen.setColor(QColor(163 , 216 , 251));
            pen.setWidth(0);
            
            // 设置画刷参数
            Brush.setColor(QColor(163 , 216 , 251));
            Brush.setStyle(Qt::SolidPattern);
            
            // 设定画笔 画刷
            painter.setPen(pen);
            painter.setBrush(Brush);
            
            // 绘制边框 先绘制一个圆角矩形
            QRect rect = this->rect();
            painter.drawRoundedRect( rect , 8 , 8);
            
            // 一边不需要圆角
            rect.setX(rect.x() + rect.width() - 30);
            rect.setWidth(30);
            painter.drawRect(rect );
            
        }
        break;
        
        case Mode_Release:    // 鼠标按下
            
        break;
        
    }
    
    /***************************** 绘制文本 图像 *****************************/
    // 设置画笔颜色
    pen.setColor(Qt::white);
    
    // 设定画笔
    painter.setPen(pen);
    
    // 设定字体
    painter.setFont(QFont("隶书" , 13));
    painter.drawText( 40 , 22 , this->M_Text);
    
    // 设置图像
    QImage image = this->M_Image.scaled(27 , 27);
    painter.drawImage(3 , 1, image);
}
// 进入事件
void Button_Main_Menu::enterEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 如果为按下状态 则不设定状态码
    if(this->Mode_Code == Mode_Press)
    {
        return ;
    }
    
    // 设定状态码
    this->Mode_Code = Mode_enter;
    
    // 更新图像
    this->update();
}
// 离开事件
void Button_Main_Menu::leaveEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 如果为按下状态 则不设定状态码
    if(this->Mode_Code == Mode_Press)
    {
        return ;
    }
    
    // 设定状态码
    this->Mode_Code = Mode_leave;
    
    // 更新图像
    this->update();
}
// 按下事件
void Button_Main_Menu::mousePressEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 设定状态码
    this->Mode_Code = Mode_Press;
    
    // 发送信号
    emit signals_click();
    
    // 更新图像
    this->update();
}
// 释放
void Button_Main_Menu::mouseReleaseEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    // 如果为按下状态 则不设定状态码
    if(this->Mode_Code == Mode_Press)
    {
        return ;
    }
    
    // 设定状态码
    this->Mode_Code = Mode_Press;
    
    // 更新图像
    this->update();
}

/************************************** 自定义按钮 **************************************/

