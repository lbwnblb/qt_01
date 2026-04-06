#pragma once

#include <QWidget>

class QLineEdit;
class QVBoxLayout;

class RegisterPanel : public QWidget {
    Q_OBJECT

public:
    explicit RegisterPanel(QWidget* parent = nullptr);

signals:
    void backToLogin();

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QLineEdit* phoneEdit;

    void setupUI();
    void setupTopBar(QVBoxLayout* mainLayout);
    void setupLogo(QVBoxLayout* mainLayout);
    void setupInputFields(QVBoxLayout* mainLayout);
    void setupRegisterButton(QVBoxLayout* mainLayout);
    void setupBackLink(QVBoxLayout* mainLayout);

    QLineEdit* createInputField(const QString& icon, const QString& placeholder);
};
