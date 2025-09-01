#include "mainwindow.h"
#include "textbox.h"
#include "operationbutton.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->setMinimumWidth(400);

    TextBox *inputLeft = new TextBox(this);
    inputLeft->setPlaceholderText("Первое число");

    TextBox *inputRight = new TextBox(this);
    inputRight->setPlaceholderText("Второе число");

    TextBox *resultOutput = new TextBox(this);
    resultOutput->setPlaceholderText("Результат вычисления");
    resultOutput->setReadOnly(true);

    QGridLayout *boxes = new QGridLayout();
    boxes->addWidget(inputLeft, 0, 0, 1, 2);
    boxes->addWidget(inputRight, 0, 2, 1, 2);
    boxes->addWidget(resultOutput, 1, 0, 1, 4);

    OperationButton *sum = new OperationButton();
    sum->setText("+");
    OperationButton *subtract = new OperationButton();
    subtract->setText("-");
    OperationButton *multiply = new OperationButton();
    multiply->setText("*");
    OperationButton *division = new OperationButton();
    division->setText("/");

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(sum);
    buttons->addWidget(subtract);
    buttons->addWidget(multiply);
    buttons->addWidget(division);

    QVBoxLayout *widgets = new QVBoxLayout(this);
    widgets->addLayout(boxes);
    widgets->addLayout(buttons);
    this->setLayout(widgets);


    connect(this, &MainWindow::calculate, resultOutput, &TextBox::calculate);

    connect(sum, &QPushButton::clicked, this, [this, inputLeft, inputRight]() {
        emit calculate(inputLeft->text(), inputRight->text(), Operation::Sum);
    });
    connect(subtract, &QPushButton::clicked, this, [this, inputLeft, inputRight]() {
        emit calculate(inputLeft->text(), inputRight->text(), Operation::Subtract);
    });
    connect(multiply, &QPushButton::clicked, this, [this, inputLeft, inputRight]() {
        emit calculate(inputLeft->text(), inputRight->text(), Operation::Multiply);
    });
    connect(division, &QPushButton::clicked, this, [this, inputLeft, inputRight]() {
        emit calculate(inputLeft->text(), inputRight->text(), Operation::Divide);
    });
}

