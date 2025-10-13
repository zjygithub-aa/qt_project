#include "widget_smart_chat_message.h"
#include <QDebug>
#include <QTextCursor>
#include <QTextCharFormat>

Widget_smart_chat_message::Widget_smart_chat_message(QWidget *parent) : QWidget(parent)
{
    /************************ 外部窗口设定 ************************/
    this->Layout = new QHBoxLayout(this);
    
    // 设定边界大小 间隔大小
    this->Layout->setContentsMargins(5 , 5 , 5 , 5 );
    this->Layout->setSpacing(5);
    
    /************************ 内部窗口设定 ************************/
    // 初始化内部窗口
    this->Left_Widget = new QWidget(this);
    this->Right_Widget = new QWidget(this);
    this->Centr_Widget = new Widget_Assist_Backdrop(this);
    
    // 初始化每个窗口的布局
    this->Left_Layout = new QVBoxLayout(this->Left_Widget);
    this->Right_Layout = new QVBoxLayout(this->Right_Widget);
    this->Centr_Layout = new QVBoxLayout(this->Centr_Widget);
    
    // 设置边界大小 间隔大小
    this->Left_Layout->setContentsMargins(5 , 5 , 5 , 5 );
    this->Left_Layout->setSpacing(5);
    
    this->Right_Layout->setContentsMargins(5 , 5 , 5 , 5 );
    this->Right_Layout->setSpacing(5);
    
    this->Centr_Layout->setContentsMargins(5 , 5 , 5 , 5 );
    this->Centr_Layout->setSpacing(5);
    
    // 设置边上两个的宽度
    this->Left_Widget->setMaximumWidth(40);
    this->Left_Widget->setMinimumWidth(40);
    
    this->Right_Widget->setMaximumWidth(40);
    this->Right_Widget->setMinimumWidth(40);
    
    // 向布局添加窗口
    this->Layout->addWidget(this->Left_Widget);
    this->Layout->addWidget(this->Centr_Widget);
    this->Layout->addWidget(this->Right_Widget);
    
    /************************ 头像、文本框、间隔器 ************************/
    
    // 标签：初始化左右两个头像标签
    this->Left_Label = new QLabel(this->Left_Widget);
    this->Right_Label = new QLabel(this->Right_Widget);
    
    
    // 标签：限制标签大小
    this->Left_Label->setFixedSize(30 , 30);
    this->Right_Label->setFixedSize(30 , 30);
    
    // 标签：设定初始头像
    this->Left_Label->setPixmap(QPixmap(":/智能对话"));
    this->Right_Label->setPixmap(QPixmap(":/头像"));
    
    // 标签：设定图像自适应
    this->Left_Label->setScaledContents(true);
    this->Right_Label->setScaledContents(true);
    
    // 间隔器：初始化
    this->Left_spacer = new QSpacerItem(10, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->Right_spacer = new QSpacerItem(10, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->Text_Label_spacer = new QSpacerItem(1000, 30 , QSizePolicy::Maximum, QSizePolicy::Expanding);
    
    // 文本框：初始化文本框
    this->TextEdit = new QTextEdit(this->Centr_Widget);
    
    // 文本框：对话框样式表
    this->TextEdit->setStyleSheet(
        "QTextEdit {"
        "   background: transparent;"         // 透明背景
        "   border: none;"                    // 去除边框
                
        "}"
    );
    
    // 文本框：自动换行
    this->TextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    
    // 文本框：设置为只读模式，禁止输入
    this->TextEdit->setReadOnly(true);
    
    /************************ 安装头像、间隔器 ************************/
    
    // 添加右边头像和弹簧   用户
    Right_Layout->addWidget(this->Right_Label);
    Right_Layout->addItem(this->Right_spacer);
    
    // 添加右边头像和弹簧    Ai
    Left_Layout->addWidget(this->Left_Label);
    Left_Layout->addItem(this->Left_spacer);
    
}

void Widget_smart_chat_message::set_Edit_Text(QString text)
{
    // 【修正】直接设置文本，而不是追加
    this->TextEdit->setText(text);
    // 创建 QFontMetrics 对象，用来获取字体和文本尺寸
    QFontMetrics metrics(QFont("楷体" , 15));
    // 获取文本的宽度（水平长度）
    this->textWidth = metrics.horizontalAdvance(text);
    QRect temp = metrics.boundingRect(text);
    this->textHeight  = temp.height();
    // 记录回车
    this->line_count = this->TextEdit->toPlainText().count('\n');
    // 计算窗口的最大宽度
    int Centr_widget_width =  this->width() - this->Left_Widget->width() - this->Right_Widget->width() - 20;
    // 【关键修复】增加对除零的保护
    if (Centr_widget_width <= 0) {
        // 如果宽度无效，先不进行尺寸计算，等待窗口布局完成后再触发
        // 或者设置一个最小默认尺寸
        this->Centr_Widget->setMinimumWidth(100);
        this->Centr_Widget->setMinimumHeight(this->textHeight + 20);
        return; // 提前退出，避免后续计算
    }
    // 文字宽度 小于 窗口最大宽度 则缩小宽度
    if(textWidth < Centr_widget_width)
    {
        // 增加间隔器
        this->Layout->insertItem(0 , this->Text_Label_spacer);
        // 设定宽度  根据文本
        this->Centr_Widget->setMinimumWidth(textWidth + 10 + 8);
        this->Centr_Widget->setMaximumWidth(textWidth + 10 + 8);
        // 设定高度  一行
        this->Centr_Widget->setMaximumHeight((textHeight + 13 + 8) * (line_count + 1));
        this->Centr_Widget->setMinimumHeight((textHeight + 13 + 8) * (line_count + 1));
        // 修改高度
        this->setMaximumHeight((textHeight + 13 + 8 + 10) * (line_count + 1));
        this->setMinimumHeight((textHeight + 13 + 8 + 10) * (line_count + 1));
    }
    else
    {
        int line_num =  (textWidth / Centr_widget_width) + 1;
        // 设定高度  多行
        this->Centr_Widget->setMaximumHeight((line_num + line_count) * (textHeight + 12 ));
        this->Centr_Widget->setMinimumHeight((line_num + line_count) * (textHeight + 12 ));
        // 修改高度
        this->setMaximumHeight((line_num + line_count) * (textHeight + 12 ) + 10);
        this->setMinimumHeight((line_num + line_count) * (textHeight + 12 ) + 10);
    }
}


void Widget_smart_chat_message::set_Send_Layout()
{
    // 发送布局
    // 隐藏 人工智能头像
    this->Left_Label->hide();
    
    // 限制右边对话框宽度 
    this->Right_Widget->setMaximumWidth(50);
    
    // 设置对话框颜色
    this->Centr_Widget->set_color(Qt::white);
    
    // 中间窗口放置 文本框
    this->Centr_Layout->addWidget(this->TextEdit);
    
}

void Widget_smart_chat_message::set_Recv_Layout()
{
    // 接收布局
    // 隐藏 用户头像
    this->Right_Label->hide();
    // 限制左边对话框宽度
    this->Left_Widget->setMaximumWidth(50);
    // 设置对话框颜色 (例如，一个浅灰色)
    this->Centr_Widget->set_color(QColor(240, 240, 240)); // 使用一个灰色背景
    // 【关键】将文本框添加到中间窗口的布局中
    this->Centr_Layout->addWidget(this->TextEdit);
}
