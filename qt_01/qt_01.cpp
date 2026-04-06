#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Click Me!");
    button.setFixedSize(200, 60);

    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMessageBox::information(&button, "Hello", "You clicked the button!");
        });

    button.show();
    return app.exec();
}