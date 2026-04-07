#include "RegisterPanel.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

RegisterPanel::RegisterPanel(QWidget* parent) : QWidget(parent) {
    setupUI();
}

void RegisterPanel::setupUI() {
    setObjectName("registerPanel");
    setStyleSheet("#registerPanel { background-color: white; }");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(50, 25, 50, 30);
    mainLayout->setSpacing(0);

    setupTopBar(mainLayout);
    mainLayout->addSpacing(10);
    setupLogo(mainLayout);
    mainLayout->addSpacing(20);

    // 标题
    QLabel* titleLabel = new QLabel("免费注册");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(20);
    setupInputFields(mainLayout);
    mainLayout->addSpacing(20);
    setupRegisterButton(mainLayout);
    mainLayout->addSpacing(15);
    setupBackLink(mainLayout);
    mainLayout->addStretch();
}

void RegisterPanel::setupTopBar(QVBoxLayout* mainLayout) {
    QHBoxLayout* topBar = new QHBoxLayout();
    topBar->addStretch();

    auto makeTopBtn = [](const QString& text) -> QPushButton* {
        QPushButton* btn = new QPushButton(text);
        btn->setFixedSize(30, 30);
        btn->setStyleSheet(
            "QPushButton { border: none; color: #999; font-size: 16px; background: transparent; }"
            "QPushButton:hover { color: #333; }"
        );
        return btn;
        };

    topBar->addWidget(makeTopBtn("⚙"));

    QPushButton* minBtn = makeTopBtn("—");
    QPushButton* closeBtn = makeTopBtn("✕");
    closeBtn->setStyleSheet(
        "QPushButton { border: none; color: #999; font-size: 16px; background: transparent; }"
        "QPushButton:hover { color: white; background: #e81123; border-radius: 4px; }"
    );

    connect(minBtn, &QPushButton::clicked, [this]() {
        window()->showMinimized();
        });
    connect(closeBtn, &QPushButton::clicked, [this]() {
        window()->close();
        });

    topBar->addWidget(minBtn);
    topBar->addWidget(closeBtn);
    topBar->setSpacing(0);
    mainLayout->addLayout(topBar);
}

void RegisterPanel::setupLogo(QVBoxLayout* mainLayout) {
    QLabel* logoLabel = new QLabel();
    logoLabel->setFixedSize(60, 60);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet(
        "background-color: #4facfe;"
        "border-radius: 30px;"
        "color: white;"
        "font-size: 28px;"
        "font-weight: bold;"
    );
    logoLabel->setText("🛡");

    QHBoxLayout* logoLayout = new QHBoxLayout();
    logoLayout->addStretch();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();
    mainLayout->addLayout(logoLayout);
}

void RegisterPanel::setupInputFields(QVBoxLayout* mainLayout) {
    usernameEdit = createInputField("👤", "请输入用户名");
    mainLayout->addWidget(usernameEdit);

    mainLayout->addSpacing(12);

    phoneEdit = createInputField("📱", "请输入手机号");
    mainLayout->addWidget(phoneEdit);

    mainLayout->addSpacing(12);

    passwordEdit = createInputField("🔒", "请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);

    mainLayout->addSpacing(12);

    confirmPasswordEdit = createInputField("🔒", "请确认密码");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(confirmPasswordEdit);
}

void RegisterPanel::setupRegisterButton(QVBoxLayout* mainLayout) {
    QPushButton* registerBtn = new QPushButton("注 册");
    registerBtn->setFixedHeight(45);
    registerBtn->setCursor(Qt::PointingHandCursor);
    registerBtn->setStyleSheet(
        "QPushButton {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop:0 #4facfe, stop:1 #42b0ff);"
        "  color: white;"
        "  border: none;"
        "  border-radius: 22px;"
        "  font-size: 16px;"
        "  font-weight: bold;"
        "  letter-spacing: 8px;"
        "}"
        "QPushButton:hover {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop:0 #3b9fee, stop:1 #359eff);"
        "}"
        "QPushButton:pressed {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop:0 #2d8fde, stop:1 #2890ef);"
        "}"
    );

    connect(registerBtn, &QPushButton::clicked, [this]() {
        QString username = usernameEdit->text().trimmed();
        QString phone = phoneEdit->text().trimmed();
        QString password = passwordEdit->text().trimmed();
        QString confirmPassword = confirmPasswordEdit->text().trimmed();

        if (username.isEmpty() || phone.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            QMessageBox::warning(this, "提示", "请填写所有字段！");
            return;
        }

        if (password != confirmPassword) {
            QMessageBox::warning(this, "提示", "两次输入的密码不一致！");
            return;
        }

        if (password.length() < 6) {
            QMessageBox::warning(this, "提示", "密码长度不能少于6位！");
            return;
        }

        QMessageBox::information(this, "注册成功",
            QString("恭喜 %1，注册成功！\n即将返回登录页面。").arg(username));

        emit backToLogin();
        });

    mainLayout->addWidget(registerBtn);
}

void RegisterPanel::setupBackLink(QVBoxLayout* mainLayout) {
    QHBoxLayout* linkLayout = new QHBoxLayout();
    linkLayout->addStretch();

    QPushButton* backBtn = new QPushButton("已有账号？返回登录");
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet(
        "QPushButton { border: none; color: #4facfe; font-size: 12px; background: transparent; }"
        "QPushButton:hover { color: #3b8dd9; }"
    );

    connect(backBtn, &QPushButton::clicked, [this]() {
        emit backToLogin();
        });

    linkLayout->addWidget(backBtn);
    linkLayout->addStretch();
    mainLayout->addLayout(linkLayout);
}

QLineEdit* RegisterPanel::createInputField(const QString& icon, const QString& placeholder) {
    QLineEdit* edit = new QLineEdit();
    edit->setPlaceholderText(placeholder);
    edit->setFixedHeight(45);
    edit->setTextMargins(30, 0, 10, 0);
    edit->setStyleSheet(
        "QLineEdit {"
        "  border: 1px solid #e0e0e0;"
        "  border-radius: 6px;"
        "  padding: 8px 5px;"
        "  font-size: 14px;"
        "  color: #333;"
        "  background: white;"
        "}"
        "QLineEdit:focus {"
        "  border-color: #4facfe;"
        "}"
        "QLineEdit::placeholder {"
        "  color: #bbb;"
        "}"
    );

    QLabel* iconLabel = new QLabel(icon, edit);
    iconLabel->setStyleSheet("border: none; background: transparent; font-size: 14px; color: #999;");
    iconLabel->setFixedSize(30, 45);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->move(8, 0);

    return edit;
}