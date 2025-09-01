#include "screendata.h"
#include <QFont>

ScreenData::ScreenData(QString _text, QWidget *parent) : QLabel(parent), textChannel(_text) {
    QFont f = this->font();
    f.setPointSize(18);
    this->setFont(f);
    this->setAlignment(Qt::AlignCenter);
    withValue = textChannel + QString::number(value);
    inputTimer.setInterval(2000);
    inputTimer.setSingleShot(true);
    connect(&inputTimer, &QTimer::timeout, this, &ScreenData::onInputTimeout);
}


