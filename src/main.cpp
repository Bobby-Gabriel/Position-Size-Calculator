#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QLineEdit>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QObject>
#include <cmath>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString styleSheetPath = QDir(QCoreApplication::applicationDirPath()).filePath("widget.qss");
    QFile styleFile(styleSheetPath);
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(QString::fromLatin1(styleFile.readAll()));
        styleFile.close();
    }

    QWidget window;
    window.resize(1300, 1000);
    window.setMinimumSize(800, 650);
    window.setWindowTitle("Position Size Calculator");

    QGridLayout *mainLayout = new QGridLayout(&window);
    mainLayout->setContentsMargins(25, 25, 25, 25);
    mainLayout->setHorizontalSpacing(16);
    mainLayout->setVerticalSpacing(16);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setRowStretch(0, 1);
    mainLayout->setRowStretch(1, 1);

    auto makePanel = []() -> QFrame* {
        QFrame *panel = new QFrame();
        panel->setObjectName("panel");

        QGridLayout *layout = new QGridLayout(panel);
        layout->setContentsMargins(20, 16, 20, 20);
        layout->setHorizontalSpacing(10);
        layout->setVerticalSpacing(8);
        layout->setAlignment(Qt::AlignTop);

        // Optional ticker title
        QLineEdit *tickerInput = new QLineEdit();
        tickerInput->setObjectName("tickerInput");
        tickerInput->setPlaceholderText("TICKER");
        tickerInput->setAlignment(Qt::AlignCenter);

        QObject::connect(tickerInput, &QLineEdit::textChanged, [tickerInput](const QString &text) {
            QString upper = text.toUpper();
            if (text != upper) {
                tickerInput->blockSignals(true);
                int pos = tickerInput->cursorPosition();
                tickerInput->setText(upper);
                tickerInput->setCursorPosition(pos);
                tickerInput->blockSignals(false);
            }
        });

        // Risk Amount
        QLabel *riskSizeLabel = new QLabel("RISK AMOUNT");
        riskSizeLabel->setObjectName("inputLabel");
        QLineEdit *riskSizeInput = new QLineEdit();
        riskSizeInput->setValidator(new QDoubleValidator(0, 1000000, 2, riskSizeInput));
        riskSizeInput->setPlaceholderText("50.00");

        // Entry Price
        QLabel *entryLabel = new QLabel("ENTRY PRICE");
        entryLabel->setObjectName("inputLabel");
        QLineEdit *entryInput = new QLineEdit();
        entryInput->setValidator(new QDoubleValidator(0, 1000000, 2, entryInput));
        entryInput->setPlaceholderText("5.48");

        // Stop Loss
        QLabel *stopLossLabel = new QLabel("STOP LOSS");
        stopLossLabel->setObjectName("inputLabel");
        QLineEdit *stopLossInput = new QLineEdit();
        stopLossInput->setValidator(new QDoubleValidator(0, 1000000, 2, stopLossInput));
        stopLossInput->setPlaceholderText("5.23");

        // Position Size output
        QLabel *shareSizeOutputLabel = new QLabel("POSITION SIZE");
        shareSizeOutputLabel->setObjectName("resultLabel");
        QLabel *shareSizeValue = new QLabel("0");
        shareSizeValue->setObjectName("resultValue");

        layout->addWidget(tickerInput,          0, 0, 1, 2);
        layout->addWidget(riskSizeLabel,        1, 0, 1, 2);
        layout->addWidget(riskSizeInput,        2, 0, 1, 2);
        layout->addWidget(entryLabel,           3, 0, 1, 2);
        layout->addWidget(entryInput,           4, 0, 1, 2);
        layout->addWidget(stopLossLabel,        5, 0, 1, 2);
        layout->addWidget(stopLossInput,        6, 0, 1, 2);
        layout->addWidget(shareSizeOutputLabel, 7, 0, 1, 2);
        layout->addWidget(shareSizeValue,       8, 0, 1, 2);

        layout->setRowMinimumHeight(7, 20);

        auto calculateShareSize = [=]() {
            double riskSize = riskSizeInput->text().toDouble();
            double entryPrice = entryInput->text().toDouble();
            double stopLoss = stopLossInput->text().toDouble();

            if (riskSize > 0 && entryPrice > 0 && stopLoss > 0 && entryPrice != stopLoss) {
                double riskPerShare = qAbs(entryPrice - stopLoss);
                int result = static_cast<int>(std::floor(riskSize / riskPerShare));
                shareSizeValue->setText(QString::number(result));
            } else {
                shareSizeValue->setText("0");
            }
        };

        QObject::connect(riskSizeInput, &QLineEdit::textChanged, calculateShareSize);
        QObject::connect(entryInput,    &QLineEdit::textChanged, calculateShareSize);
        QObject::connect(stopLossInput, &QLineEdit::textChanged, calculateShareSize);

        return panel;
    };

    mainLayout->addWidget(makePanel(), 0, 0);
    mainLayout->addWidget(makePanel(), 0, 1);
    mainLayout->addWidget(makePanel(), 1, 0);
    mainLayout->addWidget(makePanel(), 1, 1);

    window.show();

    return app.exec();
}
