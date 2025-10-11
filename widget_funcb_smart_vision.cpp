#include "widget_funcb_smart_vision.h"
#include "ui_widget_funcb_smart_vision.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QDebug>

Widget_funcB_Smart_vision::Widget_funcB_Smart_vision(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_funcB_Smart_vision)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    // 默认模式：通用物体识别
    currentModel = "general";

    // 获取 AccessToken
    getAccessToken();

    connect(manager, &QNetworkAccessManager::finished,
            this, &Widget_funcB_Smart_vision::onReplyFinished);
}

Widget_funcB_Smart_vision::~Widget_funcB_Smart_vision()
{
    delete ui;
}

void Widget_funcB_Smart_vision::getAccessToken()
{
    QString apiKey = "cCnUHURkrLavirByqAhUkU43";
    QString secretKey = "0LrTlH9qksraSUGi0yNI5ERc3H8McqaZ";

    QString tokenUrl = QString(
        "https://aip.baidubce.com/oauth/2.0/token"
        "?grant_type=client_credentials&client_id=%1&client_secret=%2"
    ).arg(apiKey).arg(secretKey);

    // ✅ 正确写法：必须加上等号来定义对象
    QNetworkRequest request = QNetworkRequest(QUrl(tokenUrl));

    // ✅ 然后调用 GET
    manager->get(request);
}


void Widget_funcB_Smart_vision::on_get_picture_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg)");
    if (path.isEmpty()) return;

    currentImagePath = path;

    // 显示图片
    QPixmap pix(path);
    if (pix.isNull()) {
        QMessageBox::warning(this, "错误", "无法加载图片");
        return;
    }

    QLabel *imgLabel = new QLabel(ui->widget_Img);
    imgLabel->setPixmap(pix.scaled(ui->widget_Img->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setGeometry(ui->widget_Img->rect());
    imgLabel->show();

    ui->Label_result->setText("图片已加载，准备识别...");
}

void Widget_funcB_Smart_vision::on_send_clicked()
{
    if (accessToken.isEmpty()) {
        QMessageBox::warning(this, "错误", "AccessToken 未准备好，请稍后重试");
        return;
    }
    if (currentImagePath.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先选择图片");
        return;
    }
    recognizeImage(currentImagePath);
}

QString Widget_funcB_Smart_vision::getApiUrlByModel() const
{
    QString baseUrl;
    if (currentModel == "friut" || currentModel == "general")
        baseUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general";
    else if (currentModel == "people")
        baseUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general";
    else if (currentModel == "animal")
        baseUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general";
    else if (currentModel == "car")
        baseUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general";
    else if (currentModel == "color")
        baseUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general";
    return baseUrl + "?access_token=" + accessToken;
}

void Widget_funcB_Smart_vision::recognizeImage(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误", "无法读取图片文件");
        return;
    }

    QByteArray imgData = file.readAll();
    file.close();

    QString base64 = imgData.toBase64();
    QByteArray postData = "image=" + QUrl::toPercentEncoding(base64);

    QString url = getApiUrlByModel();
    if (url.isEmpty()) {
        QMessageBox::warning(this, "错误", "识别接口URL错误");
        return;
    }

    QNetworkRequest request = QNetworkRequest(QUrl(url));  // ✅ 绝对正确
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    manager->post(request, postData);

    ui->Label_result->setText("识别中，请稍候...");
}

void Widget_funcB_Smart_vision::onReplyFinished(QNetworkReply *reply)
{
    QByteArray res = reply->readAll();
    reply->deleteLater();

    // 判断是否是 AccessToken
    if (res.contains("access_token")) {
        QJsonDocument doc = QJsonDocument::fromJson(res);
        accessToken = doc["access_token"].toString();
        qDebug() << "AccessToken 获取成功：" << accessToken;
        return;
    }

    // 识别结果处理
    QJsonDocument doc = QJsonDocument::fromJson(res);
    QString resultText = "识别结果：\n";

    if (doc.isObject()) {
        if (doc.object().contains("result")) {
            QJsonArray arr = doc["result"].toArray();
            for (const QJsonValue &v : arr) {
                QJsonObject obj = v.toObject();
                QString name = obj["keyword"].toString();
                double score = obj["score"].toDouble();
                resultText += QString("• %1 (置信度: %2)\n").arg(name).arg(score, 0, 'f', 2);
            }
        } else if (doc.object().contains("color_result")) {
            resultText += doc["color_result"].toObject()["color"].toString();
        } else {
            resultText = "无法解析返回结果";
        }
    }
    ui->Label_result->setText(resultText);
}

// 模式切换按钮
void Widget_funcB_Smart_vision::on_model_friut_clicked()  { currentModel = "friut";  ui->Label_result->setText("模式：水果识别"); }
void Widget_funcB_Smart_vision::on_model_people_clicked() { currentModel = "people"; ui->Label_result->setText("模式：人物属性识别"); }
void Widget_funcB_Smart_vision::on_model_animal_clicked() { currentModel = "animal"; ui->Label_result->setText("模式：动物识别"); }
void Widget_funcB_Smart_vision::on_model_car_clicked()    { currentModel = "car";    ui->Label_result->setText("模式：车辆识别"); }
void Widget_funcB_Smart_vision::on_model_color_clicked()  { currentModel = "color";  ui->Label_result->setText("模式：颜色识别"); }
