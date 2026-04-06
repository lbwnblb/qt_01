#include <QApplication>
#include <QFont>
#include <QPixmap>
#include <QPainter>
#include <QPolygonF>
#include "LoginWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 设置全局字体
    QFont defaultFont("Microsoft YaHei", 10);
    app.setFont(defaultFont);

    // 生成下拉箭头图标
    {
        QPixmap arrowPixmap(20, 20);
        arrowPixmap.fill(Qt::transparent);
        QPainter p(&arrowPixmap);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#999"));
        QPolygonF triangle;
        triangle << QPointF(4, 6) << QPointF(16, 6) << QPointF(10, 14);
        p.drawPolygon(triangle);
        p.end();
        arrowPixmap.save("arrow_down.png");
    }

    // 生成勾选图标
    {
        QPixmap checkPixmap(14, 14);
        checkPixmap.fill(Qt::transparent);
        QPainter p(&checkPixmap);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p.drawLine(3, 7, 6, 10);
        p.drawLine(6, 10, 11, 4);
        p.end();
        checkPixmap.save("checkmark.png");
    }

    LoginWindow window;
    window.show();

    return app.exec();
}