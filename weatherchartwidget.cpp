#include "weatherchartwidget.h"
#include <QPainter>
#include <QPen>

WeatherChartWidget::WeatherChartWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
}

void WeatherChartWidget::setData(const QList<int> &highs, const QList<int> &lows)
{
    highList = highs;
    lowList = lows;
    update(); // 触发重绘
}

void WeatherChartWidget::paintEvent(QPaintEvent *)
{
    if (highList.isEmpty() || lowList.isEmpty())
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int step = w / qMax(1, highList.size() - 1);
    int baseY = h - 40;

    QPen highPen(QColor(255,100,0), 2);
    QPen lowPen(QColor(0,150,255), 2);
    QBrush highBrush(QColor(255,100,0));
    QBrush lowBrush(QColor(0,150,255));

    for (int i = 0; i < highList.size(); ++i) {
        int x = i * step;
        int yHigh = baseY - highList[i]*2;
        int yLow  = baseY - lowList[i]*2 + 60;

        // 画点
        p.setBrush(highBrush);
        p.drawEllipse(QPointF(x, yHigh), 5, 5);
        p.setBrush(lowBrush);
        p.drawEllipse(QPointF(x, yLow), 5, 5);

        // 温度文字
        p.setPen(Qt::black);
        p.drawText(QPointF(x-10, yHigh-10), QString("%1℃").arg(highList[i]));
        p.drawText(QPointF(x-10, yLow+20), QString("%1℃").arg(lowList[i]));

        // 折线
        if (i < highList.size()-1) {
            int nextX = (i+1) * step;
            int nextYHigh = baseY - highList[i+1]*2;
            int nextYLow  = baseY - lowList[i+1]*2 + 60;

            p.setPen(highPen);
            p.drawLine(x, yHigh, nextX, nextYHigh);
            p.setPen(lowPen);
            p.drawLine(x, yLow, nextX, nextYLow);
        }
    }
}

