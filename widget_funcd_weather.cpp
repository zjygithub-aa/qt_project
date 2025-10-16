#include "widget_funcd_weather.h"
#include "ui_widget_funcd_weather.h"
#include "weatherchartwidget.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>

Widget_funcD_Weather::Widget_funcD_Weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_funcD_Weather)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Widget_funcD_Weather::onReplyFinished);
    connect(ui->searchButton, &QPushButton::clicked, this, &Widget_funcD_Weather::onSearchClicked);

    // 绑定折线图控件
    chartWidget = ui->chartWidget;

    // 加载全国城市ID表
    loadCityMap("C:/Users/jiayangdada/Downloads/city_id.txt");

    ui->searchInput->setText("北京");
    onSearchClicked();

    // 美化整体UI样式（通过代码设置样式表）
    this->setStyleSheet(R"(
        Widget_funcD_Weather {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0F7FA, stop:1 #FFFFFF);
            border-radius: 10px;
            padding: 10px;
        }
        QLabel {
            color: #333333;
            font-family: "Arial";
            font-size: 12px;
            padding: 5px;
        }
        QLineEdit {
            background: white;
            border: 1px solid #B0BEC5;
            border-radius: 5px;
            padding: 5px;
            margin-right: 10px;
        }
        QPushButton {
            background: #2196F3;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 5px 10px;
        }
        QPushButton:hover {
            background: #1976D2;
        }
        #chartWidget {
            margin: 15px 0;
            padding: 10px;
            border: 1px solid #B0BEC5;
            border-radius: 5px;
            background: white;
        }
        .forecastContainer {
            margin-top: 15px;
            padding: 10px;
            background: white;
            border: 1px solid #B0BEC5;
            border-radius: 5px;
        }
        .forecastItem {
            margin: 5px;
            text-align: center;
        }
    )");

    // 设置布局间距
    ui->verticalLayout->setSpacing(15); // 使用verticalLayout设置间距
}

Widget_funcD_Weather::~Widget_funcD_Weather()
{
    delete ui;
}

void Widget_funcD_Weather::loadCityMap(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开城市ID文件:" << filePath;
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        if (line.startsWith(QChar(0xFEFF))) line.remove(0, 1);

        QStringList parts = line.split("\t");
        if (parts.size() != 2) continue;

        QString id = parts[0].trimmed();
        QString name = parts[1].trimmed();
        cityMap[name] = id;
        cityNameList << name;
    }

    file.close();
    qDebug() << "已加载城市ID数:" << cityMap.size();

    completer = new QCompleter(cityNameList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->searchInput->setCompleter(completer);
}

void Widget_funcD_Weather::onSearchClicked()
{
    cityName = ui->searchInput->text().trimmed();
    if (cityName.isEmpty()) return;

    QString cityId = cityMap.value(cityName, "101010100");
    qDebug() << "搜索城市:" << cityName << " cityId:" << cityId;

    QString url = QString("http://t.weather.itboy.net/api/weather/city/%1").arg(cityId);
    manager->get(QNetworkRequest(QUrl(url)));
}

void Widget_funcD_Weather::onReplyFinished(QNetworkReply *reply)
{
    QByteArray json = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if (!doc.isObject()) return;

    QJsonObject root = doc.object();
    int status = root["status"].toInt();
    if (status != 200) {
        qDebug() << "天气接口返回非200:" << status;
        return;
    }

    QJsonObject data = root["data"].toObject();
    updateWeatherUI(data);
}

void Widget_funcD_Weather::updateWeatherUI(const QJsonObject &data)
{
    ui->cityLabel->setText(data["cityInfo"].toObject()["city"].toString());
    ui->tempLabel->setText(data["wendu"].toString() + "°C");
    ui->windHumidityLabel->setText(
        QString("湿度: %1   风力: %2")
        .arg(data["shidu"].toString())
        .arg(data["forecast"].toArray()[0].toObject()["fl"].toString())
    );

    QString dayStr = data["forecast"].toArray()[0].toObject()["date"].toString();
    dayStr.remove("日");
    QDate today = QDate::currentDate();
    QString fullDate = QString("%1-%2-%3")
                       .arg(today.year())
                       .arg(today.month(), 2, 10, QChar('0'))
                       .arg(dayStr.toInt(), 2, 10, QChar('0'));
    ui->dateLabel->setText(fullDate);

    ui->weatherDescLabel->setText(data["forecast"].toArray()[0].toObject()["type"].toString());

    QString weatherType = ui->weatherDescLabel->text();
    ui->iconLabel->setPixmap(getWeatherIcon(weatherType).scaled(60, 60, Qt::KeepAspectRatio));

    if (weatherType.contains("晴"))
        ui->moodLabel->setText("愿你拥有比阳光明媚的心情");
    else if (weatherType.contains("雨"))
        ui->moodLabel->setText("雨洗清心，愿你自在如风");
    else if (weatherType.contains("阴"))
        ui->moodLabel->setText("阴云遮日，笑容仍亮");
    else
        ui->moodLabel->setText("愿你今天顺心如意");

    highList.clear();
    lowList.clear();
    weekList.clear();
    weatherList.clear();
    QJsonArray arr = data["forecast"].toArray();
    for (int i = 0; i < qMin(7, arr.size()); ++i) {
        QJsonObject obj = arr[i].toObject();
        QString highStr = obj["high"].toString().remove("高温 ").remove("℃");
        QString lowStr = obj["low"].toString().remove("低温 ").remove("℃");
        highList << highStr.toInt();
        lowList << lowStr.toInt();
        weekList << obj["week"].toString();
        weatherList << obj["type"].toString();

        QLabel *weekLabel = findChild<QLabel*>(QString("weekLabel%1").arg(i));
        QLabel *tempLabel = findChild<QLabel*>(QString("tempRangeLabel%1").arg(i));
        QLabel *iconLabel = findChild<QLabel*>(QString("weatherIconLabel%1").arg(i));
        if (weekLabel && tempLabel && iconLabel) {
            weekLabel->setText(weekList[i]);
            tempLabel->setText(QString("%1℃~%2℃").arg(lowList[i]).arg(highList[i]));
            iconLabel->setPixmap(getWeatherIcon(weatherList[i]).scaled(30, 30, Qt::KeepAspectRatio));
        }
    }

    if (chartWidget)
        chartWidget->setData(highList, lowList, weekList);
}

QPixmap Widget_funcD_Weather::getWeatherIcon(const QString &type)
{
    if (type.contains("晴")) return QPixmap(":/img/sun.png");
    if (type.contains("云")) return QPixmap(":/img/cloud.png");
    if (type.contains("雨")) return QPixmap(":/img/rain.png");
    if (type.contains("雪")) return QPixmap(":/img/snow.png");
    if (type.contains("阴")) return QPixmap(":/img/wind.png");
    if (type.contains("霾")) return QPixmap(":/img/smog.png");
    return QPixmap(":/img/window.png");
}

void Widget_funcD_Weather::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}
