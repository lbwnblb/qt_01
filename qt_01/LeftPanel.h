#pragma once

#include <QWidget>
#include <QPainter>

class LeftPanel : public QWidget {
    Q_OBJECT

public:
    explicit LeftPanel(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void drawCard(QPainter& painter, int x, int y, int w, int h, QColor color);
};
