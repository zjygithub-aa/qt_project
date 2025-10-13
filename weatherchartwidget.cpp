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

    int topMargin = 20;
    int bottomMargin = 20;
    int leftMargin = 20;   // 左侧留白
    int rightMargin = 20;  // 右侧留白
    int chartWidth = w - leftMargin - rightMargin;
    int chartHeight = h - topMargin - bottomMargin;

    int maxTemp = *std::max_element(highList.constBegin(), highList.constEnd());
    int minTemp = *std::min_element(lowList.constBegin(), lowList.constEnd());
    int tempRange = maxTemp - minTemp;
    if (tempRange == 0) tempRange = 1;

    QPen highPen(QColor(255,100,0), 2);
    QPen lowPen(QColor(0,150,255), 2);
    QBrush highBrush(QColor(255,100,0));
    QBrush lowBrush(QColor(0,150,255));

    int n = highList.size();
    double step = n > 1 ? (double)chartWidth / (n-1) : 0;

    for (int i = 0; i < n; ++i) {
        double x = leftMargin + i * step;

        int yHigh = topMargin + chartHeight * (maxTemp - highList[i]) / tempRange;
        int yLow  = topMargin + chartHeight * (maxTemp - lowList[i]) / tempRange;

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
        if (i < n-1) {
            double nextX = leftMargin + (i+1) * step;
            int nextYHigh = topMargin + chartHeight * (maxTemp - highList[i+1]) / tempRange;
            int nextYLow  = topMargin + chartHeight * (maxTemp - lowList[i+1]) / tempRange;

            p.setPen(highPen);
            p.drawLine(x, yHigh, nextX, nextYHigh);
            p.setPen(lowPen);
            p.drawLine(x, yLow, nextX, nextYLow);
        }
    }
}



