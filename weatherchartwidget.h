#ifndef WEATHERCHARTWIDGET_H
#define WEATHERCHARTWIDGET_H

#include <QWidget>
#include <QList>

class WeatherChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherChartWidget(QWidget *parent = nullptr);

    void setData(const QList<int> &highs, const QList<int> &lows);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<int> highList;
    QList<int> lowList;
};

#endif // WEATHERCHARTWIDGET_H
