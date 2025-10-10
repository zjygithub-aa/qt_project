/***********************************************
 @Name :        小谭老师
 @Time :        2025-2-22
 @Email :       tan.zhipeng@outlook.com
 @Comment :     功能窗口 智能视觉
 @FileName :    widget_funcb_smart_vision.h
 @Version :     1.0
************************************************/

#ifndef WIDGET_FUNCB_SMART_VISION_H
#define WIDGET_FUNCB_SMART_VISION_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Widget_funcB_Smart_vision;
}

class Widget_funcB_Smart_vision : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_funcB_Smart_vision(QWidget *parent = nullptr);
    ~Widget_funcB_Smart_vision();

private slots:
    void on_get_picture_clicked();              // 选择图片
    void on_send_clicked();                     // 开始识别
    void on_model_friut_clicked();              // 模式：水果识别
    void on_model_people_clicked();             // 模式：人物识别
    void on_model_animal_clicked();             // 模式：动物识别
    void on_model_car_clicked();                // 模式：车辆识别
    void on_model_color_clicked();              // 模式：颜色识别
    void onReplyFinished(QNetworkReply *reply); // 网络请求返回回调

private:
    void getAccessToken();                      // 获取百度 AccessToken
    void recognizeImage(const QString &path);   // 执行识别
    QString getApiUrlByModel() const;           // 根据模式返回不同 API 地址

private:
    Ui::Widget_funcB_Smart_vision *ui;
    QNetworkAccessManager *manager;             // 网络请求管理器
    QString accessToken;                        // 百度 AccessToken
    QString currentImagePath;                   // 当前选择图片路径
    QString currentModel;                       // 当前识别模式
};

#endif // WIDGET_FUNCB_SMART_VISION_H
