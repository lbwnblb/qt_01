#pragma once

#include <QWidget>

class QLineEdit;
class QComboBox;
class QCheckBox;
class QVBoxLayout;

class RightPanel : public QWidget {
    Q_OBJECT

public:
    explicit RightPanel(QWidget* parent = nullptr);

private:
    QLineEdit* accountEdit;
    QLineEdit* passwordEdit;
    QComboBox* platformCombo;
    QCheckBox* rememberCheck;
    QCheckBox* autoLoginCheck;

    void setupUI();
    void setupTopBar(QVBoxLayout* mainLayout);
    void setupLogo(QVBoxLayout* mainLayout);
    void setupPlatformCombo(QVBoxLayout* mainLayout);
    void setupInputFields(QVBoxLayout* mainLayout);
    void setupLinks(QVBoxLayout* mainLayout);
    void setupLoginButton(QVBoxLayout* mainLayout);
    void setupCheckBoxes(QVBoxLayout* mainLayout);

    QLineEdit* createInputField(const QString& icon, const QString& placeholder);
};