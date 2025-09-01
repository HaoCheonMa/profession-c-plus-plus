#include "operationbutton.h"

int OperationButton::curBoxHeight;
QFont OperationButton::f;

#include <QSizePolicy>
OperationButton::OperationButton(QWidget *parent) : QPushButton(parent) {
    this->setMinimumSize(75, 75);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void OperationButton::resizeEvent(QResizeEvent * event)
{
    f = this->font();
    curBoxHeight = this->height();

    f.setPointSize(baseFSize * curBoxHeight / baseBoxHeight);
    this->setFont(f);
    QWidget::resizeEvent(event);
}
