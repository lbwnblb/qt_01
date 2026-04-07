#pragma once

#include <QWidget>
#include <QPoint>

class QStackedWidget;
class RightPanel;
class RegisterPanel;

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPoint m_dragPos;
    QStackedWidget* rightStack;
    RightPanel* rightPanel;
    RegisterPanel* registerPanel;
};