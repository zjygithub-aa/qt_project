#include "widget_main.h"
#include "ui_widget_main.h"

Widget_Main::Widget_Main(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_Main)
{
    ui->setupUi(this);
    
    /*************************** 1、主页面初始化设计 ***************************/
    // 1.1 窗口
    this->setWindowFlag(Qt::FramelessWindowHint);
    // 1.2 背景透明
    this->setAttribute(Qt::WA_TranslucentBackground); 
    // 1.3 固定窗口大小
    this->setFixedSize(850, 575);
    // 1.4 图标设定
    this->setWindowIcon(QIcon(":/头像"));
    
    /*************************** 2、关闭按钮 ***************************/
    // 2.1 创建关闭按钮
    this->butto_closr = new Button_Main_Close(this);
    // 2.2 设置按钮初始图像
    this->butto_closr->setPixmap(QPixmap(":/关闭按钮_蓝色"));
    // 2.3 设置按钮位置
    this->butto_closr->move(this->width() - 20 , 5);
    // 2.4 放置在页面最上面
    this->butto_closr->raise();
    
    /*************************** 3、标题设置 ***************************/
    // 3.1 创建标题
    this->Window_Title = new QLabel(this);
    // 3.2 设定文本
    this->Window_Title->setText("Echo Vision");
    // 3.3 设定字体
    this->Window_Title->setFont(QFont("华文隶书" , 13));
    // 3.4 居中显示
    this->Window_Title->setAlignment(Qt::AlignCenter);
    // 3.5 设定大小
    this->Window_Title->setFixedSize(150 , 30);
    // 3.6 移动位置
    this->Window_Title->move( (this->width() / 2) - (this->Window_Title->width() / 2) , -2 );
    // 3.7 放置在页面最上面
    this->butto_closr->raise();
    
    
    /*************************** 3、菜单设置 ***************************/
    // 3.1 设定头像位置 头像居中
    ui->label_head_img->setPixmap(QPixmap(":/img/head_img.png"));
    ui->label_head_img->setScaledContents(true);
    
    // 3.2 设定菜单
    ui->label_smart_chat->Set_Test("智能对话");
    ui->label_smart_chat->Set_Image(":/智能对话");
    
    ui->label_vision_recog->Set_Test("视觉识别");
    ui->label_vision_recog->Set_Image(":/视觉识别");
    
    ui->label_smart_home->Set_Test("智能家居");
    ui->label_smart_home->Set_Image(":/智能家居");
    
    ui->label_weather->Set_Test("天气预报");
    ui->label_weather->Set_Image(":/天气预报");
    
    ui->label_control_screen->Set_Test("工控大屏");
    ui->label_control_screen->Set_Image(":/工控大屏");
    
    ui->label_motor->Set_Test("电机控制");
    ui->label_motor->Set_Image(":/电机控制");
    
    // 3.3 连接菜单按钮信号
    connect(ui->label_smart_chat        ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    connect(ui->label_vision_recog      ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    connect(ui->label_smart_home        ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    connect(ui->label_weather           ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    connect(ui->label_control_screen    ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    connect(ui->label_motor             ,   &Button_Main_Menu::signals_click , this ,   &Widget_Main::slots_click_menu );
    
    
    /*************************** 4、页面设置 ***************************/
    // 4.1 初始化界面类
    Widget_Smart_chat         = new Widget_funcA_Smart_chat(this);              // 初始化智能对话界面类
    Widget_Smart_vision       = new Widget_funcB_Smart_vision(this);            // 初始化视觉识别界面类
    Widget_Smart_Home         = new Widget_funcC_Smart_Home(this);              // 初始化智能家居界面类
    Widget_Weather            = new Widget_funcD_Weather(this);                 // 初始化天气预报界面类
    Widget_Control_industrial = new Widget_funcE_Control_industrial(this);      // 初始化工控大屏界面类
    Widget_Control_motor      = new Widget_funcF_Control_motor(this);           // 初始化电机控制界面类
    
    
    // 4.2 插入到主页面
    ui->stackedWidget->addWidget(Widget_Smart_chat);                            // 将智能对话界面插入到 stackedWidget
    ui->stackedWidget->addWidget(Widget_Smart_vision);                          // 将视觉识别界面插入到 stackedWidget
    ui->stackedWidget->addWidget(Widget_Smart_Home);                            // 将智能家居界面插入到 stackedWidget
    ui->stackedWidget->addWidget(Widget_Weather);                               // 将天气预报界面插入到 stackedWidget
    ui->stackedWidget->addWidget(Widget_Control_industrial);                    // 将工控大屏界面插入到 stackedWidget
    ui->stackedWidget->addWidget(Widget_Control_motor);                         // 将电机控制界面插入到 stackedWidget
    
    // 设定尺寸
    Widget_Smart_chat->setFixedSize(696, 532);                                  // 设置智能对话页面尺寸
    Widget_Smart_vision->setFixedSize(696, 532);                                // 设置视觉识别页面尺寸
    Widget_Smart_Home->setFixedSize(696, 532);                                  // 设置智能家居页面尺寸
    Widget_Weather->setFixedSize(696, 532);                                     // 设置天气预报页面尺寸
    Widget_Control_industrial->setFixedSize(696, 532);                          // 设置工控大屏页面尺寸
    Widget_Control_motor->setFixedSize(696, 532);                               // 设置电机控制页面尺寸
    
}

Widget_Main::~Widget_Main()
{
    delete ui;
}



// 绘制窗口边框
void Widget_Main::paintEvent(QPaintEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    
    /*************************** 绘制背景 ***************************/
    // 背景为浅蓝色
    QPainter painter(this);
    
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);  
    
    // 设置画笔  #E4EEFF QColor(228 , 238 , 255)  1
    QPen pen;
    pen.setColor(QColor(246, 250, 254));
    pen.setWidth(0);
    
    // 设置画刷
    QBrush Brush;
    Brush.setColor(QColor(246, 250, 254));
    Brush.setStyle(Qt::SolidPattern);
    
    // 设定画笔 画刷
    painter.setPen(pen);
    painter.setBrush(Brush);
    
    // 绘制图形
    painter.drawRoundedRect(this->rect() , 12 , 12);
    
    
}


// 进入事件
void Widget_Main::enterEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
}

// 离开事件
void Widget_Main::leaveEvent(QEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
}

// 按下事件
void Widget_Main::mousePressEvent(QMouseEvent *event)
{
    Qt::MouseButton Mouse_button = event->button();
    
    // 获取左键按下的坐标
    if(Qt::LeftButton == Mouse_button)
    {
        this->Mouse_Press_Pos = event->pos();
        // 获取标题区域的位置和大小
        QRect titleRect = this->Window_Title->rect(); // 获取标题区域
        QPoint labelPos = this->Window_Title->mapFromParent(event->pos()); // 获取鼠标相对标题的位置
        
        // 判断鼠标是否在标题区域内
        if (titleRect.contains(labelPos)) {
            // 可以显示另外的文字
            this->Window_Title->setText("今天也要开心鸭");  // 你可以设置一些新的标题或者显示其他文字
        }
            
    }
    
}

// 释放事件
void Widget_Main::mouseReleaseEvent(QMouseEvent *event)
{
    // 不使用这个变量
    Q_UNUSED (event);
    Qt::MouseButton Mouse_button = event->button();
    
    // 获取左键按下的坐标
    if(Qt::LeftButton == Mouse_button)
    {
        this->Mouse_Press_Pos = event->pos();
        // 获取标题区域的位置和大小
        QRect titleRect = this->Window_Title->rect(); // 获取标题区域
        QPoint labelPos = this->Window_Title->mapFromParent(event->pos()); // 获取鼠标相对标题的位置
        
        // 判断鼠标是否在标题区域内
        if (titleRect.contains(labelPos)) {
            // 可以显示另外的文字
            this->Window_Title->setText("Echo Vision");  // 你可以设置一些新的标题或者显示其他文字
            
        } else {
        }
    }
    
}

// 移动事件
void Widget_Main::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动 窗口移动 左键触发
    if(event->buttons() == Qt::LeftButton)
    {
        // 移动窗口
        QPoint Move_pos = event->globalPos() - this->Mouse_Press_Pos;
        this->move(Move_pos);
    }
}

// 切换菜单
void Widget_Main::slots_click_menu()
{
    /*
     * 实现方法：
     *    - 如果是当前按钮点击，则切换页面，并且内部会将该按钮变换颜色；
     *    - 如果不是当前按钮，则更新状态码为 Mode_No(-1)，让按钮恢复为白色，保证按钮互斥操作。
     */
    
    // 判断是那个发出的信号
    QObject * senderobj = sender();
    
    // 智能对话
    if(senderobj != ui->label_smart_chat)
    {
        // 更新状态码 
        ui->label_smart_chat->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_SMART_CHAT);
    }
    
    // 视觉识别
    if(senderobj != ui->label_vision_recog)
    {
        // 更新状态码
        ui->label_vision_recog->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_VISION_RECOG);
    }
    
    // 智能家居
    if(senderobj != ui->label_smart_home)
    {
        // 更新状态码
        ui->label_smart_home->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_SMART_HOME);
    }
    
    // 天气预报
    if(senderobj != ui->label_weather)
    {
        // 更新状态码
        ui->label_weather->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_WEATHER);
    }
    
    // 工控大屏
    if(senderobj != ui->label_control_screen)
    {
        // 更新状态码
        ui->label_control_screen->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_CONTROL_SCREEN);
    }
    
    // 电机控制
    if(senderobj != ui->label_motor)
    {
        // 更新状态码
        ui->label_motor->update_start(Mode_No);
    }
    else
    {
        // 切换页面
        ui->stackedWidget->setCurrentIndex(PAGE_MOTOR);
    }
}
