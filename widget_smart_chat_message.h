/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     自定义窗口 智能对话窗口
 @FileName :    widget_assist_control_message.h
 @Version :     1.0
************************************************/


#ifndef WIDGET_SMART_CHAT_MESSAGE_H
#define WIDGET_SMART_CHAT_MESSAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>

#include <widget_assist_backdrop.h>

// 构建一个智能对话的对话框类

class Widget_smart_chat_message : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_smart_chat_message(QWidget *parent = nullptr);
    
    
public:
    // 设置显示框的内容
    void set_Edit_Text(QString text);
    
    // 发送布局
    void set_Send_Layout();
    // 接收布局
    void set_Recv_Layout();
    
protected:
    // 创建三个窗口
    QWidget * Left_Widget;                      // 左边   垂直
    QWidget * Right_Widget;                     // 右边   垂直
    Widget_Assist_Backdrop * Centr_Widget;      // 中间   垂直
    
    
    // 左右两个头像标签
    QLabel * Left_Label;        // 左边头像
    QLabel * Right_Label;       // 右边头像
    
    // 中间显示框
    QTextEdit * TextEdit;
    
    // 布局
    QBoxLayout * Layout;
    QBoxLayout * Left_Layout;      // 左边窗口布局
    QBoxLayout * Right_Layout;     // 右边窗口布局
    QBoxLayout * Centr_Layout;     // 中间窗口布局
    
    // 弹簧
    QSpacerItem * Left_spacer;          // 左边弹簧
    QSpacerItem * Right_spacer;         // 右边弹簧
    
    
    QSpacerItem * Text_Label_spacer;    // 文本框到标签的间隔器
    
    
    // 文本 基础宽度 和 基础高度  换行数量
    int textWidth = 0;
    int textHeight = 0;
    int line_count = 0;
    
signals:
    
};

#endif // WIDGET_SMART_CHAT_MESSAGE_H
