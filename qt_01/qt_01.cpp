#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QPixmap>
#include <QFont>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QPainterPath>

// ==================== 左侧面板 ====================
class LeftPanel : public QWidget {
public:
    LeftPanel(QWidget* parent = nullptr) : QWidget(parent) {
        setFixedWidth(320);
    }

protected:
    void paintEvent(QPaintEvent*) override {
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

private:
    void drawCard(QPainter& painter, int x, int y, int w, int h, QColor color) {
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(x, y, w, h, 12, 12);
    }
};

// ==================== 右侧面板 ====================
class RightPanel : public QWidget {
public:
    RightPanel(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private:
    QLineEdit* accountEdit;
    QLineEdit* passwordEdit;
    QComboBox* platformCombo;
    QCheckBox* rememberCheck;
    QCheckBox* autoLoginCheck;

    void setupUI() {
        setObjectName("rightPanel");
        setStyleSheet("#rightPanel { background-color: white; }");

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(50, 25, 50, 30);
        mainLayout->setSpacing(0);

        // 顶部右侧按钮区域（设置、最小化、关闭）
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
        topBar->addWidget(makeTopBtn("—"));
        topBar->addWidget(makeTopBtn("✕"));
        topBar->setSpacing(0);
        mainLayout->addLayout(topBar);

        mainLayout->addSpacing(10);

        // Logo 图标
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

        mainLayout->addSpacing(30);

        // 平台选择下拉框
        platformCombo = new QComboBox();
        platformCombo->addItem("淘  淘宝网");
        platformCombo->addItem("天  天猫");
        platformCombo->addItem("京  京东");
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
            "  border: none;"
            "  width: 30px;"
            "}"
            "QComboBox::down-arrow {"
            "  image: none;"
            "  border-left: 5px solid transparent;"
            "  border-right: 5px solid transparent;"
            "  border-top: 6px solid #999;"
            "  margin-right: 10px;"
            "}"
            "QComboBox QAbstractItemView {"
            "  border: 1px solid #e0e0e0;"
            "  selection-background-color: #f0f7ff;"
            "  selection-color: #333;"
            "  background: white;"
            "  color: #333;"
            "  padding: 5px;"
            "  outline: none;"
            "}"
            "QComboBox QAbstractItemView::item {"
            "  height: 36px;"
            "  padding: 6px 15px;"
            "  background: white;"
            "  color: #333;"
            "}"
            "QComboBox QAbstractItemView::item:selected {"
            "  background: #f0f7ff;"
            "  color: #333;"
            "}"
        );
        mainLayout->addWidget(platformCombo);

        mainLayout->addSpacing(15);

        // 账号输入框
        accountEdit = createInputField("👤", "请输入账号");
        mainLayout->addWidget(accountEdit);

        mainLayout->addSpacing(15);

        // 密码输入框
        passwordEdit = createInputField("🔒", "请输入密码");
        passwordEdit->setEchoMode(QLineEdit::Password);
        mainLayout->addWidget(passwordEdit);

        mainLayout->addSpacing(12);

        // 链接区域：多账号登录 | 免费注册 | 忘记密码
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

        mainLayout->addSpacing(20);

        // 登录按钮
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

        // 登录按钮点击事件
        QObject::connect(loginBtn, &QPushButton::clicked, [this]() {
            QString account = accountEdit->text().trimmed();
            QString password = passwordEdit->text().trimmed();

            if (account.isEmpty() || password.isEmpty()) {
                QMessageBox::warning(this, "提示", "请输入账号和密码！");
                return;
            }

            // 模拟登录验证
            if (account == "admin" && password == "123456") {
                QMessageBox::information(this, "登录成功",
                    QString("欢迎回来，%1！\n登录平台：%2")
                    .arg(account)
                    .arg(platformCombo->currentText().mid(3).trimmed()));
            }
            else {
                QMessageBox::warning(this, "登录失败",
                    "账号或密码错误！\n\n提示：默认账号 admin，密码 123456");
            }
            });

        mainLayout->addWidget(loginBtn);

        mainLayout->addSpacing(15);

        // 复选框区域
        QHBoxLayout* checkLayout = new QHBoxLayout();
        checkLayout->addStretch();

        rememberCheck = new QCheckBox("记住密码");
        rememberCheck->setStyleSheet(
            "QCheckBox { font-size: 12px; color: #666; spacing: 5px; }"
            "QCheckBox::indicator { width: 14px; height: 14px; border: 1px solid #ccc; border-radius: 3px; }"
            "QCheckBox::indicator:checked { background: #4facfe; border-color: #4facfe; }"
        );

        autoLoginCheck = new QCheckBox("自动登录");
        autoLoginCheck->setStyleSheet(rememberCheck->styleSheet());

        checkLayout->addWidget(rememberCheck);
        checkLayout->addSpacing(40);
        checkLayout->addWidget(autoLoginCheck);
        checkLayout->addStretch();
        mainLayout->addLayout(checkLayout);

        mainLayout->addStretch();
    }

    QLineEdit* createInputField(const QString& icon, const QString& placeholder) {
        QLineEdit* edit = new QLineEdit();
        edit->setPlaceholderText(QString("  %1  %2").arg(icon, placeholder));
        edit->setFixedHeight(45);
        edit->setStyleSheet(
            "QLineEdit {"
            "  border: 1px solid #e0e0e0;"
            "  border-radius: 6px;"
            "  padding: 8px 15px;"
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
        return edit;
    }
};

// ==================== 主窗口 ====================
class LoginWindow : public QWidget {
public:
    LoginWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("千牛工作台");
        setFixedSize(750, 480);
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        LeftPanel* leftPanel = new LeftPanel();
        RightPanel* rightPanel = new RightPanel();

        layout->addWidget(leftPanel);
        layout->addWidget(rightPanel);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 窗口圆角背景
        QPainterPath path;
        path.addRoundedRect(rect(), 10, 10);
        painter.setClipPath(path);
        painter.fillRect(rect(), Qt::white);
    }

    // 无边框窗口拖动
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPosition().toPoint() - m_dragPos);
            event->accept();
        }
    }

private:
    QPoint m_dragPos;
};

// ==================== main ====================
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 设置全局字体
    QFont defaultFont("Microsoft YaHei", 10);
    app.setFont(defaultFont);

    LoginWindow window;
    window.show();

    return app.exec();
}