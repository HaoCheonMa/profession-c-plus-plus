#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPalette>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Проверка номера телефона");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Поле ввода
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("+11111111111");

    // Надпись для результата
    QLabel *label = new QLabel("Not Ok");
    label->setAlignment(Qt::AlignCenter);

    layout->addWidget(lineEdit);
    layout->addWidget(label);

    // Регулярное выражение: плюс, 11 цифр
    QRegularExpression regex("^\\+\\d{11}$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, &window);
    lineEdit->setValidator(validator);

    QObject::connect(lineEdit, &QLineEdit::textChanged, [&](const QString &text) {
        int pos = 0;
        QValidator::State state = validator->validate(const_cast<QString&>(text), pos);
        if (state == QValidator::Acceptable) {
            label->setText("Ok");
            QPalette p = label->palette();
            p.setColor(QPalette::WindowText, Qt::green);
            label->setPalette(p);
        } else {
            label->setText("Not Ok");
            QPalette p = label->palette();
            p.setColor(QPalette::WindowText, Qt::red);
            label->setPalette(p);
        }
    });

    window.show();
    return app.exec();
}
