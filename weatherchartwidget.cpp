#include "weatherchartwidget.h"
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include <QFont>

WeatherChartWidget::WeatherChartWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
}

void WeatherChartWidget::setData(const QList<int> &highs, const QList<int> &lows, const QStringList &weeks)
{
    highList = highs;
    lowList = lows;
    weekList = weeks; // Set the week list
    update(); // 触发重绘
}

void WeatherChartWidget::paintEvent(QPaintEvent *)
{
    if (highList.isEmpty() || lowList.isEmpty() || weekList.isEmpty())
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int w = width();
    int h = height();

    int topMargin = 30;    // 增加顶部边距以容纳标签
    int bottomMargin = 40; // 增加底部边距以容纳x轴标签
    int leftMargin = 50;   // 增加左侧边距以容纳y轴标签
    int rightMargin = 30;  // 右侧边距
    int chartWidth = w - leftMargin - rightMargin;
    int chartHeight = h - topMargin - bottomMargin;

    // 找到最大和最小温度，并添加一些缓冲
    int maxTemp = *std::max_element(highList.constBegin(), highList.constEnd()) + 2;
    int minTemp = *std::min_element(lowList.constBegin(), lowList.constEnd()) - 2;
    int tempRange = maxTemp - minTemp;
    if (tempRange == 0) tempRange = 1;

    // 绘制渐变背景
    QLinearGradient bgGradient(0, 0, 0, h);
    bgGradient.setColorAt(0, QColor(240, 248, 255)); // 浅蓝
    bgGradient.setColorAt(1, QColor(255, 255, 255)); // 白色
    p.fillRect(rect(), bgGradient);

    // 绘制网格线
    QPen gridPen(QColor(200, 200, 200), 1, Qt::DashLine);
    p.setPen(gridPen);

    // 水平网格线（温度刻度）
    int numHorizontalLines = 5;
    for (int i = 0; i <= numHorizontalLines; ++i) {
        int y = topMargin + (chartHeight * i) / numHorizontalLines;
        p.drawLine(leftMargin, y, w - rightMargin, y);
    }

    // 垂直网格线（日子）
    int n = highList.size();
    double step = n > 1 ? (double)chartWidth / (n - 1) : 0;
    for (int i = 0; i < n; ++i) {
        double x = leftMargin + i * step;
        p.drawLine(x, topMargin, x, topMargin + chartHeight);
    }

    // 绘制y轴标签（温度刻度）
    QFont labelFont("Arial", 8);
    p.setFont(labelFont);
    p.setPen(QColor(100, 100, 100));
    for (int i = 0; i <= numHorizontalLines; ++i) {
        int temp = maxTemp - (i * tempRange / numHorizontalLines);
        int y = topMargin + (chartHeight * i) / numHorizontalLines;
        p.drawText(10, y - 8, 40, 16, Qt::AlignRight | Qt::AlignVCenter, QString("%1°C").arg(temp));
    }

    // 曲线颜色和样式
    QPen highPen(QColor(255, 140, 0), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // 橙色高温线
    QPen lowPen(QColor(30, 144, 255), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // 蓝色低温线
    QBrush highBrush(QColor(255, 140, 0));
    QBrush lowBrush(QColor(30, 144, 255));

    // 绘制高温曲线
    p.setPen(highPen);
    for (int i = 0; i < n - 1; ++i) {
        double x1 = leftMargin + i * step;
        double y1 = topMargin + chartHeight * (maxTemp - highList[i]) / tempRange;
        double x2 = leftMargin + (i + 1) * step;
        double y2 = topMargin + chartHeight * (maxTemp - highList[i + 1]) / tempRange;
        p.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // 绘制低温曲线
    p.setPen(lowPen);
    for (int i = 0; i < n - 1; ++i) {
        double x1 = leftMargin + i * step;
        double y1 = topMargin + chartHeight * (maxTemp - lowList[i]) / tempRange;
        double x2 = leftMargin + (i + 1) * step;
        double y2 = topMargin + chartHeight * (maxTemp - lowList[i + 1]) / tempRange;
        p.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // 绘制点和温度标签
    QFont tempFont("Arial", 9, QFont::Bold);
    p.setFont(tempFont);
    for (int i = 0; i < n; ++i) {
        double x = leftMargin + i * step;
        double yHigh = topMargin + chartHeight * (maxTemp - highList[i]) / tempRange;
        double yLow = topMargin + chartHeight * (maxTemp - lowList[i]) / tempRange;

        // 高温点
        p.setBrush(highBrush);
        p.setPen(highPen);
        p.drawEllipse(QPointF(x, yHigh), 6, 6);

        // 低温点
        p.setBrush(lowBrush);
        p.setPen(lowPen);
        p.drawEllipse(QPointF(x, yLow), 6, 6);

        // 温度文字（高温在上，低温在下）
        p.setPen(QColor(255, 140, 0));
        p.drawText(QRectF(x - 20, yHigh - 25, 40, 20), Qt::AlignCenter, QString("%1°C").arg(highList[i]));
        p.setPen(QColor(30, 144, 255));
        p.drawText(QRectF(x - 20, yLow + 10, 40, 20), Qt::AlignCenter, QString("%1°C").arg(lowList[i]));

        // x轴标签（星期）
        p.setPen(QColor(100, 100, 100));
        p.setFont(labelFont);
        p.drawText(QRectF(x - 20, h - bottomMargin + 5, 40, 20), Qt::AlignCenter, weekList[i]);
    }
}
