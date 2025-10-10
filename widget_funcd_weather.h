#ifndef WIDGET_FUNCD_WEATHER_H
#define WIDGET_FUNCD_WEATHER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QMap>
#include <QCompleter>
#include <QStringListModel>
#include "weatherchartwidget.h"

namespace Ui {
class Widget_funcD_Weather;
}

class Widget_funcD_Weather : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_funcD_Weather(QWidget *parent = nullptr);
    ~Widget_funcD_Weather();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onSearchClicked();
    void onReplyFinished(QNetworkReply *reply);

private:
    Ui::Widget_funcD_Weather *ui;
    QNetworkAccessManager *manager;

    QString cityName;
    QStringList weekList;
    QList<int> highList, lowList;
    QList<QString> weatherList;
    QCompleter *completer = nullptr;
    QStringList cityNameList; // 所有城市名，用于提示

    QMap<QString, QString> cityMap; // key = 城市名, value = 城市ID

    WeatherChartWidget *chartWidget; // 添加这一行，指向折线图控件

    void loadCityMap(const QString &filePath);
    void updateWeatherUI(const QJsonObject &data);
    QPixmap getWeatherIcon(const QString &type);
};

#endif // WIDGET_FUNCD_WEATHER_H
