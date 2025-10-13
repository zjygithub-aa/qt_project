#include "button_cust_base.h"

Button_Cust_Base::Button_Cust_Base(QWidget *parent) : QLabel(parent)
{
    
}


void Button_Cust_Base::Set_Image(QString Image_path)
{
    // 设定图像
    this->M_Image = QImage(Image_path);
    // 更新图像
    this->update();
}

void Button_Cust_Base::Set_Test(QString Text)
{
    // 设定图像
    this->M_Text = Text;
    // 更新图像
    this->update();
}

void Button_Cust_Base::update_start(int Mode_Code)
{
    // 更新状态码
    this->Mode_Code = Mode_Code;
    // 更新会话
    this->update();
}

/************************************** 自定义按钮 **************************************/

//void Button_Cust_Base::paintEvent(QPaintEvent *event)
//{
//    // 不使用这个变量
//    Q_UNUSED (event);
//}

//void Button_Cust_Base::enterEvent(QEvent *event)
//{
//    // 不使用这个变量
//    Q_UNUSED (event);
//}

//void Button_Cust_Base::leaveEvent(QEvent *event)
//{
//    // 不使用这个变量
//    Q_UNUSED (event);
//}

//void Button_Cust_Base::mousePressEvent(QMouseEvent *event)
//{
//    // 不使用这个变量
//    Q_UNUSED (event);
//}

//void Button_Cust_Base::mouseReleaseEvent(QMouseEvent *event)
//{
//    // 不使用这个变量
//    Q_UNUSED (event);
//}


void Button_Cust_Base::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // 处理控件内的鼠标移动事件
        // 不让事件传递给父窗口
        event->accept();
    }
}
/************************************** 自定义按钮 **************************************/
