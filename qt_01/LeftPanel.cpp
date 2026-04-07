#include "LeftPanel.h"
#include <QLinearGradient>
#include <QFont>
#include <QVector>
#include <QPointF>

LeftPanel::LeftPanel(QWidget* parent) : QWidget(parent) {
    setFixedWidth(320);
}

void LeftPanel::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 蓝色渐变背景
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, QColor("#4facfe"));
    gradient.setColorAt(1, QColor("#3b8dd9"));
    painter.fillRect(rect(), gradient);

    // 标题文字
    QFont titleFont("Microsoft YaHei", 20, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(30, 80, "全新发布");

    // 版本标签
    QFont versionFont("Microsoft YaHei", 9, QFont::Bold);
    painter.setFont(versionFont);

    // v9.0 背景圆角矩形
    QRectF versionRect(155, 62, 42, 20);
    painter.setBrush(QColor(255, 150, 50));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(versionRect, 10, 10);
    painter.setPen(Qt::white);
    painter.drawText(versionRect, Qt::AlignCenter, "v9.0");

    // 副标题
    QFont subFont("Microsoft YaHei", 10);
    painter.setFont(subFont);
    painter.setPen(QColor(255, 255, 255, 200));
    painter.drawText(30, 110, "回归核心经营链路 聚焦体验与服务升级");

    // 绘制装饰卡片 - 主卡片
    drawCard(painter, 40, 150, 200, 130, QColor(255, 255, 255, 40));
    drawCard(painter, 60, 165, 200, 130, QColor(255, 255, 255, 60));

    // 卡片上的小图标装饰
    painter.setBrush(QColor(255, 255, 255, 80));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(80, 185, 60, 8, 4, 4);
    painter.drawRoundedRect(80, 200, 100, 8, 4, 4);
    painter.drawRoundedRect(80, 215, 80, 8, 4, 4);

    // NEW 标签
    painter.setBrush(QColor(76, 217, 100));
    painter.drawRoundedRect(155, 175, 45, 20, 10, 10);
    QFont newFont("Arial", 8, QFont::Bold);
    painter.setFont(newFont);
    painter.setPen(Qt::white);
    painter.drawText(QRectF(155, 175, 45, 20), Qt::AlignCenter, "NEW");

    // 底部小卡片
    drawCard(painter, 30, 310, 180, 80, QColor(255, 255, 255, 50));

    // 图表装饰线
    painter.setPen(QPen(QColor(255, 255, 255, 150), 2));
    QVector<QPointF> chartPoints = {
        {50, 370}, {80, 350}, {100, 360}, {130, 340}, {160, 345}, {190, 330}
    };
    for (int i = 0; i < chartPoints.size() - 1; i++) {
        painter.drawLine(chartPoints[i], chartPoints[i + 1]);
    }

    // 用户头像图标
    painter.setBrush(QColor(255, 200, 100));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(55, 330, 30, 30);

    // 上箭头装饰
    painter.setPen(QPen(QColor(255, 255, 255, 120), 2));
    painter.drawLine(250, 300, 250, 260);
    painter.drawLine(245, 268, 250, 260);
    painter.drawLine(255, 268, 250, 260);

    painter.drawLine(275, 320, 275, 285);
    painter.drawLine(270, 293, 275, 285);
    painter.drawLine(280, 293, 275, 285);
}

void LeftPanel::drawCard(QPainter& painter, int x, int y, int w, int h, QColor color) {
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(x, y, w, h, 12, 12);
}