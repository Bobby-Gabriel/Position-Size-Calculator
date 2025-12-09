#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QObject>
#include <cmath>
#include <QFile>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load stylesheet from the executable's directory
    QString styleSheetPath = QDir(QCoreApplication::applicationDirPath()).filePath("widget.qss");
    QFile styleFile(styleSheetPath);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromLatin1(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        styleFile.close();
    }

    QWidget window;
    window.resize(600, 450);
    window.setWindowTitle("Position Size Calculator");

    // Create grid layout
    QGridLayout *layout = new QGridLayout(&window);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setHorizontalSpacing(20);
    layout->setVerticalSpacing(20);
    layout->setAlignment(Qt::AlignTop);

    // Create label and input for Risk size
    QLabel *riskSizeLabel = new QLabel("RISK AMOUNT");
    riskSizeLabel->setObjectName("inputLabel");
    QLineEdit *riskSizeInput = new QLineEdit();
    QDoubleValidator *riskSizeValidator = new QDoubleValidator(0, 1000000, 2, riskSizeInput);
    riskSizeInput->setValidator(riskSizeValidator);
    riskSizeInput->setPlaceholderText("50.00");

    // Create label and input for entry price
    QLabel *entryLabel = new QLabel("ENTRY PRICE");
    entryLabel->setObjectName("inputLabel");
    QLineEdit *entryInput = new QLineEdit();
    QDoubleValidator *entryValidator = new QDoubleValidator(0, 1000000, 2, entryInput);
    entryInput->setValidator(entryValidator);
    entryInput->setPlaceholderText("5.48");

    // Create label and input for stop loss
    QLabel *stopLossLabel = new QLabel("STOP LOSS");
    stopLossLabel->setObjectName("inputLabel");
    QLineEdit *stopLossInput = new QLineEdit();
    QDoubleValidator *stopLossValidator = new QDoubleValidator(0, 1000000, 2, stopLossInput);
    stopLossInput->setValidator(stopLossValidator);
    stopLossInput->setPlaceholderText("5.23");

    // Create output label for share size
    QLabel *shareSizeOutputLabel = new QLabel("POSITION SIZE");
    shareSizeOutputLabel->setObjectName("resultLabel");
    QLabel *shareSizeValue = new QLabel("0");
    shareSizeValue->setObjectName("resultValue");

    // Add widgets to grid layout
    layout->addWidget(riskSizeLabel, 0, 0, 1, 2);
    layout->addWidget(riskSizeInput, 1, 0, 1, 2);
    layout->addWidget(entryLabel, 2, 0, 1, 2);
    layout->addWidget(entryInput, 3, 0, 1, 2);
    layout->addWidget(stopLossLabel, 4, 0, 1, 2);
    layout->addWidget(stopLossInput, 5, 0, 1, 2);
    layout->addWidget(shareSizeOutputLabel, 6, 0, 1, 2);
    layout->addWidget(shareSizeValue, 7, 0, 1, 2);

    layout->setRowMinimumHeight(6, 30);

    // Connect signals for real-time calculation
    auto calculateShareSize = [=]() {
        double riskSize = riskSizeInput->text().toDouble();
        double entryPrice = entryInput->text().toDouble();
        double stopLoss = stopLossInput->text().toDouble();

        if (riskSize > 0 && entryPrice > 0 && stopLoss > 0 && entryPrice != stopLoss) {
            double riskPerShare = qAbs(entryPrice - stopLoss);
            double shareSize = riskSize / riskPerShare;
            int shareSizeRounded = static_cast<int>(std::floor(shareSize));
            shareSizeValue->setText(QString::number(shareSizeRounded));
        } else {
            shareSizeValue->setText("0");
        }
    };

    QObject::connect(riskSizeInput, &QLineEdit::textChanged, calculateShareSize);
    QObject::connect(entryInput, &QLineEdit::textChanged, calculateShareSize);
    QObject::connect(stopLossInput, &QLineEdit::textChanged, calculateShareSize);

    window.show();

    return app.exec();
}
