#include "splitbutton.h"
#include <QFont>

SplitButton::SplitButton(QWidget *parent) : QPushButton(parent) {
    QFont f = font();
    f.setPointSize(12);
    this->setFont(f);
    this->setFixedSize(50, 80);
}

void SplitButton::mousePressEvent(QMouseEvent *event) {
    int halfHeight = height() / 2;
    if (event->pos().y() < halfHeight) {
        emit upperClicked();
    } else {
        emit lowerClicked();
    }
    emit clicked();
    QPushButton::mousePressEvent(event);
}
