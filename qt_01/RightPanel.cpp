#include "RightPanel.h"
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QDebug>

// Debug 模式用本地地址，Release 模式用线上地址
#ifdef QT_DEBUG
static const QString BASE_URL = "http://0.0.0.0:2781";
#else
static const QString BASE_URL = "https://agent.aiyiyong.com";
#endif

RightPanel::RightPanel(QWidget* parent) : QWidget(parent) {
    networkManager = new QNetworkAccessManager(this);
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
    mainLayout->addSpacing(20);

    // 状态提示标签（账号输入框上方）
    statusLabel = new QLabel();
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setFixedHeight(20);
    statusLabel->setStyleSheet("font-size: 13px; color: #e81123; background: transparent;");
    statusLabel->hide();
    mainLayout->addWidget(statusLabel);
    mainLayout->addSpacing(10);

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

    linksLayout->addStretch();
    QPushButton* registerLink = makeLink("免费注册", "#333");
    linksLayout->addWidget(registerLink);
    connect(registerLink, &QPushButton::clicked, [this]() {
        emit registerClicked();
        });
    linksLayout->addSpacing(15);
    linksLayout->addWidget(makeLink("忘记密码", "#333"));
    mainLayout->addLayout(linksLayout);
}

void RightPanel::setupLoginButton(QVBoxLayout* mainLayout) {
    loginBtn = new QPushButton("登 录");
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

    connect(loginBtn, &QPushButton::clicked, this, &RightPanel::doLogin);

    mainLayout->addWidget(loginBtn);
}

void RightPanel::doLogin() {
    QString account = accountEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (account.isEmpty() || password.isEmpty()) {
        statusLabel->setStyleSheet("font-size: 13px; color: #e81123; background: transparent;");
        statusLabel->setText("请输入账号和密码！");
        statusLabel->show();
        return;
    }

    // 隐藏之前的提示
    statusLabel->hide();

    // 禁用登录按钮，防止重复点击
    loginBtn->setEnabled(false);
    loginBtn->setText("登录中...");

    // 构造 JSON 请求体
    QJsonObject json;
    json["user_name"] = account;
    json["password"] = password;
    QJsonDocument doc(json);

    QByteArray requestBody = doc.toJson(QJsonDocument::Compact);
    qDebug() << "========== 登录请求 ==========";
    qDebug() << "URL:" << BASE_URL + "/api/login";
    qDebug() << "请求体:" << requestBody;

    // 发送 HTTP POST 请求
    QNetworkRequest request(QUrl(BASE_URL + "/api/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager->post(request, requestBody);

    connect(reply, &QNetworkReply::finished, this, [this, reply, account]() {
        // 恢复按钮状态
        loginBtn->setEnabled(true);
        loginBtn->setText("登 录");

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray responseData = reply->readAll();

        qDebug() << "========== 登录响应 ==========";
        qDebug() << "HTTP 状态码:" << statusCode;
        qDebug() << "网络错误码:" << reply->error();
        qDebug() << "错误描述:" << reply->errorString();
        qDebug() << "响应头:";
        for (const auto& header : reply->rawHeaderList()) {
            qDebug() << "  " << header << ":" << reply->rawHeader(header);
        }
        qDebug() << "响应体:" << responseData;
        qDebug() << "==============================";

        if (reply->error() == QNetworkReply::NoError) {
            QJsonParseError parseError;
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "JSON 解析失败:" << parseError.errorString();
                statusLabel->setStyleSheet("font-size: 13px; color: #e81123; background: transparent;");
                statusLabel->setText("服务器返回数据格式错误");
                statusLabel->show();
                reply->deleteLater();
                return;
            }

            QJsonObject responseObj = responseDoc.object();
            qDebug() << "解析后的 JSON:" << responseObj;

            // 后端统一格式: {"code": 200, "msg": "success", "data": {"token": "..."}}
            int code = responseObj.value("code").toInt();
            QString msg = responseObj.value("msg").toString();
            qDebug() << "业务码:" << code << "消息:" << msg;

            if (code == 200) {
                QJsonObject dataObj = responseObj.value("data").toObject();
                QString token = dataObj.value("token").toString();
                qDebug() << "获取到 token:" << token;
                m_token = token;
                // 成功：绿色显示
                statusLabel->setStyleSheet("font-size: 13px; color: #27ae60; background: transparent;");
                statusLabel->setText(QString("[%1] 登录成功，欢迎 %2！").arg(code).arg(account));
                statusLabel->show();
                emit loginSuccess(token);
            }
            else {
                // 失败：红色显示，带响应码
                statusLabel->setStyleSheet("font-size: 13px; color: #e81123; background: transparent;");
                statusLabel->setText(QString("[%1] %2").arg(code).arg(msg));
                statusLabel->show();
            }
        }
        else {
            // 网络错误处理
            QString errorMsg;
            if (reply->error() == QNetworkReply::ConnectionRefusedError) {
                errorMsg = "无法连接到服务器，请确认服务器已启动";
            }
            else if (reply->error() == QNetworkReply::TimeoutError) {
                errorMsg = "连接超时，请稍后重试";
            }
            else {
                QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
                if (!responseDoc.isNull()) {
                    QJsonObject responseObj = responseDoc.object();
                    errorMsg = responseObj.value("msg").toString();
                }
                if (errorMsg.isEmpty()) {
                    errorMsg = reply->errorString();
                }
            }
            qDebug() << "登录失败:" << errorMsg;
            statusLabel->setStyleSheet("font-size: 13px; color: #e81123; background: transparent;");
            statusLabel->setText(QString("[网络错误] %1").arg(errorMsg));
            statusLabel->show();
        }

        reply->deleteLater();
        });
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