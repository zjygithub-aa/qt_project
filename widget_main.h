/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     主窗口
 @FileName :    widget_main.h
 @Version :     1.0
************************************************/



#ifndef WIDGET_MAIN_H
#define WIDGET_MAIN_H

#include <Qt>
#include <QDebug>
#include <QWidget>

#include <QMouseEvent>

#include <QLabel>
#include <QImage>
#include <QPixmap>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QColor>

#include "button_main_close.h"
#include "button_main_menu.h"

// 界面类
#include <widget_funca_smart_chat.h>
#include <widget_funcb_smart_vision.h>
#include <widget_funcc_smart_home.h>
#include <widget_funcd_weather.h>
#include <widget_funce_control_industrial.h>
#include <widget_funcf_control_motor.h>

// page 页面编号
#define PAGE_SMART_CHAT         0           // 智能对话
#define PAGE_VISION_RECOG       1           // 视觉识别
#define PAGE_SMART_HOME         2           // 智能家居
#define PAGE_WEATHER            3           // 天气预报
#define PAGE_CONTROL_SCREEN     4           // 工控大屏
#define PAGE_MOTOR              5           // 电机控制


QT_BEGIN_NAMESPACE
namespace Ui { class Widget_Main; }
QT_END_NAMESPACE

class Widget_Main : public QWidget
{
    Q_OBJECT
    
public:
    Widget_Main(QWidget *parent = nullptr);
    ~Widget_Main();

protected:
    // 绘图事件
    void paintEvent(QPaintEvent *event);
    
    // 进入事件
    void enterEvent(QEvent *event);
    
    // 离开事件
    void leaveEvent(QEvent *event);
    
    // 按下事件
    void mousePressEvent(QMouseEvent *event);
    
    // 释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    
    // 移动事件
    void mouseMoveEvent(QMouseEvent *event);
    
    
protected:
    // 自定义控件
    // 关闭按钮
    Button_Main_Close * butto_closr;
    
    // 标题
    QLabel * Window_Title;
    
    // 页面类
    Widget_funcA_Smart_chat             *       Widget_Smart_chat;              // 智能对话
    Widget_funcB_Smart_vision           *       Widget_Smart_vision;            // 视觉识别
    Widget_funcC_Smart_Home             *       Widget_Smart_Home;              // 智能家居
    Widget_funcD_Weather                *       Widget_Weather;                 // 天气预报
    Widget_funcE_Control_industrial     *       Widget_Control_industrial;      // 工控大屏
    Widget_funcF_Control_motor          *       Widget_Control_motor;           // 电机控制
    
protected:
    QPoint Mouse_Press_Pos;
    
    
protected slots:
    void slots_click_menu();
    
private:
    Ui::Widget_Main *ui;
};
#endif // WIDGET_MAIN_H
