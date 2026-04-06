#include "RightPanel.h"
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

RightPanel::RightPanel(QWidget* parent) : QWidget(parent) {
    setupUI();
}

void RightPanel::setupUI() {
    setObjectName("rightPanel");
    setStyleSheet("#rightPanel { background-color: white; }");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(50, 25, 50, 30);
    mainLayout->setSpacing(0);

    setupTopBar(mainLayout);
    mainLayout->addSpacing(10);
    setupLogo(mainLayout);
    mainLayout->addSpacing(30);
    setupPlatformCombo(mainLayout);
    mainLayout->addSpacing(15);
    setupInputFields(mainLayout);
    mainLayout->addSpacing(12);
    setupLinks(mainLayout);
    mainLayout->addSpacing(20);
    setupLoginButton(mainLayout);
    mainLayout->addSpacing(15);
    setupCheckBoxes(mainLayout);
    mainLayout->addStretch();
}

void RightPanel::setupTopBar(QVBoxLayout* mainLayout) {
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

void RightPanel::setupLogo(QVBoxLayout* mainLayout) {
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

void RightPanel::setupPlatformCombo(QVBoxLayout* mainLayout) {
    platformCombo = new QComboBox();
    platformCombo->addItem("淘宝网");
    platformCombo->addItem("天猫");
    platformCombo->addItem("京东");
    platformCombo->setFixedHeight(45);
    platformCombo->setStyleSheet(
        "QComboBox {"
        "  border: 1px solid #e0e0e0;"
        "  border-radius: 6px;"
        "  padding: 8px 15px;"
        "  font-size: 14px;"
        "  color: #333;"
        "  background: white;"
        "}"
        "QComboBox::drop-down {"
        "  subcontrol-origin: padding;"
        "  subcontrol-position: center right;"
        "  border: none;"
        "  width: 30px;"
        "}"
        "QComboBox::down-arrow {"
        "  width: 10px;"
        "  height: 10px;"
        "  image: url(arrow_down.png);"
        "}"
        "QComboBox QAbstractItemView {"
        "  border: 1px solid #e0e0e0;"
        "  selection-background-color: #f0f7ff;"
        "  selection-color: #333;"
        "  background: white;"
        "  padding: 5px;"
        "  outline: none;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "  min-height: 36px;"
        "  padding: 6px 15px;"
        "  color: #333;"
        "  background: white;"
        "}"
        "QComboBox QAbstractItemView::item:hover {"
        "  background-color: #f0f7ff;"
        "}"
        "QComboBox QAbstractItemView::item:selected {"
        "  background-color: #f0f7ff;"
        "}"
    );
    mainLayout->addWidget(platformCombo);
}

void RightPanel::setupInputFields(QVBoxLayout* mainLayout) {
    accountEdit = createInputField("👤", "请输入账号");
    mainLayout->addWidget(accountEdit);

    mainLayout->addSpacing(15);

    passwordEdit = createInputField("🔒", "请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);
}

void RightPanel::setupLinks(QVBoxLayout* mainLayout) {
    QHBoxLayout* linksLayout = new QHBoxLayout();

    auto makeLink = [](const QString& text, const QString& color = "#4facfe") -> QPushButton* {
        QPushButton* btn = new QPushButton(text);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            QString("QPushButton { border: none; color: %1; font-size: 12px; background: transparent; }"
                "QPushButton:hover { color: #3b8dd9; }").arg(color)
        );
        return btn;
        };

    linksLayout->addWidget(makeLink("多账号登录"));
    linksLayout->addStretch();
    linksLayout->addWidget(makeLink("免费注册", "#333"));
    linksLayout->addSpacing(15);
    linksLayout->addWidget(makeLink("忘记密码", "#333"));
    mainLayout->addLayout(linksLayout);
}

void RightPanel::setupLoginButton(QVBoxLayout* mainLayout) {
    QPushButton* loginBtn = new QPushButton("登 录");
    loginBtn->setFixedHeight(45);
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setStyleSheet(
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

    connect(loginBtn, &QPushButton::clicked, [this]() {
        QString account = accountEdit->text().trimmed();
        QString password = passwordEdit->text().trimmed();

        if (account.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "提示", "请输入账号和密码！");
            return;
        }

        if (account == "admin" && password == "123456") {
            QMessageBox::information(this, "登录成功",
                QString("欢迎回来，%1！\n登录平台：%2")
                .arg(account)
                .arg(platformCombo->currentText()));
        }
        else {
            QMessageBox::warning(this, "登录失败",
                "账号或密码错误！\n\n提示：默认账号 admin，密码 123456");
        }
        });

    mainLayout->addWidget(loginBtn);
}

void RightPanel::setupCheckBoxes(QVBoxLayout* mainLayout) {
    QHBoxLayout* checkLayout = new QHBoxLayout();
    checkLayout->addStretch();

    rememberCheck = new QCheckBox("记住密码");
    rememberCheck->setStyleSheet(
        "QCheckBox { font-size: 12px; color: #666; spacing: 5px; }"
        "QCheckBox::indicator { width: 14px; height: 14px; border: 1px solid #ccc; border-radius: 3px; }"
        "QCheckBox::indicator:checked { background: #4facfe; border-color: #4facfe; image: url(checkmark.png); }"
    );

    autoLoginCheck = new QCheckBox("自动登录");
    autoLoginCheck->setStyleSheet(rememberCheck->styleSheet());

    checkLayout->addWidget(rememberCheck);
    checkLayout->addSpacing(40);
    checkLayout->addWidget(autoLoginCheck);
    checkLayout->addStretch();
    mainLayout->addLayout(checkLayout);
}

QLineEdit* RightPanel::createInputField(const QString& icon, const QString& placeholder) {
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