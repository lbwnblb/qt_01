#pragma once

#include <QWidget>

class QLineEdit;
class QCheckBox;
class QVBoxLayout;
class QNetworkAccessManager;
class QPushButton;

class RightPanel : public QWidget {
    Q_OBJECT

public:
    explicit RightPanel(QWidget* parent = nullptr);

signals:
    void registerClicked();
    void loginSuccess(const QString& token);

private:
    QLineEdit* accountEdit;
    QLineEdit* passwordEdit;
    QCheckBox* rememberCheck;
    QCheckBox* autoLoginCheck;
    QNetworkAccessManager* networkManager;
    QPushButton* loginBtn;
    QString m_token;

    void setupUI();
    void setupTopBar(QVBoxLayout* mainLayout);
    void setupLogo(QVBoxLayout* mainLayout);
    void setupInputFields(QVBoxLayout* mainLayout);
    void setupLinks(QVBoxLayout* mainLayout);
    void setupLoginButton(QVBoxLayout* mainLayout);
    void setupCheckBoxes(QVBoxLayout* mainLayout);
    void doLogin();

    QLineEdit* createInputField(const QString& icon, const QString& placeholder);
};