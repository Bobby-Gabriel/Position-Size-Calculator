#include <QApplication>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Position Size Calculator");
    window.resize(400, 300);

    QLabel *label = new QLabel("Hello", &window);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px;");

    window.show();

    return app.exec();
}
