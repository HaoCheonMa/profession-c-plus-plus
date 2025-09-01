#include "textbox.h"
#include <QFont>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

int TextBox::curBoxHeight;
QFont TextBox::f;

TextBox::TextBox(QWidget *parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(50);
    QRegularExpression numFormat("[-+]?\\d+([.,]?\\d+)?");
    QRegularExpressionValidator *numValidator = new QRegularExpressionValidator(numFormat, this);
    this->setValidator(numValidator);
}

void TextBox::resizeEvent(QResizeEvent * event)
{
    f = this->font();
    curBoxHeight = this->height();

    f.setPointSize(baseFSize * curBoxHeight / baseBoxHeight);
    this->setFont(f);
    QWidget::resizeEvent(event);
}

void TextBox::calculate(const QString &firstNum, const QString &secondNum, MainWindow::Operation op)
{
    if (firstNum.isEmpty() || secondNum.isEmpty())
    {
        setText("Empty line");
        return;
    }
    double first = firstNum.toDouble();
    double second = secondNum.toDouble();
    double resultNum = 0.0;

    switch(op)
    {
    case MainWindow::Operation::Sum:
        resultNum = first + second;
        break;
    case MainWindow::Operation::Subtract:
        resultNum = first - second;
        break;
    case MainWindow::Operation::Multiply:
        resultNum = first * second;
        break;
    case MainWindow::Operation::Divide:
        if (second != 0.0)
            resultNum = first / second;
        else {
            setText("Error: Div by 0");
            return;
        }
        break;
    }
    setText(QString::number(resultNum));
}
