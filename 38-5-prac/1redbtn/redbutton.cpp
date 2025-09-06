#include "redbutton.h"
#include <QPainter>
#include <QSizePolicy>

RedButton::RedButton(QWidget *parent) : QPushButton(parent) {
    originalNormal.load("assets/normal.png");
    originalPressed.load("assets/pressed.png");
    normalBtn = originalNormal;
    pressedBtn = originalPressed;
    curBtn = normalBtn;
    curBtn = curBtn.scaled(150, 150);
    int imgWidth = curBtn.width();
    int imgHeight = curBtn.height();
    this->setMinimumSize(imgWidth, imgHeight);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, &RedButton::onTimeout);
    sndPlayer.setSource(sndSource);
    sndPlayer.setAudioOutput(&sndOutput);
}

void RedButton::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QSize pixSize = curBtn.size();
    QSize widgetSize = size();
    pixSize.scale(widgetSize, Qt::KeepAspectRatio);

    int x = (widgetSize.width() - pixSize.width()) / 2;
    int y = (widgetSize.height() - pixSize.height()) / 2;

    QRect targetRect(x, y, pixSize.width(), pixSize.height());
    painter.drawPixmap(targetRect, curBtn);
}
