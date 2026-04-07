#include "LoginWindow.h"
#include "LeftPanel.h"
#include "RightPanel.h"
#include "RegisterPanel.h"
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("千牛工作台");
    setFixedSize(750, 480);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    LeftPanel* leftPanel = new LeftPanel();

    rightStack = new QStackedWidget();
    rightPanel = new RightPanel();
    registerPanel = new RegisterPanel();

    rightStack->addWidget(rightPanel);
    rightStack->addWidget(registerPanel);
    rightStack->setCurrentIndex(0);

    connect(rightPanel, &RightPanel::registerClicked, [this]() {
        rightStack->setCurrentIndex(1);
        });
    connect(registerPanel, &RegisterPanel::backToLogin, [this]() {
        rightStack->setCurrentIndex(0);
        });

    layout->addWidget(leftPanel);
    layout->addWidget(rightStack);
}

void LoginWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    painter.setClipPath(path);
    painter.fillRect(rect(), Qt::white);
}

void LoginWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginWindow::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPos);
        event->accept();
    }
}